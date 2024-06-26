//
// Created by joey on 2024-06-18.
//

#include "../sys/headerfile.h"

void initSPI(void);
void writeWhileReadSPI(void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize);
void writeSPI(void* pTransmitData, size_t txSize);
void readSPI(void* pReceiveData, size_t rxSize);
