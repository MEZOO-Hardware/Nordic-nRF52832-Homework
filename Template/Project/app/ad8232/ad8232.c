//
// Created by joey on 2024-07-03
//

#include "ad8232.h"

/****************************/
/********** ad8232 **********/
/****************************/

void initAD8232()
{
		initPortOutSet(AVCC_EN);	
	
// Normal   : High(Set)
// ShutDown : Low(Clear)	
		initPortOutSet(AD8232_SHDN);		
	  nrf_delay_us(200);
	
// Fast Recovery Enable  : High(Set)
// Fast Recovery Disable : Low(Clear)			
		initPortOutSet(AD8232_FR);
	  nrf_delay_us(200);
	
// AC Lead OFF(2P) : High(Set)
// DC Lead OFF(3P) : Low(Clear)			
		initPortOutSet(AD8232_ACDC);
	  nrf_delay_us(200);
	
		NRF_LOG_INFO("AD8232 init Success");
}
 