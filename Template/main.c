//
// Created by joey on 2024-06-18.
//

/*****************************/
/******** include api ********/
/*****************************/

#include "Project/app/app.h"
#include "Project/api/api.h"
#include "Project/sys/sys.h"
#include "Project/sys/headerfile.h"
#include "Project/protocol/protocol.h"
#include "Project/filter/filter.h"

/****************************/
/******** main entry ********/
/****************************/

void handerLowPowerConsumption()
{
    nrf_pwr_mgmt_init();
    nrf_pwr_mgmt_run();					// initConverterMCUState
		NRF_POWER->DCDCEN = 1;			// initConverterDCDC
}

void initPeripherals()
{
		initNRF52Port();
    initUART();
//		initComoPort();
//		initSeggerRTT();
    initI2C();
//    initSPI();
//		initADC();
		initPinChangeInterrupt();
	
		nrf_delay_ms(20);
//    NRF_LOG_INFO("initPeripherals Completed");
//    NRF_LOG_FLUSH();
	  printf("initPeripherals Completed\n");

}

void initSensors()
{
//		initAD8232();
//		initAD7171();
		initBMA456();
//    NRF_LOG_INFO("initSensors Completed");
//    NRF_LOG_FLUSH();
		printf("initSensors Completed\n");
}

int main()
{
//		initPowerHold();
		initPeripherals();	
		initSensors();
		handerLowPowerConsumption();
		initTimerInterrupt();
	
//	  NRF_LOG_INFO("init ALL Completed");
//    NRF_LOG_FLUSH();
		printf("init ALL Completed\n");
	
    while (true)
    {			
//				idle_state_handle();
			
//				if(isAD7171ReadyPin125Hz())
//				{
//						AD7171();
//						initPortToggle(28);
//						disableAD7171ReadyPin125Hz();
//				}
				print45byteLabView();
			
				if(isBMA456ReadyPin100Hz())
				{
						BMA456();
						disableBMA456ReadyPin100Hz();
				}
				
		} // while
} // main
