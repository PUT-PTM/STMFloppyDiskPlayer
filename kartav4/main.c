
#include "main.h"

int volatile ADC_Result;


void IniTimer()//obsluga timerem
{
	//ustawienie trybu pracy priorytetow przerwan
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef p;
	//numer przerwania
	p.NVIC_IRQChannel = TIM2_IRQn;
	// priorytet g��wny
	p.NVIC_IRQChannelPreemptionPriority = 0x00;	//priorytet
	// subpriorytet
	p.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana�
	p.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype�nion� struktur� do rejestr�w
	NVIC_Init(&p);

	//doprowadzenie sygnalu zerowego
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef a;
	a.TIM_Prescaler=8400;
	a.TIM_CounterMode=TIM_CounterMode_Up;
	a.TIM_Period=2499;
	a.TIM_ClockDivision=0;
	a.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &a);


	// wyczyszczenie przerwania od timera 2
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	// zezwolenie na przerwania od przepe�nienia dla timera 2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//wlaczenie timera
	TIM_Cmd(TIM2, ENABLE);

}

void wyslij_dziwek(int dzwiek)
{
	int b;
	b=1;

	do
	{
		if (SPI_I2S_GetFlagStatus(CODEC_I2S, SPI_I2S_FLAG_TXE))
		{
			SPI_I2S_SendData(CODEC_I2S,dzwiek);
			b=0;
		}
	}while(b);
}

void TIM2_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		//Obs�uga odleg�osciomierza - rgulacja g�oscnosci
		ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC_Result = ADC_GetConversionValue(ADC1)>>3;

		if (ADC_Result >255) ADC_Result = 255;

		Codec_VolumeCtrl(ADC_Result);	//ustawienie g�osnoci

		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


int ini_adc(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); //wej. ADC,
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ADC

	GPIO_InitTypeDef GPIO_InitStructure;

	//inicjalizacja wejścia ADC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitTypeDef ADC_InitStructure;

	//ustawienie rozdzielczości przetwornika na maksymalną (12 bitów)
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	//wyłączenie trybu skanowania (odczytywać będziemy jedno wejście ADC
	//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wejściach/kanałach)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//włączenie ciągłego trybu pracy
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//wyłączenie zewnętrznego wyzwalania
	//konwersja może być wyzwalana timerem, stanem wejścia itd. (szczegóły w //dokumentacji)
	//tu można wybrać dowolną opcję ze względu na linię poniżej, która wyłącza //wyzwalanie innymi układami peryferyjnymi (timerem, zewn. wejściem…)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//wartość binarna wyniku będzie podawana z wyrównaniem do prawej
	//funkcja do odczytu stanu przetwornika ADC zwraca wartość 16-bitową
	//dla przykładu, wartość 0xFF wyrównana w prawo to 0x00FF, w lewo 0x0FF0
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//liczba konwersji równa 1, bo 1 kanał
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);

	ADC_Cmd(ADC1, ENABLE);

	//enables GPIO clock for PortD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
}



int main(void)
{
	SystemInit();

	ini_adc();			//w��czenie ADC (do obs�ugi odleg�osciomierza)
	codec_init();
	codec_ctrl_init();

	Codec_VolumeCtrl(200); //(0-255) pierwotna glosnos�
	I2S_Cmd(CODEC_I2S, ENABLE);



	IniTimer();			//w��czenie timera (z obs�ug� odleg�osciomierza)

	start_sd();			//w��czenie karty SD
	przycisk_start();	//w�czenie przycisku

	while(1)
    {

    }
}

