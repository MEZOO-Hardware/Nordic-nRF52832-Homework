//
// Created by joey on 2024-06-18.
//

#include "pinChangeInterrupt.h"

/****************************/
/****** ready pin flag ******/
/****************************/

volatile bool flag125HzAD7171 = false;

void enableAD7171ReadyPin125Hz()
{
		flag125HzAD7171 = true;
}

void disableAD7171ReadyPin125Hz()
{
		flag125HzAD7171 = false;
}

bool isAD7171ReadyPin125Hz()
{
		return flag125HzAD7171;
}

/****************************/
/********* handler **********/
/****************************/

void handlerMAX30205(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
}

void handlerBMA400(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
}

void handlerAD7171(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
		enableAD7171ReadyPin125Hz();
}

void initRDYPinMAX30205()
{
		ret_code_t err_code;
		
		nrf_drv_gpiote_in_config_t configMAX30205 = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    configMAX30205.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(P12, &configMAX30205, handlerMAX30205);
    APP_ERROR_CHECK(err_code);
		
    nrf_drv_gpiote_in_event_enable(P12, true);
}

void initRDYPinBMA400()
{
		ret_code_t err_code;
	
		nrf_drv_gpiote_in_config_t configBMA400 = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    configBMA400.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(P14, &configBMA400, handlerBMA400);
    APP_ERROR_CHECK(err_code);
		
    nrf_drv_gpiote_in_event_enable(P14, true);
}

void initRDYPinAD7171()
{
		ret_code_t err_code;
		
		nrf_drv_gpiote_in_config_t configAD7171 = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    configAD7171.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(13, &configAD7171, handlerAD7171);
    APP_ERROR_CHECK(err_code);
		
    nrf_drv_gpiote_in_event_enable(13, true);
}

void initPinChangeInterrupt()
{
    ret_code_t err_code;
	
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
		
//		initRDYPinMAX30205();
//		initRDYPinBMA400();
		initRDYPinAD7171();
}