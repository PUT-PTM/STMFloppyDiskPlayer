#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"

/*
	uint32_t d1 = 2499;
	uint32_t d05 = 1249;
	uint32_t d025 = 625;
	uint32_t d0125 = 312;
	uint32_t d075 = 1875;
*/

void Inits()
{
	SystemInit();
	SystemCoreClockUpdate();

	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

}

void Init_Tim4()
{
	 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	 TIM_TimeBaseStructure.TIM_Period =45976;
	 TIM_TimeBaseStructure.TIM_Prescaler =6;
	 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	 TIM_OCInitTypeDef TIM_OCInitStructure;
	 /* PWM1 Mode configuration: */
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 TIM_OCInitStructure.TIM_Pulse = 0;
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	 TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	 TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	 TIM_ARRPreloadConfig(TIM4, ENABLE);

	 TIM_Cmd(TIM4, ENABLE);
}

void Init_Tim5()
{
	 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	 TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

 	 TIM_TimeBaseStructure.TIM_Period = 2499;
 	 TIM_TimeBaseStructure.TIM_Prescaler =8399;
 	 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
 	 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
 	 TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

 	 TIM_ARRPreloadConfig(TIM5, ENABLE);

 	 TIM_Cmd(TIM5, ENABLE);
}

void Init_GPIO()
{
		GPIO_InitTypeDef GPIO_InitStructure;

		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

	 	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

}

void play(uint32_t period, uint16_t prescaler)
{
	int x;
	TIM4->ARR = period;
	TIM4->PSC = prescaler;
	TIM4->CCR1 = (period/2);
}

void noise()
{
	int x;
	TIM4->ARR = 63000;
	TIM4->PSC = 90;
	TIM4->CCR1 = 63000;
}

void wait(uint32_t dlugosc)
{
	volatile int x;
	while((TIM5->CNT)<dlugosc) {x++;}
	TIM5->CNT = 0;
}

void tone(int dzwiek)
{
	if(dzwiek == 1) play(45976,6); //C 261
	if(dzwiek == 2) play(22052,12); //D 293
	if(dzwiek == 3) play(1948,130); //E 329
	if(dzwiek == 4) play(1850,129); //F 349
	if(dzwiek == 5) play(1850,115); //G 391
	if(dzwiek == -1) play(1850,203); //A bas 322
}

int main(void)
{
	Inits();
	Init_Tim4();
	Init_Tim5();
	Init_GPIO();


	TIM5->ARR = 3999;
	TIM5->PSC = 8399;
	TIM5->CCR1 = 3999;
	uint32_t d1 = TIM5->ARR, d05 = d1/2, d025 = d1/4, d0125 = d1/8;


volatile int x;
    while(1)

    {
    	//1 linijka

    	tone(3); wait(d025);
    	noise(); wait(d0125);

    	tone(3); wait(d025);
    	noise(); wait(d0125);

    	tone(4); wait(d025);
    	noise(); wait(d0125);

    	tone(5); wait(d025);
    	noise(); wait(d0125);

    	tone(5); wait(d025);
    	noise(); wait(d0125);

    	tone(4); wait(d025);
    	noise(); wait(d0125);

    	tone(3); wait(d025);
    	noise(); wait(d0125);

    	tone(2); wait(d025);
    	noise(); wait(d0125);

    	tone(1); wait(d025);
    	noise(); wait(d0125);

    	tone(1); wait(d025);
    	noise(); wait(d0125);

    	tone(2); wait(d025);
    	noise(); wait(d0125);

    	tone(3); wait(d025);
    	noise(); wait(d0125);

    	tone(3); wait(d025); wait(d0125);
    	noise(); wait(d0125);

    	tone(2); wait(d0125);
    	noise(); wait(d0125);

    	tone(2); wait(d05);
    	noise(); wait(d0125);


    	//2 linijka

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(4); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(5); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(5); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(4); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025); wait(d0125);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d0125);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d05);
    	    	noise(); wait(d0125);

    	    	//3 linijka

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d0125);
    	    	noise(); wait(d0125);

    	    	tone(4); wait(d0125);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d0125);
    	    	noise(); wait(d0125);

    	    	tone(4); wait(d0125);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	//4 linijka

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(4); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(5); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(-1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(-1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(3); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(2); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);

    	    	tone(1); wait(d025);
    	    	noise(); wait(d0125);


    }
}
