#pragma once

#include <Windows.h>
#include <stdint.h>
#include "ftd2xx.h"
#include "libMPSSE_spi.h"

typedef struct _electrode_config
{
	FT_HANDLE handle;
	ChannelConfig channel_config;
}electrode_config_t;

void electrode_init(electrode_config_t* cfg, FT_HANDLE handle, bool initHandle = true);

void electrode_set(electrode_config_t* cfg, uint16_t minus, uint16_t plus);
