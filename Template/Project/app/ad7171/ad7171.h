//
// Created by joey on 2024-07-03.
//

#include "../sys/headerfile.h"
#include "../protocol/protocol.h"
#include "../api/api.h"

enum AD7171_Resister
{
		AD7171_RST		=	19,
		AD7171_SCLK		= 12,
		AD7171_DOUT		= 13
};

void initAD7171();
void AD7171();
