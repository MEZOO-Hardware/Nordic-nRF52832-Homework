#include "max30001.h"

/****************************/
/******* read & write *******/
/****************************/

void writeReadMAX30001(uint8_t *txData, uint8_t txLength, uint8_t* rxData, uint8_t rxLength)
{
		writeReadSPI(txData, txLength, rxData, rxLength);
}

/****************************/
/******** max30001 **********/
/****************************/

static uint8_t	wrData[1] = {0x1F};
static uint8_t	rdData[3] = {0,};

void MAX30001Info()
{
		initPortOutClear(12);
		
		writeReadMAX30001(wrData, sizeof(wrData), rdData, sizeof(rdData));
		
		initPortOutSet(12);	
		
		NRF_LOG_INFO("wr Data : 0x%x", wrData[0]);
		NRF_LOG_INFO("rd Data: 0x%x 0x%x 0x%x", rdData[0], rdData[1], rdData[2]);
		NRF_LOG_FLUSH();	
}