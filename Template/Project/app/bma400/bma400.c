//
// Created by joey on 2024-06-18.
//

#include "bma400.h"

static volatile bool m_xfer_done = false;

void writeReadBMA400(uint8_t *w_data, uint32_t w_length, uint8_t *r_data, uint32_t r_length)
{
		writeReadI2C(BMA400_ADDR, w_data, w_length, r_data, r_length);
}

void writeBMA400(uint8_t *w_data, uint32_t w_length)
{
		writeI2C(BMA400_ADDR, w_data, w_length);
}

/********************/
/****** config ******/
/********************/

void setSoftReset()
{
		uint8_t config[2];
		config[0] = BMA400_CommandReg_ADDR;
		config[1] = (0xb6);
		
		writeBMA400(&config[0], sizeof(config));
}

void setAccConfig0()
{
// filt1_bw 		   = 0x00 
// osr_lp 	 			 = 0x00
// power_mode_conf = 0x02
	
		uint8_t config[2];
		config[0] = BMA400_AccConfig0_ADDR;
		config[1] = (0x02);

		writeBMA400(&config[0], sizeof(config));
}

void setAccConfig1()
{
// acc_range  = 0x01 
// osr 				= 0x01
// acc_odr  	= 0x07
	
		uint8_t config[2];
		config[0] = BMA400_AccConfig1_ADDR;
		config[1] = (0x57);

		writeBMA400(&config[0], sizeof(config));
}

void setINTConfig0()
{
		uint8_t config[2];
		config[0] = BMA400_INTConfig0_ADDR;
		config[1] = (0x80);

		writeBMA400(&config[0], sizeof(config));
}

void setInt1Map()
{
		uint8_t config[2];
		config[0] = BMA400_INT1MAP_ADDR;
		config[1] = (0x80);

		writeBMA400(&config[0], sizeof(config));
}

/********************/
/****** printer *****/
/********************/

void printerConectCheckBMA400()
{
    ret_code_t err_code;

    uint8_t rdData;
		uint8_t wrData[1] = {BMA400_ChipID_ADDR}; 
		
		err_code = writeReadI2C(BMA400_ADDR, wrData, sizeof(wrData), &rdData, sizeof(rdData));
    APP_ERROR_CHECK(err_code);

    if (err_code == BMA400_ChipID_ADDR)
    {
			NRF_LOG_INFO("BMA400 init Success");
    }
    else
    {
    	NRF_LOG_INFO("BMA400 init Fail");
    }
}

/********************/
/******* read *******/
/********************/

static uint8_t AccXYZRaw[6];

void readAccXYZ()
{
		uint8_t wrData[1] = {BMA400_AccXLSB_ADDR};
	
    writeReadBMA400(wrData, sizeof(wrData), &AccXYZRaw[0], sizeof(AccXYZRaw));
}

/********************/
/***** converter ****/
/********************/

static int16_t accXVal = 0;
static int16_t accYVal = 0;
static int16_t accZVal = 0;

void convAccXYZ(void)
{
    accXVal = (int16_t)(((uint16_t)AccXYZRaw[1] << 8) | AccXYZRaw[0]);
    accYVal = (int16_t)(((uint16_t)AccXYZRaw[3] << 8) | AccXYZRaw[2]);
    accZVal = (int16_t)(((uint16_t)AccXYZRaw[5] << 8) | AccXYZRaw[4]);

    if(accXVal > 2047) accXVal = (accXVal - 4096);
    if(accYVal > 2047) accYVal = (accYVal - 4096);
    if(accZVal > 2047) accZVal = (accZVal - 4096);
}

/********************/
/****** bma400 ******/
/********************/

void initBMA400()
{
    setSoftReset();
    nrf_delay_ms(2);
    setAccConfig0();
    nrf_delay_us(200);
    setAccConfig1();
    nrf_delay_us(200);
    setINTConfig0();
    nrf_delay_us(200);
    setInt1Map();
    nrf_delay_ms(2);
	
		printerConectCheckBMA400();
}

void BMA400()
{
    readAccXYZ();
    convAccXYZ();
//    saveBMA400(accXVal, accYVal, accZVal);
}









