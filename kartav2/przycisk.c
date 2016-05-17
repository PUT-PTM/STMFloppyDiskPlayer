#include "diody.h"
#include "przycisk.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

void przycisk_start(void)
{
	IniPrzycisku();
	IniTimerPrzerwanie2();
}

void IniPrzycisku(void)
{
//przycisk - PA0

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef y;
	EXTI_InitTypeDef ex;

	y.GPIO_Pin = GPIO_Pin_0;
	y.GPIO_Mode = GPIO_Mode_IN;
	y.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &y);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;
	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	// priorytet główny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	// uruchom dany kanał
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wypełnioną strukturę do rejestrów
	NVIC_Init(&NVIC_InitStructure);


	///* Configure EXTI Line0 */
	ex.EXTI_Line=EXTI_Line0;
	ex.EXTI_Mode=EXTI_Mode_Interrupt;
	ex.EXTI_Trigger=EXTI_Trigger_Rising;
	ex.EXTI_LineCmd=ENABLE;
	EXTI_Init(&ex);

	///* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0) ;
}

void IniTimerPrzerwanie2()//wykorzystywany do przycisku
{
	//ustawienie trybu pracy priorytetow przerwan
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef p;
	//numer przerwania
	p.NVIC_IRQChannel = TIM5_IRQn;
	// priorytet główny
	p.NVIC_IRQChannelPreemptionPriority = 0x01;
	// subpriorytet
	p.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanał
	p.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wypełnioną strukturę do rejestrów
	NVIC_Init(&p);

	//doprowadzenie sygnalu zerowego
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseInitTypeDef a;
	a.TIM_Prescaler=8400;
	a.TIM_CounterMode=TIM_CounterMode_Up;
	a.TIM_Period=200;
	a.TIM_ClockDivision=0;
	a.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5, &a);


	// wyczyszczenie przerwania od timera (wystąpiło przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	// zezwolenie na przerwania od przepełnienia dla timera
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	//wlaczenie timera
	//TIM_Cmd(TIM5, ENABLE);
}


void EXTI0_IRQHandler ( void )
{
	if ( EXTI_GetITStatus ( EXTI_Line0 ) != RESET ) // sprawdzenie źródł a przerwania
	{
	TIM_Cmd(TIM5, ENABLE);
	}
	EXTI_ClearITPendingBit ( EXTI_Line0 ); //pamiętamy o zerowaniu bitu przerwania
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			plik_wav();
			//otwarcie_pliku();
		}
		TIM_Cmd(TIM5, DISABLE);
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}
