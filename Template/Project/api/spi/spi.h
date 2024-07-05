//
// Created by joey on 2024-06-18.
//

#include "../sys/headerfile.h"

void initSPI(void);
void writeReadSPI(void* txData, size_t txLength, void* rxData, size_t rxLength);
void writeSPI(void* pTransmitData, size_t txSize);
void readSPI(void* pReceiveData, size_t rxSize);
