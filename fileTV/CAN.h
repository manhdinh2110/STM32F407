#ifndef __CAN_H
#define __CAN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

void Config_CAN_GPIO();
void Config_CAN1();
void Config_CAN2();
void NVIC_Config();
void CAN1WriteData(uint16_t ID);
void CAN2WriteData(uint16_t ID);
void CAN1_RX0_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
#endif /* __GPIO_H */