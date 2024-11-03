#include "stm32f4xx.h"
#include <stdio.h>
#include "lcd.h"
#include "TIMER.h"
#include "gpio.h"
#include "CAN.h"
#include "Encoder.h"
uint8_t Can1Flag,Can2Flag;
	CanTxMsg TxMessage;
	uint16_t CAN1_ID,CAN2_ID;
//void TIM6cog(void)
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
//	TIM_TimeBaseInitTypeDef timer1;
//	
//  timer1.TIM_ClockDivision=TIM_CKD_DIV1;
//	timer1.TIM_CounterMode=TIM_CounterMode_Up;
//	timer1.TIM_Period=1000-1;
//	timer1.TIM_Prescaler=42;
//	timer1.TIM_RepetitionCounter=0;
//  TIM_TimeBaseInit(TIM6,&timer1);

//TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);

//	NVIC_InitTypeDef ngat;
//ngat.NVIC_IRQChannel=TIM6_DAC_IRQn;
//ngat.NVIC_IRQChannelCmd=ENABLE;
//ngat.NVIC_IRQChannelPreemptionPriority=0;
//ngat.NVIC_IRQChannelSubPriority=1;
//NVIC_Init(&ngat);
//	
//	TIM_Cmd(TIM6,ENABLE);
//}
//void config(void)
//{
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	GPIO_InitTypeDef GPIO_InitStruc;
//	GPIO_InitStruc.GPIO_Mode =GPIO_Mode_OUT;
//	GPIO_InitStruc.GPIO_OType=GPIO_OType_PP;
//	GPIO_InitStruc.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
//	GPIO_InitStruc.GPIO_PuPd=GPIO_PuPd_NOPULL;
//	GPIO_InitStruc.GPIO_Speed=GPIO_High_Speed ;
//	GPIO_Init(GPIOC,&GPIO_InitStruc);
//	
//}
//void TIM6_DAC_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
//	{
//		static int time=0;
//		if(++time==1000)
//		{
//						GPIO_ToggleBits(GPIOC,GPIO_Pin_12);
//time=0;
//		}
//		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);


//	}



uint32_t   usartdiv;
uint32_t M_part, F_part;
void UART3_config(void)
{
	//D8-USART3_TX
	//D9-USART3_RX
RCC->AHB1ENR |=(1<<3);//Enable Clock GPIOA;
RCC->APB1ENR |=(1<<18);//Enable clock USART2
GPIOD->MODER |=(2<<16)|(2<<18);//Alternate Function for GPIOA2,A3
GPIOD->OSPEEDR |=(3<<18)|(3<<16);//High speed for A2,A3
GPIOD->AFR[1] |=(7<<0)|(7<<4);
USART3->CR1=0x00;

USART3->CR1 &=~(1<<15); // oversampling by 16
USART3->CR1 &=~(1<<12); //M=0 8 bit word
		usartdiv=((25*14200000)/(4*115200));
   M_part=usartdiv/100;
	 F_part=(usartdiv-(M_part*100));
	 F_part=(((F_part*16)+50)+100)&((uint8_t) 0x0F);
	USART3->BRR = (F_part<<0) | (M_part<<4);
  //USART2->BRR |=(7<<4)|(10<<0);
  USART3->CR1 |=(1<<13); //Rx enable
 USART3->CR1 |=(1<<2)|(1<<3);//Tx Enable
}
void Send_data(uint8_t c)
{
while(!(USART3->SR &(1<<7)))
	;//Check the shift register empty
	USART3->DR=(c&0xff);
while(!(USART3->SR) &(1<<6))
	;//Wait for TC set 
//return c;
}
uint8_t Get_Char(void){
	uint8_t temp;
	while(!((USART3->SR) & (1 << 5))); // wait for RXNE bit to set
	temp = USART3->DR ; // read the data and clear the RXNE bit 
	return temp;
}

int main()
{
	Config_Encoder_GPIO();
	
//	GPIO_Configuration();
//TIM6cog();
//	config();
//init_lcd();
//	 Config_CAN_GPIO();
//	 Config_CAN1();
//	 Config_CAN2();
//	 NVIC_Config();
	
	while(1)
	{
//		CAN2WriteData(0x123);
//		
//		TxMessage.Data[0]=0x12;
//		CAN_Transmit(CAN2,&TxMessage);
//		
//		TxMessage.Data[0]=0x02;
//		CAN_Transmit(CAN2,&TxMessage);
//		OUT_LCD("ABV",0,0);
//	if(Can2Flag==ENABLE)
//	{
//	Can2Flag=DISABLE;
//		Send_data('2');
//	
//	}
//	if(Can1Flag==ENABLE)
//	{
//	Can1Flag=DISABLE;
//		Send_data('1');
//	
//	}

	}
}