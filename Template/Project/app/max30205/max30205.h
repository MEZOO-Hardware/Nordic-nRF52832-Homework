//
// Created by joey on 2024-07-03.
//

#include "../sys/headerfile.h"
#include "../api/api.h"

enum MAX30205_Register
{
		MAX30205_ADDR							  = 0x14,
		MAX30205_Connect_ADDR 		  = 0x00,
		MAX30205_TempRead_ADDR			= 0x00,
		MAX30205_ConfigMode_ADDR 		= 0x01,
		MAX30205_TempHYST_ADDR	  	= 0x02,
		MAX30205_TempOS_ADDR 				= 0x03,

		MAX30205_OneShot_ADDR				=	0x80,
		MAX30205_TimeOut_ADDR		 		= 0x40,
		MAX30205_DataFormat_ADDR		= 0x20,
		MAX30205_FaultQueue1_ADDR		= 0x10,
		MAX30205_FaultQueue0_ADDR		= 0x08,
		MAX30205_OsPolagrity_ADDR		= 0x04,
		MAX30205_Interrupt_ADDR			= 0x02,
		MAX30205_ShutDown_ADDR			= 0x01,
	
		MAX30205_Temp_26						= 0x1A,
		MAX30205_Temp_27						= 0x1B,
		MAX30205_Temp_28						= 0x1C,
		MAX30205_Temp_29						= 0x1D,
		MAX30205_Temp_30						= 0x1E,
		MAX30205_Temp_31						= 0x1F
};

void initMAX30205();
void MAX30205();