//
// Created by joey on 2024-07-03.
//

#include "max30205.h"

/****************************/
/******* write & read *******/
/****************************/

static volatile bool m_xfer_done = false;

void wirteReadMAX30205(uint8_t *w_data, uint32_t w_length, uint8_t *r_data, uint32_t r_length)
{
		writeReadI2C(MAX30205_ADDR, w_data, w_length, r_data, r_length);
}

void writeMAX30205(uint8_t *w_data, uint32_t w_length)
{
		writeI2C(MAX30205_ADDR, w_data, w_length);
}

/****************************/
/********** config **********/
/****************************/

void configInterruptMode()
{	
		uint8_t config[2];
		config[0] = MAX30205_ConfigMode_ADDR;
		config[1] = MAX30205_Interrupt_ADDR;
		writeMAX30205(config, sizeof(config));	
		
		uint8_t configTempOS[3];
		configTempOS[0] = MAX30205_TempOS_ADDR;
		configTempOS[1] = MAX30205_Temp_26;
		configTempOS[2] = 0x00;

		writeMAX30205(configTempOS, sizeof(configTempOS));
}

/****************************/
/********* printer **********/
/****************************/

void printerConnetCheckMAX30205()
{
    ret_code_t err_code;
	
    uint8_t rdData;
		uint8_t wrData[1] = {MAX30205_Connect_ADDR};
		
		err_code = writeReadI2C(MAX30205_ADDR, wrData, sizeof(wrData), &rdData, sizeof(rdData));
    APP_ERROR_CHECK(err_code);

    if (err_code == MAX30205_Connect_ADDR)
    {
        NRF_LOG_INFO("MAX30205 init Success, initial Temp = %d\n", rdData);
    }
    else
    {
        NRF_LOG_INFO("MAX30205 init Fail\n");
    }
}

/****************************/
/******** data read *********/
/****************************/

static uint8_t tempRaw[2];

void readTemp()
{
		uint8_t wrData[1] = {MAX30205_TempRead_ADDR};
	
    wirteReadMAX30205(wrData, sizeof(wrData), tempRaw, sizeof(tempRaw));
}

/****************************/
/****** data converter ******/
/****************************/

//void convTemp()
//{
//		uint8_t wrData[1] = {MAX30205_TempRead_ADDR};
//	
//    wirteReadMAX30205(wrData, sizeof(wrData), tempRaw, sizeof(tempRaw));
//}

/****************************/
/********* max30205 *********/
/****************************/

void initMAX30205()
{
		configInterruptMode();
    nrf_delay_us(200);	
	
		printerConnetCheckMAX30205();
}

void MAX30205()
{	
		readTemp();
//	  convTemp();
//		saveMax30205(tempRaw);	
}
