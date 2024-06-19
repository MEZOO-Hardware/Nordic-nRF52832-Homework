#include "../../sys/headerfile.h"

/* Formula */
//RESULT = [V(P) -  V(N) ] * GAIN/REFERENCE * 2^(RESOLUTION - m)
//if CONFIG.MODE = SE (m = 0), if CONFIG.MODE=Diff (m = 1)

//V(N) = 0;
//GAIN = 1/6;
//REFERENCE Voltage = internal (0.6V);
//RESOLUTION : 12 bit;
//m = 0;

//10bit & VDD : 3.6V
//V(P) = RESULT x REFERENCE / (GAIN x RESOLUTION) = RESULT x (0.6 / (1/6 x 2^(10)) =  ADC_RESULT x 0.003515625;			
//#define ADC_RESULT_IN_VOLTS(ADC_RESULT) ((ADC_RESULT * 0.003515625))

//10bit & VDD : 3V
//V(P) = RESULT x REFERENCE / (GAIN x RESOLUTION) = RESULT x (0.75 / (1/4 x 2^(10)) =  ADC_RESULT x 0.0029296875;		
//#define ADC_RESULT_IN_VOLTS(ADC_RESULT) ((ADC_RESULT * 0.0029296875))

//12bit & VDD : 3V
//V(P) = RESULT x REFERENCE / (GAIN x RESOLUTION) = RESULT x (0.75 / (1/4 x 2^(12)) =  ADC_RESULT x 0.000732421875;
#define ADC_RESULT_IN_VOLTS(ADC_RESULT) ((ADC_RESULT * 0.000732421875))
#define SAMPLES_IN_BUFFER 1

static nrf_saadc_value_t     m_buffer_pool[1][SAMPLES_IN_BUFFER];
static nrf_ppi_channel_t     m_ppi_channel;
static uint32_t              m_adc_evt_counter;
static uint16_t rawDataADC;
static float resultValueADC;

void initADC();