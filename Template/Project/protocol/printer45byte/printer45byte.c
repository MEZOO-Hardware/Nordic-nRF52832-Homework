#include "printer45byte.h"

/****************************/
/******** start flag ********/
/****************************/

volatile bool flag45byteLabViewPrinter = true;

void enable45byteLabViewPrinter()
{
    flag45byteLabViewPrinter = true;
}
void disable45byteLabViewPrinter()
{
    flag45byteLabViewPrinter = false;
}

/****************************/
/******** set etc data ******/
/****************************/

#define etcDataNum      6
static uint16_t etcDataRaw[etcDataNum] = {0, };

void saveBpm(uint16_t bpmVal)
{
    etcDataRaw[0] = bpmVal;
}

void saveEcgDataErrorCount(uint16_t ecgDataErrorVal)
{
    etcDataRaw[1] = ecgDataErrorVal;
}

void saveMAX30205(uint16_t MAX30205Val)
{
    etcDataRaw[2] = MAX30205Val;
}

void saveEcgThres(uint16_t ecgThresVal)
{
    etcDataRaw[3] = ecgThresVal;
}

void saveMAX30101DataErrorCount(uint16_t MAX30101DataErrorVal)
{
    etcDataRaw[4] = MAX30101DataErrorVal;
}

void saveBMA400DataErrorCount(uint16_t BMA400DataErrorVal)
{
    etcDataRaw[5] = BMA400DataErrorVal;
}

/****************************/
/******** set ecg data ******/
/****************************/

#define ecgRawSampleNum     1			
#define ecgRawVarNum				1
static uint16_t ecgErrorCount = 0;
static uint8_t ecgIndex = 0;
static uint16_t ecgRaw[ecgRawVarNum] = {0, };

void saveEcg(uint16_t EcgVal)
{
    if(ecgIndex >= ecgRawSampleNum)
    {
        ecgErrorCount++;
        saveEcgDataErrorCount(ecgErrorCount);
    }
		else
		{
        ecgRaw[ecgIndex] = EcgVal;
    }

    ecgIndex++;
}

#define ecgRawSampleNum2     1			
#define ecgRawVarNum2				1
static uint16_t ecgErrorCount2 = 0;
static uint8_t ecgIndex2 = 0;
static uint16_t ecgRaw2[ecgRawVarNum2] = {0, };

void saveEcg2(uint16_t EcgVal2)
{
    if(ecgIndex2 >= ecgRawSampleNum2)
    {
        ecgErrorCount2++;
//        saveEcgDataErrorCount2(ecgErrorCount2);
    }
		else
		{
        ecgRaw2[ecgIndex2] = EcgVal2;
    }

    ecgIndex2++;
}

#define ecgRawSampleNum3     1			
#define ecgRawVarNum3				1
static uint16_t ecgErrorCount3 = 0;
static uint8_t ecgIndex3 = 0;
static uint16_t ecgRaw3[ecgRawVarNum3] = {0, };

void saveEcg3(uint16_t EcgVal3)
{
    if(ecgIndex3 >= ecgRawSampleNum3)
    {
        ecgErrorCount3++;
//        saveEcgDataErrorCount3(ecgErrorCount3);
    }
		else
		{
        ecgRaw3[ecgIndex3] = EcgVal3;
    }

    ecgIndex3++;
}

#define ecgRawSampleNum4     1			
#define ecgRawVarNum4				1
static uint16_t ecgErrorCount4 = 0;
static uint8_t ecgIndex4 = 0;
static uint16_t ecgRaw4[ecgRawVarNum4] = {0, };

void saveEcg4(uint16_t EcgVal4)
{
    if(ecgIndex4 >= ecgRawSampleNum4)
    {
        ecgErrorCount4++;
//        saveEcgDataErrorCount4(ecgErrorCount4);
    }
		else
		{
        ecgRaw4[ecgIndex4] = EcgVal4;
    }

    ecgIndex4++;
}

#define ecgRawSampleNum5     1			
#define ecgRawVarNum5				1
static uint16_t ecgErrorCount5 = 0;
static uint8_t ecgIndex5 = 0;
static uint16_t ecgRaw5[ecgRawVarNum5] = {0, };

void saveEcg5(uint16_t EcgVal5)
{
    if(ecgIndex5 >= ecgRawSampleNum5)
    {
        ecgErrorCount5++;
//        saveEcgDataErrorCount5(ecgErrorCount5);
    }
		else
		{
        ecgRaw5[ecgIndex5] = EcgVal5;
    }

    ecgIndex5++;
}

/****************************/
/******** set acc data ******/
/****************************/

#define BMA400RawSampleNum    1
#define BMA400RawVarNum       3
static uint8_t BMA400DataErrorCount = 0;
static uint8_t BMA400Index = 0;
static uint16_t BMA400Raw[BMA400RawVarNum] = {0, };

void saveBMA400(int16_t accXVal, int16_t accYVal, int16_t accZVal)
{
    if(BMA400Index >= BMA400RawSampleNum)
    {
        BMA400DataErrorCount++;
        saveBMA400DataErrorCount(BMA400DataErrorCount);
    }
		else
		{
        BMA400Raw[0] = accXVal;
        BMA400Raw[1] = accYVal;
        BMA400Raw[2] = accZVal;
    }

    BMA400Index++;
}

/****************************/
/******** set ppg data ******/
/****************************/

#define MAX30101RawSampleNum    4
#define MAX30101RawVarNum       3
static uint8_t MAX30101DataErrorCount = 0;
static uint8_t MAX30101Index = 0;
static uint16_t MAX30101Raw[MAX30101RawSampleNum][MAX30101RawVarNum] = {0, };

void saveMAX30101(uint16_t RedVal, uint16_t IrVal, uint16_t GreenVal)
{
    if(MAX30101Index >= MAX30101RawSampleNum)
    {
        MAX30101DataErrorCount++;
        saveMAX30101DataErrorCount(MAX30101DataErrorCount);
    }
		else
		{
        MAX30101Raw[MAX30101Index][0] = RedVal;
        MAX30101Raw[MAX30101Index][1] = IrVal;
        MAX30101Raw[MAX30101Index][2] = GreenVal;
    }

    MAX30101Index++;
}


static uint8_t EtcIndex = 0;
void print45byteLabView()
{
    if(flag45byteLabViewPrinter)
		{
				nrf_gpio_pin_toggle(17);
				putchar((unsigned char) 0xFE);
				putchar((unsigned char) 50);

				for (int i = 0; i < ecgRawSampleNum; i++)
				{
						putchar((unsigned char) (ecgRaw[i] >> 8)); 
						putchar((unsigned char) (ecgRaw[i] >> 0));
				}
				ecgIndex = 0;
				
				for (int i = 0; i < ecgRawSampleNum2; i++)
				{
						putchar((unsigned char) (ecgRaw2[i] >> 8)); 
						putchar((unsigned char) (ecgRaw2[i] >> 0));
				}
				ecgIndex2 = 0;
				
				for (int i = 0; i < ecgRawSampleNum3; i++)
				{
						putchar((unsigned char) (ecgRaw3[i] >> 8)); 
						putchar((unsigned char) (ecgRaw3[i] >> 0));
				}
				ecgIndex3 = 0;
				
				for (int i = 0; i < ecgRawSampleNum4; i++)
				{
						putchar((unsigned char) (ecgRaw4[i] >> 8)); 
						putchar((unsigned char) (ecgRaw4[i] >> 0));
				}
				ecgIndex4 = 0;
				
				for (int i = 0; i < ecgRawSampleNum5; i++)
				{
						putchar((unsigned char) (ecgRaw5[i] >> 8)); 
						putchar((unsigned char) (ecgRaw5[i] >> 0));
				}
				ecgIndex5 = 0;				
				
				disable45byteLabViewPrinter();
		}
}

//static uint8_t EtcIndex = 0;
//void print45byteLabView()
//{
//    if(flag45byteLabViewPrinter)
//		{
//				putchar((unsigned char) 0xFE);
//				putchar((unsigned char) 45);

//				for (int i = 0; i < ecgRawSampleNum; i++)
//				{
//						putchar((unsigned char) (ecgRaw[i] >> 8)); 
//						putchar((unsigned char) (ecgRaw[i] >> 0));
//				}
//				ecgIndex = 0;


//				for (int i = 0; i < BMA400RawVarNum; i++)
//				{
//						putchar((unsigned char) (BMA400Raw[i] >> 8));
//						putchar((unsigned char) (BMA400Raw[i] >> 0));
//				}
//				BMA400Index = 0;


//				for (int i = 0; i < MAX30101RawSampleNum; i++)
//				{
//						for (int j = 0; j < MAX30101RawVarNum; j++)
//						{
//								putchar((unsigned char) (MAX30101Raw[i][j] >> 8));
//								putchar((unsigned char) (MAX30101Raw[i][j] >> 0));
//						}
//				}
//				MAX30101Index = 0;


//				if (EtcIndex >= 4)
//				{
//						EtcIndex = 0;
//				}
//				putchar((unsigned char) EtcIndex);
//				putchar((unsigned char) (etcDataRaw[EtcIndex] >> 8));
//				putchar((unsigned char) (etcDataRaw[EtcIndex] >> 0));
//				EtcIndex++;

//				disable45byteLabViewPrinter();
//		}
//}


//void print45byteLabView()
//{
//    if(flag45byteLabViewPrinter)
//		{
//				nrf_gpio_pin_toggle(17);
//				putchar((unsigned char) 0xFE);
//				putchar((unsigned char) 50);

//				for (int i = 0; i < ecgRawSampleNum; i++)
//				{
//						putchar((unsigned char) (ecgRaw[i] >> 8)); 
//						putchar((unsigned char) (ecgRaw[i] >> 0));
//				}
//				ecgIndex = 0;
//				
//				for (int i = 0; i < ecgRawSampleNum2; i++)
//				{
//						putchar((unsigned char) (ecgRaw2[i] >> 8)); 
//						putchar((unsigned char) (ecgRaw2[i] >> 0));
//				}
//				ecgIndex2 = 0;
//				
//				for (int i = 0; i < ecgRawSampleNum; i++)
//				{
//						putchar((unsigned char) (ecgRaw[i] >> 8)); 
//						putchar((unsigned char) (ecgRaw[i] >> 0));
//				}
//				ecgIndex = 0;
//				
//				for (int i = 0; i < ecgRawSampleNum; i++)
//				{
//						putchar((unsigned char) (ecgRaw[i] >> 8)); 
//						putchar((unsigned char) (ecgRaw[i] >> 0));
//				}
//				ecgIndex = 0;
//				
//				for (int i = 0; i < ecgRawSampleNum; i++)
//				{
//						putchar((unsigned char) (ecgRaw[i] >> 8)); 
//						putchar((unsigned char) (ecgRaw[i] >> 0));
//				}
//				ecgIndex = 0;

//				disable45byteLabViewPrinter();
//		}
//}
