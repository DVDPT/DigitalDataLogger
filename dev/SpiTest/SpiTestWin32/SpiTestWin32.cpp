//// SpiTestWin32.cpp : Defines the entry point for the console application.
////
//#include "stdafx.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
///* OS specific libraries */
//#ifdef _WIN32
//#include <windows.h>
//#endif
//
//#include "ftd2xx.h"
//#include "libMPSSE_spi.h"
//#include "maxim186.h"
//
//#define APP_CHECK_STATUS(exp) {if(exp!=FT_OK){printf("%s:%d:%s(): status(0x%x) \
//!= FT_OK\n",__FILE__, __LINE__, __FUNCTION__,exp);exit(1);}else{;}};
//
//#define APP_NUMBER_OF_SINGLE_CONVERTION_BUFFER_SIZE (2)
//
//int _22tmain(int argc, _TCHAR* argv[])
//{
//	int i;
//	FT_STATUS status;
//	FT_DEVICE_LIST_INFO_NODE devList;
//	uint32 channels = 0;
//	FT_HANDLE channelHandle;
//	ChannelConfig channelConfig;
//	uint8_t data[APP_NUMBER_OF_SINGLE_CONVERTION_BUFFER_SIZE];
//	uint8_t dataOut[APP_NUMBER_OF_SINGLE_CONVERTION_BUFFER_SIZE];
//	maxim186_configuration_t maxim186_control_byte;
//	uint32_t sizeTransfered = 0;
//	uint32_t convertedValue;
//	uint8 aux;
//	///
//	///	Init spi library.
//	///
//	Init_libMPSSE();
//
//	///
//	///	Check number of channels.
//	///
//	SPI_GetNumChannels(&channels);
//
//	for(i=0;i<channels;i++)
//		{
//			status = SPI_GetChannelInfo(i,&devList);
//			//APP_CHECK_STATUS(status);
//			printf("Information on channel number %d:\n",i);
//			/* print the dev info */
//			printf("		Flags=0x%x\n",devList.Flags); 
//			printf("		Type=0x%x\n",devList.Type); 
//			printf("		ID=0x%x\n",devList.ID); 
//			printf("		LocId=0x%x\n",devList.LocId); 
//			printf("		SerialNumber=%s\n",devList.SerialNumber); 
//			printf("		Description=%s\n",devList.Description); 
//			printf("		ftHandle=0x%x\n",devList.ftHandle);/*is 0 unless open*/
//		}
//
//	///
//	///	Configure the channel.
//	///
//	channelConfig.ClockRate = 5000000;
//	channelConfig.LatencyTimer= 255;
//	channelConfig.configOptions = SPI_CONFIG_OPTION_MODE0 | SPI_CONFIG_OPTION_CS_DBUS3;
//	channelConfig.Pin = 0x00000000;/*FinalVal-FinalDir-InitVal-InitDir (for dir 0=in, 1=out)*/
//
//	///
//	///	Open spi channel
//	///
//	status = SPI_OpenChannel(0,&channelHandle);
//	APP_CHECK_STATUS(status);
//
//	
//	///
//	///	Initialize the channel
//	///
//	status = SPI_InitChannel(channelHandle,&channelConfig);
//	APP_CHECK_STATUS(status);
//
//
//	///
//	///	Init the control word for the adc.
//	///
//	maxim186_control_byte.reserved = 1;
//	maxim186_control_byte.channel = MAXIM186_CONFIG_CHANNEL_0;
//	maxim186_control_byte.polarity = MAXIM186_CONFIG_POLARITY_UNIPOLAR;
//	maxim186_control_byte.conversion_type = MAXIM186_CONFIG_CONVERSION_TYPE_SINGLE_ENDED;
//	maxim186_control_byte.clock_power_mode = MAXIM186_CONFIG_CLOCK_POWER_MODE_INTERNAL_CLOCK_MODE;
//
//	printf("config word -> %x\n",maxim186_control_byte.control_word);
//	
//	//
//	
//	/*
//	do
//	{
//
//		status = SPI_ReadWrite(channelHandle,
//			(uint8*)data,
//			(uint8*)dataOut, // size of bytes to send
//			APP_NUMBER_OF_SINGLE_CONVERTION_BUFFER_SIZE,
//			(uint32*)&sizeTransfered,
//			SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
//			);
//		APP_CHECK_STATUS(status);
//	*/
//
//
//	
//	
//	do
//	{
//		
//		SPI_Write
//			(
//				channelHandle,
//				(uint8*)&maxim186_control_byte.control_word,
//				1, // size of bytes to send
//				(uint32*)&sizeTransfered,
//				SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
//			);
//	
//	
//	
//		assert(sizeTransfered == 1);
//	
//		SPI_Read
//			(
//				channelHandle,
//				(uint8*)data,
//				APP_NUMBER_OF_SINGLE_CONVERTION_BUFFER_SIZE,
//				(uint32*)&sizeTransfered,
//				SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES
//			);
//			//*/
//
//			//printf("%d",sizeTransfered);
//		assert(sizeTransfered == APP_NUMBER_OF_SINGLE_CONVERTION_BUFFER_SIZE);
//
//	
//
//		//
//		convertedValue = ((data[0] << 8) | data[1]) >> 3;
//		//printf("Value: %d | %x\n ",convertedValue,convertedValue);
//		convertedValue *=4000;
//		convertedValue/=4096;
//
//
//		printf("Converted value: D:%d X:%x\n",convertedValue , convertedValue);
//		Sleep(200);
//	} while(1);
//	//*/
//
//	///
//	///	Close the channel.	
//	///
//	status = SPI_CloseChannel(channelHandle);
//	APP_CHECK_STATUS(status);
//
//
//
//	
//
//}
//
