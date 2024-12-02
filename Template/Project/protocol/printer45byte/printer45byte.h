#include "../sys/headerfile.h"

void saveEcgDataErrorCount(uint16_t EcgDataErrorVal);
void saveMAX30205(uint16_t Max30205Val);
void saveEcgThres(uint16_t EcgThresVal);
void saveMAX30101DataErrorCount(uint16_t Max30101DataErrorVal);
void saveBMA400DataErrorCount(uint16_t Bma400DataErrorVal);
void saveEcg(uint16_t EcgVal);
void saveEcg2(uint16_t EcgVal);
void saveEcg3(uint16_t EcgVal);
void saveEcg4(uint16_t EcgVal);
void saveEcg5(uint16_t EcgVal);
void saveBMA400(int16_t accXVal, int16_t accYVal, int16_t accZVal);
void saveMAX30101(uint16_t RedVal, uint16_t IrVal, uint16_t GreenVal);
void print45byteLabView();
void saveBpm(uint16_t BpmVal);

void enable45byteLabViewPrinter();
void disable45byteLabViewPrinter();

// #include "../sys/headerfile.h"

// void saveEcgDataErrorCount(uint16_t EcgDataErrorVal);
// void saveMAX30205(uint16_t Max30205Val);
// void saveEcgThres(uint16_t EcgThresVal);
// void saveMAX30101DataErrorCount(uint16_t Max30101DataErrorVal);
// void saveBMA400DataErrorCount(uint16_t Bma400DataErrorVal);

// void saveEcg(int16_t EcgVal);
// void saveEcg2(int16_t EcgVal);
// void saveEcg3(int16_t EcgVal);
// void saveEcg4(int16_t EcgVal);

// void saveBMA400(int16_t accXVal, int16_t accYVal, int16_t accZVal);
// void saveMAX30101(uint16_t RedVal, uint16_t IrVal, uint16_t GreenVal);
// void print45byteLabView();
// void saveBpm(uint16_t BpmVal);

// void enable45byteLabViewPrinter();
// void disable45byteLabViewPrinter();