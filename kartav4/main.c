
#include "main.h"

int volatile ADC_Result;


void IniTimer()//obsluga timerem
{
	//ustawienie trybu pracy priorytetow przerwan
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef p;
	//numer przerwania
	p.NVIC_IRQChannel = TIM2_IRQn;
	// priorytet g³ówny
	p.NVIC_IRQChannelPreemptionPriority = 0x00;	//priorytet
	// subpriorytet
	p.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	p.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
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
	// zezwolenie na przerwania od przepe³nienia dla timera 2
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
		//Obs³uga odleg³osciomierza - rgulacja g³oscnosci
		ADC_SoftwareStartConv(ADC1);
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC_Result = ADC_GetConversionValue(ADC1)>>3;

		if (ADC_Result >255) ADC_Result = 255;

		Codec_VolumeCtrl(ADC_Result);	//ustawienie g³osnoci

		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


int ini_adc(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); //wej. ADC,
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ADC

	GPIO_InitTypeDef GPIO_InitStructure;

	//inicjalizacja wejÅ›cia ADC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitTypeDef ADC_InitStructure;

	//ustawienie rozdzielczoÅ›ci przetwornika na maksymalnÄ… (12 bitÃ³w)
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	//wyÅ‚Ä…czenie trybu skanowania (odczytywaÄ‡ bÄ™dziemy jedno wejÅ›cie ADC
	//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wejÅ›ciach/kanaÅ‚ach)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//wÅ‚Ä…czenie ciÄ…gÅ‚ego trybu pracy
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//wyÅ‚Ä…czenie zewnÄ™trznego wyzwalania
	//konwersja moÅ¼e byÄ‡ wyzwalana timerem, stanem wejÅ›cia itd. (szczegÃ³Å‚y w //dokumentacji)
	//tu moÅ¼na wybraÄ‡ dowolnÄ… opcjÄ™ ze wzglÄ™du na liniÄ™ poniÅ¼ej, ktÃ³ra wyÅ‚Ä…cza //wyzwalanie innymi ukÅ‚adami peryferyjnymi (timerem, zewn. wejÅ›ciemâ€¦)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//wartoÅ›Ä‡ binarna wyniku bÄ™dzie podawana z wyrÃ³wnaniem do prawej
	//funkcja do odczytu stanu przetwornika ADC zwraca wartoÅ›Ä‡ 16-bitowÄ…
	//dla przykÅ‚adu, wartoÅ›Ä‡ 0xFF wyrÃ³wnana w prawo to 0x00FF, w lewo 0x0FF0
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//liczba konwersji rÃ³wna 1, bo 1 kanaÅ‚
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

	ini_adc();			//w³¹czenie ADC (do obs³ugi odleg³osciomierza)
	codec_init();
	codec_ctrl_init();

	Codec_VolumeCtrl(200); //(0-255) pierwotna glosnosæ
	I2S_Cmd(CODEC_I2S, ENABLE);



	IniTimer();			//w³¹czenie timera (z obs³ug¹ odleg³osciomierza)

	start_sd();			//w³¹czenie karty SD
	przycisk_start();	//w³czenie przycisku

	while(1)
    {

    }
}

