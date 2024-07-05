//
// Created by joey on 2024-06-18.
//

#include "port.h"

#define initPortOut(portNumber)                 nrf_gpio_pin_dir_set(portNumber, NRF_GPIO_PIN_DIR_OUTPUT)
#define initPortOut2(portNumber)                nrf_gpio_cfg_output(portNumber)
#define initPortIn(portNumber)                  nrf_gpio_pin_dir_set(portNumber, NRF_GPIO_PIN_DIR_INPUT)
#define initPortIn2(portNumber)                 nrf_gpio_cfg_input(portNumber, NRF_GPIO_PIN_NOPULL)

#define setPort(portNumber)                     nrf_gpio_pin_set(portNumber)
#define clearPort(portNumber)                   nrf_gpio_pin_clear(portNumber)
#define togglePort(portNumber)									nrf_gpio_pin_toggle(portNumber)

void initPortOutSet(uint8_t portNumber)
{
    initPortOut(portNumber);
    setPort(portNumber);
}

void initPortOutClear(uint8_t portNumber)
{
    initPortOut(portNumber);
    clearPort(portNumber);
}

void initPort()
{
    initPortIn(NULL);
    initPortOut(NULL);
}

void initNRF52Port()
{
    initPortIn(PORT13_Button1);
    initPortIn(PORT14_Button2);
    initPortIn(PORT15_Button3);
    initPortIn(PORT16_Button4);
    initPortOut(PORT17_LED1);
    initPortOut(PORT18_LED2);
    initPortOut(PORT19_LED3);
    initPortOut(PORT20_LED4);
	
    initPortOutSet(12);
}

void initComoPort()
{
//		initPortOutSet(28); // TP1
//    initPortOutSet(16); // LED1
//    initPortOutSet(17); // LED2
//    initPortIn(15);  		// SW1
//    initPortIn(14);  		// SW2
}

void initPowerHold()
{
    nrf_delay_ms(500);
    initPortOutSet(24);
}
