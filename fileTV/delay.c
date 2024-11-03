#include "delay.h"

void tim_configuration(void){

	/* using register */
	RCC -> APB1ENR |= (1 << 4); // initialize clock for timer 6

	TIM6 -> PSC = ((SystemCoreClock/2)/1000000)-1; // 84Mhz/84 = 1MHz ~~ 1uS delay
	TIM6 -> ARR = 1000;	// MAX ARR value

	TIM6 -> CR1 |= (1 << 0); // counter enabled
	TIM6 -> EGR |= (1 << 0); // set bits UG

	/* using std library */
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 	// enable clock timer 6


	/* setting mode for TIM6 */
	//TIMInit.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1 ;
	//TIMInit.TIM_CounterMode = TIM_CounterMode_Up;
	//TIMInit.TIM_Period = 1000 - 1;	// dem 1000 xung ung voi 1ms
	//TIMInit.TIM_ClockDivision = 0;
	//TIM_TimeBaseInit(TIM6,&TIMInit);
	//TIM_Cmd(TIM6,ENABLE);
}
void delay_1ms(uint32_t us){
	while(us){
		/* using register
		TIM6 -> CNT = 0;	// reset counter
		while((TIM6 -> CNT) < 1000);		// wait for counter reach the entered value
		us--;
		*/
		TIM_SetCounter(TIM6, 0);
		while(TIM_GetCounter(TIM6) < 1000); // cause of setting time period = 999
		us--;
	}
}




