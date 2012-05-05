
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "maxim186.h"

#include "ftd2xx_util.h"

#define SIZE_OF_DATA_TO_READ_TO_RECOVER_CONVERTED_SAMPLE (2)
#define SIZE_OF_ADC_CONTROL_WORD (1)

void maxim186_init(maxim186_configuration_t* adcConfig, FT_HANDLE handle)
{
	adcConfig->channel_handle = handle;

#ifdef _DEBUG

	FTD2XXX_CHECK_STATUS(SPI_InitChannel(adcConfig->channel_handle, &adcConfig->channel_config));
#elif
	SPI_InitChannel(adcConfig->channel_handle, &adcConfig->channel_config)
#endif

}

uint32_t maxim186_get_converted_sample(maxim186_configuration_t* config)
{

	uint32_t sizeTransfered;
	uint8_t data[SIZE_OF_DATA_TO_READ_TO_RECOVER_CONVERTED_SAMPLE];

	SPI_Write
			(
			config->channel_handle,
				(uint8*)&config->control_word,
				SIZE_OF_ADC_CONTROL_WORD,
				(uint32*)&sizeTransfered,
				SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
			);
	
	
#ifdef _DEBUG
		assert(sizeTransfered == SIZE_OF_ADC_CONTROL_WORD );
#endif

		SPI_Read
			(
				config->channel_handle,
				(uint8*)data,
				SIZE_OF_DATA_TO_READ_TO_RECOVER_CONVERTED_SAMPLE,
				(uint32*)&sizeTransfered,
				SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
			);
#ifdef _DEBUG
	assert(sizeTransfered == SIZE_OF_DATA_TO_READ_TO_RECOVER_CONVERTED_SAMPLE);
#endif

	return ((data[0] << 8) | data[1]) >> 3;

	
}