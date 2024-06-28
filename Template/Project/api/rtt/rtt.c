//
// Created by joey on 2024-06-18.
//

#include "rtt.h"

void initSeggerRTT()
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
}