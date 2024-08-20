//
// Created by joey on 2024-07-03
//

#include "ad7171.h"

/****************************/
/******** read only *********/
/****************************/

void readAD7171(uint8_t* rxData, uint8_t rxLength)
{
    readSPI(rxData, rxLength);
}

/****************************/
/********** config **********/
/****************************/

void setSoftResetAD7171()
{
		initPortOutSet(AD7171_RST);	
		
		initPortOutClear(AD7171_RST);
		nrf_delay_us(1);
	
		initPortOutSet(AD7171_RST);
		nrf_delay_ms(1);
}

/****************************/
/******** data read *********/
/****************************/

static uint8_t adcRaw[3] = {0,};

void readADCtoAD7171()
{
		readAD7171(adcRaw, sizeof(adcRaw));
}

/****************************/
/****** data converter ******/
/****************************/

static uint16_t adcCovData = 0;

void convADCtoAD7171()
{
    adcCovData = (int16_t)(((uint16_t)adcRaw[0] << 8) | adcRaw[1]);
}

/****************************/
/********** ad7171 **********/
/****************************/

void initAD7171()
{
		setSoftResetAD7171();
		NRF_LOG_INFO("AD7171 init Success");
		NRF_LOG_FLUSH();
}
	
void AD7171()
{
		readADCtoAD7171();
		convADCtoAD7171();
//		saveEcg(adcCovData);

//		printf("%d\n", adcCovData);
		NRF_LOG_INFO("ADC Value = %d\n", adcCovData);
    NRF_LOG_FLUSH();
}
