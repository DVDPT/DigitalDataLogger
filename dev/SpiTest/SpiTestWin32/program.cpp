#include <tchar.h>
#include <Windows.h>
#include <stdio.h>

#include "libMPSSE_spi.h"
#include "maxim186.h"
#include "ftd2xx_util.h"

#define APP_ADC_CHIP_SELECT (SPI_CONFIG_OPTION_CS_DBUS3)
#define APP_SPI_CHANNEL (0)
#define APP_SPI_CLOCK (5000000)
#define APP_SPI_LATENCY (255)
#define APP_SPI_PINS (0)

maxim186_configuration_t channel0_config;
maxim186_configuration_t channel1_config;
maxim186_configuration_t channel2_config;

static void _print_channels_info(int channels);

static void _initialize()
{
	Init_libMPSSE();
}

static void _init_spi_to_adc(FT_HANDLE* handle)
{
	FT_STATUS status;
	uint32 channels = 0;

	SPI_GetNumChannels(&channels);

	if(channels == 0)
	{
		printf("No FTDI device found.\n");
		return;
	}

	_print_channels_info(channels);

	status = SPI_OpenChannel(APP_SPI_CHANNEL,handle);
	FTD2XXX_CHECK_STATUS(status);
}

void _print_channels_info(int channels)
{
	FT_STATUS status;
	FT_DEVICE_LIST_INFO_NODE devList;
	int i;

	for(i=0;i<channels;i++)
		{
			status = SPI_GetChannelInfo(i,&devList);
			FTD2XXX_CHECK_STATUS(status);
			printf("Information on channel number %d:\n",i);
			/* print the dev info */
			printf("		Flags=0x%x\n",devList.Flags); 
			printf("		Type=0x%x\n",devList.Type); 
			printf("		ID=0x%x\n",devList.ID); 
			printf("		LocId=0x%x\n",devList.LocId); 
			printf("		SerialNumber=%s\n",devList.SerialNumber); 
			printf("		Description=%s\n",devList.Description); 
			printf("		ftHandle=0x%x\n",devList.ftHandle);/*is 0 unless open*/
		}

}



static void _init_adc_channel(maxim186_configuration_t* cfg, unsigned int channel )
{
	cfg->channel_config.ClockRate = APP_SPI_CLOCK;
	cfg->channel_config.LatencyTimer= APP_SPI_LATENCY;
	cfg->channel_config.configOptions = SPI_CONFIG_OPTION_MODE0 | APP_ADC_CHIP_SELECT;
	cfg->channel_config.Pin = APP_SPI_PINS;
	
	cfg->reserved = 1;
	cfg->channel = channel;
	cfg->polarity = MAXIM186_CONFIG_POLARITY_UNIPOLAR;
	cfg->conversion_type = MAXIM186_CONFIG_CONVERSION_TYPE_SINGLE_ENDED;
	cfg->clock_power_mode = MAXIM186_CONFIG_CLOCK_POWER_MODE_INTERNAL_CLOCK_MODE;

}

static void _init_adc_channels()
{
	_init_adc_channel(&channel0_config,MAXIM186_CONFIG_CHANNEL_0);
	_init_adc_channel(&channel1_config,MAXIM186_CONFIG_CHANNEL_1);
	_init_adc_channel(&channel2_config,MAXIM186_CONFIG_CHANNEL_2);
}

static void _transform_converted_value_range(uint32_t* convertedValue)
{
	*convertedValue *=4000;
	*convertedValue/=4096;
}


static void _read_from_channels(uint32_t* channel0ConvertedValue, uint32_t* channel1ConvertedValue,uint32_t* channel2ConvertedValue)
{
	*channel0ConvertedValue = maxim186_get_converted_sample(&channel0_config);
	*channel1ConvertedValue = maxim186_get_converted_sample(&channel1_config);
	*channel2ConvertedValue = maxim186_get_converted_sample(&channel2_config);
	_transform_converted_value_range(channel0ConvertedValue);
	_transform_converted_value_range(channel1ConvertedValue);
	_transform_converted_value_range(channel2ConvertedValue);
}

static void _adc_main()
{
	uint32_t channel0ConvertedValue,channel1ConvertedValue,channel2ConvertedValue;
	FT_HANDLE channelHandle;


	_initialize();
	_init_spi_to_adc(&channelHandle);

	
	///
	///	Init the adc channels.
	///
	_init_adc_channels();

	maxim186_init(&channel0_config,channelHandle);
	channel1_config.channel_handle = channelHandle;
	channel2_config.channel_handle = channelHandle;


	do
	{
		_read_from_channels(&channel0ConvertedValue,&channel1ConvertedValue,&channel2ConvertedValue);

		printf("Ch0: %d\t Ch1: %d\t Ch2: %d\t\n",channel0ConvertedValue , channel1ConvertedValue,channel2ConvertedValue);
		Sleep(500);

	}while(1);


}

static void _adc_only_test()
{
	FT_HANDLE handle;
	uint32_t convertedValue;

	_initialize();
	_init_spi_to_adc(&handle);


	_init_adc_channel(&channel0_config,MAXIM186_CONFIG_CHANNEL_0);
	
	maxim186_init(&channel0_config,handle);
	
	do
	{
		convertedValue = maxim186_get_converted_sample(&channel0_config);
		_transform_converted_value_range(&convertedValue);
			

		printf("Converted value: D:%d X:%x\n",convertedValue , convertedValue);
		Sleep(500);
	}while(1);

}




int _tmain(int argc, _TCHAR* argv[])
{
	_adc_main();
	_adc_only_test();
	return 1;
}