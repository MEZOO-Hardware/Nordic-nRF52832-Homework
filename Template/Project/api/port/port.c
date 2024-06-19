//
// Created by joey on 2024-06-18.
//

#include "port.h"

void initNRF52Board()
{
		bsp_board_init(BSP_INIT_LEDS);
		bsp_board_init(BSP_INIT_BUTTONS);
}
