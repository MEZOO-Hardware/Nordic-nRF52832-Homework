//
// Created by joey on 2024-06-18.
//

#include "../sys/headerfile.h"

/* I2C instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif

#define I2C_SDA_PIN         ARDUINO_SDA_PIN    // nRF52_DK_Board Pin SDA 26
#define I2C_SCL_PIN         ARDUINO_SCL_PIN    // nRF52_DK_Board Pin SCL 27

void initI2C();

ret_code_t writeI2C(uint8_t address, uint8_t *w_data, uint8_t w_length);
ret_code_t writeReadI2C(uint8_t address, uint8_t *w_data, uint8_t w_length, uint8_t *r_data, uint8_t r_length);
