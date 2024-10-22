//
// Created by joey on 2024-09-24.
//

#include "bma456.h"

/****************************/
/******* write & read *******/
/****************************/

static volatile bool m_xfer_done = false;

void writeReadBMA456(uint8_t *w_data, uint32_t w_length, uint8_t *r_data, uint32_t r_length)
{
		writeReadI2C(BMA456_ADRR, w_data, w_length, r_data, r_length);
}

void writeBMA456(uint8_t *w_data, uint32_t w_length)
{
		writeI2C(BMA456_ADRR, w_data, w_length);
}

/****************************/
/********** config **********/
/****************************/

void setSoftResetBMA456()
{
	uint8_t config[2];
	config[0] = 0x7E;
	config[1] = (0xB6);
	
	writeBMA456(&config[0], sizeof(config));
}

void setAccConf()
{
	uint8_t config[2];
	config[0] = 0x40;
	config[1] = (0xA8); 	

	writeBMA456(&config[0], sizeof(config));
}

void setPwrCrtl()
{
	uint8_t config[2];
	config[0] = 0x7D;
	config[1] = (0x04); 	

	writeBMA456(&config[0], sizeof(config));
}

void setAccRange()
{
	uint8_t config[2];
	config[0] = 0x41;
	config[1] = (0x00);

	writeBMA456(&config[0], sizeof(config));
}

void setInt2ToCtrl()
{
	uint8_t config[2];
	config[0] = 0x54;
	config[1] = (0x08);

	writeBMA456(&config[0], sizeof(config));
}

void setIntMapData()
{
	uint8_t config[2];
	config[0] = 0x58;
	config[1] = (0x40);

	writeBMA456(&config[0], sizeof(config));
}

/****************************/
/********* printer **********/
/****************************/

void printerConectCheckBMA456()
{
		ret_code_t err_code;

    uint8_t rdData;
		uint8_t wrData[1] = {0x16}; 
		
		err_code = writeReadI2C(BMA456_ADRR, wrData, sizeof(wrData), &rdData, sizeof(rdData));
    APP_ERROR_CHECK(err_code);

    if (err_code == 0x00)
    {
			NRF_LOG_INFO("BMA456 init Success");
			NRF_LOG_FLUSH();
//			printf("BMA456 init Success\n");	
    }
    else
    {
    	NRF_LOG_INFO("BMA456 init Fail");
			NRF_LOG_FLUSH();
//			printf("BMA456 init Fail\n");
    }
}



/****************************/
/******** data read *********/
/****************************/

static uint8_t accXYZRaw[6];

void readAccXYZ()
{
		uint8_t wrData[1] = {0x12};
	
    writeReadBMA456(wrData, sizeof(wrData), &accXYZRaw[0], sizeof(accXYZRaw));
}

/****************************/
/****** data converter ******/
/****************************/

static int16_t accX = 0;
static int16_t accY = 0;
static int16_t accZ = 0;

void convAccXYZ(void)
{
    accX = (int16_t)(((uint16_t)accXYZRaw[1] << 8) | accXYZRaw[0]);
    accY = (int16_t)(((uint16_t)accXYZRaw[3] << 8) | accXYZRaw[2]);
    accZ = (int16_t)(((uint16_t)accXYZRaw[5] << 8) | accXYZRaw[4]);

    if (accX > 32767) accX -= 65536;  
    if (accY > 32767) accY -= 65536;
    if (accZ > 32767) accZ -= 65536;
}

/****************************/
/********** bma456 **********/
/****************************/

void initBMA456()
{
    setSoftResetBMA456();
		nrf_delay_ms(2); 
		setPwrCrtl();	
		nrf_delay_us(200);
		setAccConf();
    nrf_delay_us(200);
	  setAccRange();
    nrf_delay_us(200);
    setInt2ToCtrl();
    nrf_delay_us(200);
    setIntMapData();
    nrf_delay_us(200);

		printerConectCheckBMA456();
}

void BMA456()
{
    readAccXYZ();
    convAccXYZ();

		NRF_LOG_INFO("X:%d Y:%d Z:%d", accX, accY, accZ);
		NRF_LOG_FLUSH();
//    saveBMA400(accX, accY, accZ);
}
