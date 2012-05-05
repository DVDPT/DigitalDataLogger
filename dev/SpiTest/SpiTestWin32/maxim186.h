#pragma once


#include <stdint.h>
#include <Windows.h>
#include "ftd2xx.h"
#include "libMPSSE_spi.h"
#include "maxim186_config.h"

typedef struct _maxim186_control_byte
{
	FT_HANDLE channel_handle;
	ChannelConfig channel_config;
	union
	{
		uint8_t control_word;
		struct
		{
			unsigned clock_power_mode : 2;
			unsigned conversion_type : 1;
			unsigned polarity : 1;
			unsigned channel : 3;
			unsigned reserved : 1;
		};
	};
} maxim186_configuration_t;


void maxim186_init(maxim186_configuration_t* adcConfig, FT_HANDLE handle);

uint32_t maxim186_get_converted_sample(maxim186_configuration_t* config);

