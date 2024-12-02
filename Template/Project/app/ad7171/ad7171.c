//
// Created by joey on 2024-07-03
//

#include "ad7171.h"

void movingAverageFilter();
void applyFIR_LowPassFilter(uint16_t adcCovData);
/****************************/
/******** read only *********/
/****************************/

void readAD7171(uint8_t* rxData, uint8_t rxLength)
{
    readSPI(rxData, rxLength);
}

/****************************/
/********** config **********/
/****************************/

void setSoftResetAD7171()
{
		initPortOutSet(AD7171_RST);	
		
		initPortOutClear(AD7171_RST);
		nrf_delay_us(1);
	
		initPortOutSet(AD7171_RST);
		nrf_delay_ms(1);
}

/****************************/
/******** data read *********/
/****************************/

static uint8_t adcRaw[3] = {0,};

void readADCtoAD7171()
{
		readAD7171(adcRaw, sizeof(adcRaw));
}

/****************************/
/****** data converter ******/
/****************************/

static uint16_t adcCovData = 0;

void convADCtoAD7171()
{
    adcCovData = (int16_t)(((uint16_t)adcRaw[0] << 8) | adcRaw[1]);
}

/****************************/
/********** ad7171 **********/
/****************************/

void initAD7171()
{
		setSoftResetAD7171();
//		NRF_LOG_INFO("AD7171 init Success");
//		NRF_LOG_FLUSH();
}

/****************************/
/******* data filter ********/
/****************************/

// MAF
#define lengthMAF 6
uint16_t xMAF[lengthMAF] = {0};
uint16_t dataMAF = 0;

void firMovingAverageFilter()
{
    uint16_t sum = 0;
 
    for (int i = lengthMAF - 1; i > 0; i--)
		{
       xMAF[i] = xMAF[i - 1];
    }
		
    xMAF[0] = adcCovData;

    for (int i = 0; i < lengthMAF; i++)
		{
       sum += xMAF[i];
    }
		
    dataMAF = sum / lengthMAF;
}

// LPF_FIR
#define orderLPF_FIR 31
uint16_t xLPF_FIR[orderLPF_FIR] = {0};
uint16_t dataLPF_FIR = 0;

const float coefficientLPF_FIR[orderLPF_FIR] =
{
	-0.0016325767,  0.0003426832,  0.0024053052, -0.0038349897, -0.0006152647,
	0.0092646393, -0.0098887734, -0.0067410168,  0.0265869296, -0.0179750627,
	-0.0281396881,  0.0662771421, -0.0248768950, -0.1169040698, 0.2849232235,
	0.6376659222 , 0.2849232235, -0.1169040698, -0.0248768950,  0.0662771421,
	-0.0281396881, -0.0179750627,  0.0265869296, -0.0067410168, -0.0098887734,
	0.0092646393, -0.0006152647, -0.0038349897,  0.0024053052,  0.0003426832,
	-0.0016325767
};

void firLowPassFilter()
{ 
		uint16_t yLPF_FIR = 0;
	
    for (int i = orderLPF_FIR - 1; i > 0; i--)
		{
				xLPF_FIR[i] = xLPF_FIR[i - 1];
    }
		
    xLPF_FIR[0] = adcCovData;

    for (int i = 0; i < orderLPF_FIR; i++)
		{
				yLPF_FIR += xLPF_FIR[i] * coefficientLPF_FIR[i];
    }
		
		dataLPF_FIR = yLPF_FIR;
}

// HPF_FIR
#define orderHPF_FIR 31  
uint16_t xHPF_FIR[orderHPF_FIR] = {0};
uint16_t dataHPF = 0;

const float coefficientHPF_FIR[orderHPF_FIR] =
{
	-0.0005514495, -0.0006222155, -0.0008293751, -0.0011647177, -0.0016142530,
	-0.0021588158, -0.0027749086, -0.0034357419, -0.0041124274, -0.0047752690,
	-0.0053950936, -0.0059445612, -0.0063993951, -0.0067394743, -0.0069497415,
	0.9926151741, -0.0069497415, -0.0067394743, -0.0063993951, -0.0059445612,
	-0.0053950936, -0.0047752690, -0.0041124274, -0.0034357419, -0.0027749086,
	-0.0021588158, -0.0016142530, -0.0011647177, -0.0008293751, -0.0006222155,
	-0.0005514495
};

void firHighPassFilter()
{ 
		uint16_t yHPF_FIR = 0;
	
    for (int i = orderHPF_FIR - 1; i > 0; i--)
		{
        xHPF_FIR[i] = xHPF_FIR[i - 1];
    }
		
    xHPF_FIR[0] = adcCovData;

    for (int i = 0; i < orderHPF_FIR; i++)
		{
        yHPF_FIR += xHPF_FIR[i] * coefficientHPF_FIR[i];
    }
		
		dataHPF = yHPF_FIR;
}

// IIR LPF
#define orderLPF_IIR 1 
float bLPF_IIR[] = {0.2113249, 0.2113249}; // Feedforward (b0, b1, b2)
float aLPF_IIR[] = {1.0000000, -0.5773503};   		 // Feedback 		(a0, a1, a2)

float xLPF_IIR[orderLPF_IIR + 1] = {0};
float yLPF_IIR[orderLPF_IIR + 1] = {0}; 
int16_t dataLPF_IIR = 0;

void iirLowPassFiler()
{
    float ynLPF_IIR = 0;
	  
		for (int i = orderLPF_IIR; i > 0; i--)
		{
        xLPF_IIR[i] = xLPF_IIR[i - 1];
        yLPF_IIR[i] = yLPF_IIR[i - 1];
    }
		
		xLPF_IIR[0] = adcCovData; 
		
    for (int i = 0; i <= orderLPF_IIR; i++)
		{
        ynLPF_IIR += bLPF_IIR[i] * xLPF_IIR[i];						 // Feedforward
        if (i > 0) ynLPF_IIR -= aLPF_IIR[i] * yLPF_IIR[i]; // Feedback
    }

    yLPF_IIR[0] = ynLPF_IIR / aLPF_IIR[0]; 
		
    dataLPF_IIR = yLPF_IIR[0];  
}


// IIR HPF
#define orderHPF_IIR 1 
float bHPF_IIR[] = {0.9967382, -0.9967382}; // Feedforward (b0, b1, b2)
float aHPF_IIR[] = {1.0, -0.9934763};   		 // Feedback 		(a0, a1, a2)

float xHPF_IIR[orderHPF_IIR + 1] = {0};
float yHPF_IIR[orderHPF_IIR + 1] = {0}; 
int16_t dataHPF_IIR = 0;

void iirHighPassFiler()
{
    float ynHPF_IIR = 0;
	  
		for (int i = orderHPF_IIR; i > 0; i--)
		{
        xHPF_IIR[i] = xHPF_IIR[i - 1];
        yHPF_IIR[i] = yHPF_IIR[i - 1];
    }
		
		xHPF_IIR[0] = adcCovData; 
		
    for (int i = 0; i <= orderHPF_IIR; i++)
		{
        ynHPF_IIR += bHPF_IIR[i] * xHPF_IIR[i];						 // Feedforward
        if (i > 0) ynHPF_IIR -= aHPF_IIR[i] * yHPF_IIR[i]; // Feedback
    }

    yHPF_IIR[0] = ynHPF_IIR / aHPF_IIR[0]; 
		
    dataHPF_IIR = yHPF_IIR[0];  
}

// IIR BSF
#define orderBSF_IIR 2 
float bBSF_IIR[] = {0.04948996, 0.09897991, 0.04948996}; // Feedforward (b0, b1, b2)
float aBSF_IIR[] = {1.0000000, -1.2796324, 0.4775923};   		 // Feedback 		(a0, a1, a2)

float xBSF_IIR[orderBSF_IIR + 1] = {0};
float yBSF_IIR[orderBSF_IIR + 1] = {0}; 
int16_t dataBSF_IIR = 0;

void iirBandStopFiler()
{
    float ynBSF_IIR = 0;
	  
		for (int i = orderBSF_IIR; i > 0; i--)
		{
        xBSF_IIR[i] = xBSF_IIR[i - 1];
        yBSF_IIR[i] = yBSF_IIR[i - 1];
    }
		
		xBSF_IIR[0] = adcCovData; 
		
    for (int i = 0; i <= orderBSF_IIR; i++)
		{
        ynBSF_IIR += bBSF_IIR[i] * xBSF_IIR[i];						 // Feedforward
        if (i > 0) ynBSF_IIR -= aBSF_IIR[i] * yBSF_IIR[i]; // Feedback
    }

    yBSF_IIR[0] = ynBSF_IIR / aBSF_IIR[0]; 
		
    dataBSF_IIR = yBSF_IIR[0];  
}


float dataBSF_IIR_ALL = 0;
float dataHPF_IIR_ALL = 0;
float dataLPF_IIR_ALL = 0;
int16_t data_IIR_ALL = 0;

float xBSF_IIR_ALL[orderBSF_IIR + 1] = {0};
float yBSF_IIR_ALL[orderBSF_IIR + 1] = {0}; 
float xHPF_IIR_ALL[orderHPF_IIR + 1] = {0};
float yHPF_IIR_ALL[orderHPF_IIR + 1] = {0}; 
float xLPF_IIR_ALL[orderLPF_IIR + 1] = {0};
float yLPF_IIR_ALL[orderLPF_IIR + 1] = {0}; 

void iirAllFilter()
{
    float ynBSF_IIR_ALL = 0;
	  
		for (int i = orderBSF_IIR; i > 0; i--)
		{
        xBSF_IIR_ALL[i] = xBSF_IIR_ALL[i - 1];
        yBSF_IIR_ALL[i] = yBSF_IIR_ALL[i - 1];
    }
		
		xBSF_IIR_ALL[0] = adcCovData; 
		
    for (int i = 0; i <= orderBSF_IIR; i++)
		{
        ynBSF_IIR_ALL += bBSF_IIR[i] * xBSF_IIR_ALL[i];						 // Feedforward
        if (i > 0) ynBSF_IIR_ALL -= aBSF_IIR[i] * yBSF_IIR_ALL[i]; // Feedback
    }

    yBSF_IIR_ALL[0] = ynBSF_IIR_ALL / aBSF_IIR[0]; 
		
    dataBSF_IIR_ALL = yBSF_IIR_ALL[0];

    float ynHPF_FIR_ALL = 0;
	  
		for (int i = orderHPF_IIR; i > 0; i--)
		{
        xHPF_IIR_ALL[i] = xHPF_IIR_ALL[i - 1];
        yHPF_IIR_ALL[i] = yHPF_IIR_ALL[i - 1];
    }
		
		xHPF_IIR_ALL[0] = dataBSF_IIR_ALL; 
		
    for (int i = 0; i <= orderHPF_IIR; i++)
		{
        ynHPF_FIR_ALL += bHPF_IIR[i] * xHPF_IIR_ALL[i];						 // Feedforward
        if (i > 0) ynHPF_FIR_ALL -= aHPF_IIR[i] * yHPF_IIR_ALL[i]; // Feedback
    }

    yHPF_IIR_ALL[0] = ynHPF_FIR_ALL / aHPF_IIR[0]; 
		
    dataHPF_IIR_ALL = yHPF_IIR_ALL[0];

    float ynLPF_IIR_ALL = 0;
	  
		for (int i = orderLPF_IIR; i > 0; i--)
		{
        xLPF_IIR_ALL[i] = xLPF_IIR_ALL[i - 1];
        yLPF_IIR_ALL[i] = yLPF_IIR_ALL[i - 1];
    }
		
		xLPF_IIR_ALL[0] = dataHPF_IIR_ALL; 
		
    for (int i = 0; i <= orderLPF_IIR; i++)
		{
        ynLPF_IIR_ALL += bLPF_IIR[i] * xLPF_IIR_ALL[i];						 // Feedforward
        if (i > 0) ynLPF_IIR_ALL -= aLPF_IIR[i] * yLPF_IIR_ALL[i]; // Feedback
    }

    yLPF_IIR_ALL[0] = ynLPF_IIR_ALL / aLPF_IIR[0]; 
		
    dataLPF_IIR_ALL = yLPF_IIR_ALL[0];
		
		data_IIR_ALL = dataLPF_IIR_ALL;
}

void AD7171()
{
		readADCtoAD7171();
		convADCtoAD7171();
	
//		firMovingAverageFilter();
//		firLowPassFilter();
//		firHighPassFilter();
		iirBandStopFiler();
		iirLowPassFiler();
		iirHighPassFiler();
		iirAllFilter();
	
		saveEcg(adcCovData);
//		saveEcg2(dataMAF);
		saveEcg2(dataBSF_IIR);
//		saveEcg3(dataLPF_FIR);
		saveEcg3(dataLPF_IIR);	
		saveEcg4(dataHPF_IIR);
		saveEcg5(data_IIR_ALL);
//		saveEcg4(dataHPF_FIR);
	
	
//		printf("%d\n", adcCovData);
//		NRF_LOG_INFO("ADC Value = %d\n", adcCovData);
//    NRF_LOG_FLUSH();
}



