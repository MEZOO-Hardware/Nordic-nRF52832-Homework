//
// Created by joey on 2024-06-18.
//

#include "../sys/headerfile.h"
#include "../api/api.h"

enum BMA400_Register
{
    BMA400_ADDR							  = 0x14,
    BMA400_ChipID_ADDR 		    = 0x00,
    BMA400_Reserved_ADDR			= 0x01,
    BMA400_ErrReg_ADDR 				= 0x02,
    BMA400_Status_ADDR 				= 0x03,
    BMA400_AccXLSB_ADDR 			= 0x04,
    BMA400_AccXMSB_ADDR 			= 0x05,
    BMA400_AccYLSB_ADDR 			= 0x06,
    BMA400_AccYMSB_ADDR 			= 0x07,
    BMA400_AccZLSB_ADDR 			= 0x08,
    BMA400_AccZMSB_ADDR 			= 0x09,
    BMA400_SensorTime0_ADDR		= 0x0A,
    BMA400_SensorTime1_ADDR		= 0x0B,
    BMA400_SensorTime2_ADDR		= 0x0C,
    BMA400_EVENT_ADDR					= 0x0D,
    BMA400_INTStat0_ADDR 			= 0x0E,
    BMA400_INTStat1_ADDR 			= 0x0F,
    BMA400_INTStat2_ADDR 			= 0x10,
    BMA400_TempData_ADDR 			= 0x11,
    BMA400_FIFOLength0_ADDR 	= 0x12,
    BMA400_FIFOLength1_ADDR 	= 0x13,
    BMA400_FIFOData_ADDR 			= 0x14,
    BMA400_STEPCnt0_ADDR 			= 0x15,
    BMA400_STEPCnt1_ADDR 			= 0x16,
    BMA400_STEPCnt2_ADDR 			= 0x17,
    BMA400_STEPStat_ADDR 			= 0x18,
    BMA400_AccConfig0_ADDR 		= 0x19,
    BMA400_AccConfig1_ADDR 		= 0x1A,
    BMA400_AccConfig2_ADDR 		= 0x1B,
    BMA400_INTConfig0_ADDR 		= 0x1F,
    BMA400_INTConfig1_ADDR 		= 0x20,
    BMA400_INT1MAP_ADDR 			= 0x21,
    BMA400_INT2MAP_ADDR 			= 0x22,
		BMA400_INT12MAP_ADDR 			= 0x23,
		BMA400_FIFOConfig0_ADDR 	=	0x26,
		BMA400_FIFOConfig1_ADDR 	= 0x27,
		BMA400_FIFOConfig2_ADDR 	= 0x28,
    BMA400_CommandReg_ADDR 		= 0x7E
};

void initBMA400();
void BMA400();