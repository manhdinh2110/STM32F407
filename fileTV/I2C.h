#ifndef I2C_H_
#define I2C_H_
#include "stm32f4xx.h"
void I2CGPIO(void);
void I2Cset(void);
void I2Cstart(void);
void I2Ctran(char dulieu[]);
void I2Cadd(uint8_t diachi);
void I2Cre(uint8_t Address,uint8_t *buffer,uint8_t size);
void I2Cstop(void);

void I2Cini(void);
void I2Cini1(void);

void I2C_Read1(uint8_t deviceAddr, uint8_t regAddr,uint16_t *diachi,uint8_t len);
void I2C_Write1(uint8_t deviceAddr, uint8_t regAddr, uint8_t data);
void I2C_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t data);
void I2C_Read(uint8_t deviceAddr, uint8_t regAddr,uint16_t *diachi,uint8_t len);
#endif