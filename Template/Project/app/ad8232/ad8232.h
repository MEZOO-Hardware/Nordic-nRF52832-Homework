//
// Created by joey on 2024-07-03.
//

#include "../sys/headerfile.h"
#include "../api/api.h"

enum AD8232_Resister
{
		AVCC_EN				=   23,
		AD8232_LOD_P  = 	18,
		AD8232_LOD_N  = 	20,
		AD8232_SHDN   =	  29,
		AD8232_FR   	=	  30,
		AD8232_ACDC		= 	31
};

void initAD8232();
