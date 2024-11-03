#include "CAN.h"

uint8_t CAN1_DATA0,CAN1_DATA1,CAN1_DATA2,CAN1_DATA3,CAN1_DATA4,CAN1_DATA5,CAN1_DATA6,CAN1_DATA7;
uint8_t CAN2_DATA0,CAN2_DATA1,CAN2_DATA2,CAN2_DATA3,CAN2_DATA4,CAN2_DATA5,CAN2_DATA6,CAN2_DATA7;
extern uint16_t CAN2_ID;
extern uint16_t CAN1_ID;
extern __IO uint8_t Can1Flag,Can2Flag;
//H13: CAN1_TX
//I9: CAN1_RX
void Config_CAN_GPIO()
{
GPIO_InitTypeDef gpio;
/*Config CAN1*/

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);
GPIO_PinAFConfig(GPIOH,GPIO_PinSource13,GPIO_AF_CAN1);
GPIO_PinAFConfig(GPIOI,GPIO_PinSource9,GPIO_AF_CAN1);
/*Config CAN RX va TX*/
	gpio.GPIO_Mode=GPIO_Mode_AF;
	gpio.GPIO_Pin=GPIO_Pin_13;
	gpio.GPIO_Speed=GPIO_Speed_100MHz;
	gpio.GPIO_PuPd=GPIO_PuPd_UP;
	gpio.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOH,&gpio);
	gpio.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOI,&gpio);
/*Config CAN2*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
/*Connect CAN to PIN*/
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_CAN2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_CAN2);
/*Config CAN RX and TX*/
/*App on STM32F407*/
/*
**Ve connect ta connect CAN 1-CAN 2:
PI9-CAN1_RX-> PB6-CAN2_TX
H13-CAN1_TX->PB5-CAN2_RX
*/
	gpio.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_OType=GPIO_OType_PP;
	gpio.GPIO_PuPd=GPIO_PuPd_UP;
	gpio.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Init(GPIOB,&gpio);
}


void Config_CAN1()
{
	CAN_InitTypeDef can;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
CAN_DeInit(CAN1);
CAN_StructInit(&can);
	CanTxMsg TxMessage; 
/* CAN cell init */
	can.CAN_TTCM=DISABLE;
	can.CAN_ABOM=DISABLE;
	can.CAN_AWUM=DISABLE;
	can.CAN_NART=DISABLE;
	can.CAN_RFLM=DISABLE;
	can.CAN_TXFP=DISABLE;
	can.CAN_Mode=CAN_Mode_Normal;
	/*CAN Baudtare*/
	can.CAN_SJW=CAN_SJW_1tq;
	/* CAN Baudrate = 1MBps (CAN clocked at 30 MHz) */
  can.CAN_BS1=CAN_BS1_2tq;
	can.CAN_BS2=CAN_BS2_2tq;
	can.CAN_Prescaler=42;
	CAN_Init(CAN1,&can);// Khoi dong CAN
	
	/* CAN filter init */
	CAN_FilterInitTypeDef canfilter;

	canfilter.CAN_FilterNumber=0;
	canfilter.CAN_FilterMode=CAN_FilterMode_IdMask;
	canfilter.CAN_FilterScale=CAN_FilterScale_32bit;
	canfilter.CAN_FilterIdHigh=0;
	canfilter.CAN_FilterMaskIdLow=0;
	canfilter.CAN_FilterMaskIdHigh=0;
	canfilter.CAN_FilterFIFOAssignment=0;
	canfilter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&canfilter);
	/*Transmit Structure*/
	TxMessage.StdId=0x321;
	TxMessage.DLC=0x01;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.IDE=CAN_ID_STD;
	/* Enable FIFO 0 message pending Interrupt */
CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}

void Config_CAN2()
{
	CAN_InitTypeDef can;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
CAN_DeInit(CAN2);
CAN_StructInit(&can);
	CanTxMsg TxMessage; 
/* CAN cell init */
	can.CAN_TTCM=DISABLE;
	can.CAN_ABOM=DISABLE;
	can.CAN_AWUM=DISABLE;
	can.CAN_NART=DISABLE;
	can.CAN_RFLM=DISABLE;
	can.CAN_TXFP=DISABLE;
	can.CAN_Mode=CAN_Mode_Normal;
	/*CAN Baudtare*/
	can.CAN_SJW=CAN_SJW_1tq;
	/* CAN Baudrate = 1MBps (CAN clocked at 30 MHz) */
  can.CAN_BS1=CAN_BS1_2tq;
	can.CAN_BS2=CAN_BS2_1tq;
	can.CAN_Prescaler=42;
	CAN_Init(CAN2,&can);// Khoi dong CAN
	
	/* CAN filter init */
		CAN_FilterInitTypeDef canfilter;

	canfilter.CAN_FilterNumber=14;
	canfilter.CAN_FilterMode=CAN_FilterMode_IdMask;
	canfilter.CAN_FilterScale=CAN_FilterScale_32bit;
	canfilter.CAN_FilterIdHigh=0;
	canfilter.CAN_FilterMaskIdLow=0;
	canfilter.CAN_FilterMaskIdHigh=0;
	canfilter.CAN_FilterFIFOAssignment=0;
	canfilter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&canfilter);
	/*Transmit Structure*/
	TxMessage.StdId=0x321;
	TxMessage.DLC=0x01;
	TxMessage.ExtId = 0x01;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.IDE=CAN_ID_STD;
	/* Enable FIFO 0 message pending Interrupt */
CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
}


void NVIC_Config()
{
NVIC_InitTypeDef ngat;
	
ngat.NVIC_IRQChannel=CAN1_RX0_IRQn;
	ngat.NVIC_IRQChannelPreemptionPriority=0;
	ngat.NVIC_IRQChannelSubPriority=1;
ngat.NVIC_IRQChannelCmd=ENABLE;
NVIC_Init(&ngat);
	
	ngat.NVIC_IRQChannel=CAN2_RX0_IRQn;
	ngat.NVIC_IRQChannelPreemptionPriority=0;
	ngat.NVIC_IRQChannelSubPriority=2;
ngat.NVIC_IRQChannelCmd=ENABLE;
NVIC_Init(&ngat);
}
void CAN1WriteData(uint16_t ID)
{
	CanTxMsg TxMessage; 
CAN1_DATA0=0;CAN1_DATA1=0;
CAN1_DATA2=0;CAN1_DATA3=0;
	CAN1_DATA4=0;CAN1_DATA5=0;
	CAN1_DATA6=0;CAN1_DATA7=0;
	/* transmit */
TxMessage.StdId=ID;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.DLC=8;
	TxMessage.Data[0]=CAN1_DATA0;
		TxMessage.Data[1]=CAN1_DATA1;
	TxMessage.Data[2]=CAN1_DATA2;
	TxMessage.Data[3]=CAN1_DATA3;
	TxMessage.Data[4]=CAN1_DATA4;
	TxMessage.Data[5]=CAN1_DATA5;
	TxMessage.Data[6]=CAN1_DATA6;
	TxMessage.Data[7]=CAN1_DATA7;
CAN_Transmit(CAN1,&TxMessage);
}
void CAN2WriteData(uint16_t ID)
{
	CanTxMsg TxMessage; 
CAN2_DATA0=0;CAN2_DATA1=0;
CAN2_DATA2=0;CAN2_DATA3=0;
	CAN2_DATA4=0;CAN2_DATA5=0;
	CAN2_DATA6=0;CAN2_DATA7=0;
	/* transmit */
TxMessage.StdId=ID;
	TxMessage.RTR=CAN_RTR_DATA;
	TxMessage.IDE=CAN_ID_STD;
	TxMessage.DLC=8;
	TxMessage.Data[0]=CAN2_DATA0;
		TxMessage.Data[1]=CAN2_DATA1;
	TxMessage.Data[2]=CAN2_DATA2;
	TxMessage.Data[3]=CAN2_DATA3;
	TxMessage.Data[4]=CAN2_DATA4;
	TxMessage.Data[5]=CAN2_DATA5;
	TxMessage.Data[6]=CAN2_DATA6;
	TxMessage.Data[7]=CAN2_DATA7;
CAN_Transmit(CAN2,&TxMessage);
}
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage; 
CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	CAN1_ID=RxMessage.StdId;
	CAN1_DATA0=RxMessage.Data[0];
	CAN1_DATA1=RxMessage.Data[1];
	CAN1_DATA2=RxMessage.Data[2];
	CAN1_DATA3=RxMessage.Data[3];
	CAN1_DATA4=RxMessage.Data[4];
	CAN1_DATA5=RxMessage.Data[5];
	CAN1_DATA6=RxMessage.Data[6];
	CAN1_DATA7=RxMessage.Data[7];
CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	Can1Flag=ENABLE;
}


void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage; 
CAN_Receive(CAN2,CAN_FIFO0,&RxMessage);
	CAN2_ID=RxMessage.StdId;
	CAN2_DATA0=RxMessage.Data[0];
	CAN2_DATA1=RxMessage.Data[1];
	CAN2_DATA2=RxMessage.Data[2];
	CAN2_DATA3=RxMessage.Data[3];
	CAN2_DATA4=RxMessage.Data[4];
	CAN2_DATA5=RxMessage.Data[5];
	CAN2_DATA6=RxMessage.Data[6];
	CAN2_DATA7=RxMessage.Data[7];
CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);
	Can2Flag=ENABLE;
}




