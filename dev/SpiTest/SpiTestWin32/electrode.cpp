#include <assert.h>
#include <stdio.h>
#include "ftd2xx_util.h"
#include "electrode.h"

#define SIZE_OF_ELECTRODE_MESSAGE (2)

void electrode_init(electrode_config_t* cfg, FT_HANDLE handle, bool initHandle)
{
		cfg->handle = handle;

		if(!initHandle)
			return;

#ifdef _DEBUG

	FTD2XXX_CHECK_STATUS(SPI_InitChannel(cfg->handle, &cfg->channel_config));
#else
		SPI_InitChannel(cfg->handle, &cfg->channel_config);
#endif
}

void electrode_set(electrode_config_t* cfg, uint16_t minus, uint16_t plus)
{
	uint16_t value;
	uint32_t sizeTransfered;
	uint8_t electrodeOut[SIZE_OF_ELECTRODE_MESSAGE];

	
	///	  9   8 7 6 5   4   3 2 1 0
	///      MSB     LSB   MSB     LSB
	/// | 1 | X X X X | 1 | X X X X |
	///  E+     SEL+    E-    SEL-
	value = ((minus & 0xF) | 0x10) | ((plus | 0x10 )<< 5);

	electrodeOut[1] = value & 0xFF;
	electrodeOut[0] = value >> 8;


	SPI_ChangeCS(cfg->handle,cfg->channel_config.configOptions);

	SPI_Write
			(
				cfg->handle,
				electrodeOut,
				SIZE_OF_ELECTRODE_MESSAGE,
				(uint32*)&sizeTransfered,
				SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES | SPI_TRANSFER_OPTIONS_CHIPSELECT_ENABLE | SPI_TRANSFER_OPTIONS_CHIPSELECT_DISABLE
			);

#ifdef _DEBUG
		assert(sizeTransfered == SIZE_OF_ELECTRODE_MESSAGE );
#endif
}
