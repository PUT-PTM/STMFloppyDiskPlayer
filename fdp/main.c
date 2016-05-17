#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_dac.h"

void Init_TIM4()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//51 Hz - Gis
	TIM_TimeBaseStructure.TIM_Period = 17;
	TIM_TimeBaseStructure.TIM_Prescaler = 133;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM4, ENABLE);
}

void Init_DAC()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitTypeDef DAC_InitStructure;

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

	DAC_Init(DAC_Channel_1,&DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);
}

unsigned int c,i,a;

int main(void)
{

	Init_TIM4();
	Init_DAC();

	int x = 0;
    while(1)
    {

    	DAC_SetChannel1Data(DAC_Align_12b_R, 0xFFF);
    	a = 100;
    	for(i=0;i<0xAFFFF;i++) {x++;}
    	DAC_SetChannel1Data(DAC_Align_12b_R, 0x000);
    	a = 0;
    	for(i=0;i<0xAFFFF;i++) {x++;}
    	/*c = TIM4->CNT;

    	if(TIM_GetFlagStatus(TIM4, TIM_FLAG_Update)) {
    		if(x == 0) DAC_SetChannel1Data(DAC_Align_12b_R, 0xFFF);
    		else DAC_SetChannel1Data(DAC_Align_12b_R, 0x000);
    	}*/
    }
}
