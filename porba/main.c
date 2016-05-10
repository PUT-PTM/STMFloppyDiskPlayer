
// Test czy p³ytka poprawnie dzia³a
// 	ustawic diody zeby mruga³y w odpowiednich odstepach czasu i
//zatrzymywac je przyciskiem (sygna³ SOS) 3 szybko 3x wolno (plus na przycisk wylacz/wlacz)

#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"

void init_gpio() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void init_tim4() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 8399;

	TIM_TimeBaseStructure.TIM_Prescaler = 1259;

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

}

void init_tim3() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */

	TIM_TimeBaseStructure.TIM_Period = 8399;

	TIM_TimeBaseStructure.TIM_Prescaler = 4999;

	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

void init_pwm() {
	TIM_OCInitTypeDef TIM_OCInitStructure;

	/* PWM1 Mode configuration: */

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

	TIM_OCInitStructure.TIM_Pulse = 0;

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

void init_nvicTIM4() {
	// ustawienie trybu pracy priorytetów przerwañ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;

	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	// wyczyszczenie przerwania od timera 3 (wyst¹pi³o przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	// zezwolenie na przerwania od przepe³nienia dla timera 3
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

void init_nvicTIM3() {
	// ustawienie trybu pracy priorytetów przerwañ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;

	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	// wyczyszczenie przerwania od timera 3 (wyst¹pi³o przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// zezwolenie na przerwania od przepe³nienia dla timera 3
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void init_button() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

unsigned int licznikTIM3 = 0, licznikTIM4 = 0;

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		GPIO_ToggleBits(GPIOD,
				GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		licznikTIM3++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		GPIO_ToggleBits(GPIOD,
				GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		licznikTIM4++;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void init_exti() {

	//NVIC_InitTypeDef NVIC_InitStructure;
	//NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&NVIC_InitStructure);
	//EXTI_InitTypeDef EXTI_InitStructure;
	//EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	//EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	//EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	//EXTI_Init(&EXTI_InitStructure);
	//SYSCFG_EXTILineConfig(GPIOD, EXTI_PinSource1);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef Button_IRQ;
	Button_IRQ.NVIC_IRQChannel = EXTI0_IRQn;
	Button_IRQ.NVIC_IRQChannelCmd = ENABLE;
	Button_IRQ.NVIC_IRQChannelPreemptionPriority = 0x00;
	Button_IRQ.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&Button_IRQ);

	EXTI_InitTypeDef EXTI_Structure;
	EXTI_Structure.EXTI_Line = GPIO_Pin_0;
	EXTI_Structure.EXTI_LineCmd = ENABLE;
	EXTI_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Structure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_Structure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);

}

unsigned int OnOff = 0, i =0;

void EXTI0_IRQHandler(void) { //Je¿eli zg³oszono przerwanie
	if (EXTI_GetITStatus(EXTI_Line0) == SET) {
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		if (OnOff == 0){
			TIM_Cmd(TIM3, DISABLE);
			TIM_Cmd(TIM4, DISABLE);
			OnOff++;
		}
		else if (OnOff==1){
			TIM_Cmd(TIM3, ENABLE);
			OnOff--;
		}
		for(i = 0; i<7000000; i++);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main(void) {
	SystemInit();

	// inity
	init_gpio();
	//init_button();
	init_tim4();
	init_tim3();
	//init_pwm();
	//init_gpio_af();
	init_nvicTIM4();
	init_nvicTIM3();
	init_exti();

	//start timer
	//TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	//GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	for (;;) {
		if (licznikTIM3 == 6) {
			TIM_Cmd(TIM3, DISABLE);
			TIM_Cmd(TIM4, ENABLE);
			licznikTIM3 = licznikTIM4 = 0;
		}
		if (licznikTIM4 == 6) {
			TIM_Cmd(TIM3, ENABLE);
			TIM_Cmd(TIM4, DISABLE);
			licznikTIM4 = licznikTIM3 = 0;
		}
	}

}
