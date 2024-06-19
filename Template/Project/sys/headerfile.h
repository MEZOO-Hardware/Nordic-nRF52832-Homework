//
// Created by joey on 2024-06-18.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "boards.h"
#include "bsp.h"

#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_saadc.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_spi.h"

#include "app_error.h"
#include "app_util_platform.h"
#include "app_uart.h"
