#include "Encoder.h"

//PC6-----> A : Toc do vi tri
//PC7-----> B : Chieu quay
//-------->XUNG Z: Ktra Quay het 1 vong

int cout;
double speed;
void Config_Encoder_GPIO()
{
	/*
	Ngat timer/Input capture
	Config GPIO PC6
	*/
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode=GPIO_Mode_AF;
	gpio.GPIO_OType=GPIO_OType_PP;
	gpio.GPIO_Pin=GPIO_Pin_6;
	gpio.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&gpio);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	/*Config Pin 7 PORT C*/
	
	/*Config ngat*/
	NVIC_InitTypeDef ngat;
	ngat.NVIC_IRQChannel=TIM3_IRQn;
	ngat.NVIC_IRQChannelCmd=ENABLE;
	ngat.NVIC_IRQChannelPreemptionPriority=0;/*ngat chinh*/
	ngat.NVIC_IRQChannelSubPriority=1;/*ngat phu*/
	NVIC_Init(&ngat);
}

void Config_Inputcapture()
{
	/*Config timer3*/
TIM_TimeBaseInitTypeDef input;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);/*Xung clock TIM3*/
input.TIM_ClockDivision=TIM_CKD_DIV1;
	input.TIM_CounterMode=TIM_CounterMode_Up;
	input.TIM_RepetitionCounter=0;
	input.TIM_Period=0;/*Bo sung*/
	input.TIM_Prescaler=0;/*Bo sung*/
	TIM_TimeBaseInit(TIM3,&input);
	/*Config Input capture*/
	TIM_ICInitTypeDef ipct;
	ipct.TIM_Channel=0;
	ipct.TIM_ICFilter=0;
	ipct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	ipct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	ipct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&ipct);
	TIM_ITConfig(TIM3,TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}
void TIM3_IRQHandler()
{
if(TIM_GetITStatus(TIM3,TIM_IT_CC1)==1)
{
cout++;
	if(cout==334)
	{
	cout=0;
		//sovong++;
	
	}
//vitri=cout/334*360
TIM_ClearFlag(TIM3,TIM_IT_CC1);
}
if(TIM_GetITStatus(TIM3,TIM_IT_Update)==1)
{
speed=cout/334*60;
TIM_ClearFlag(TIM3,TIM_IT_Update);

}


}
//Ok chua



