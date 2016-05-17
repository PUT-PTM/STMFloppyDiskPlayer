#include "diody.h"
#include "stm32f4xx_gpio.h"

int dioda(int dioda, int ustaw)
{
	/*
	 * dioda - numer diody (1-4)
	 * ustaw - l. dodatnia -> w³¹cz
	 *         zero        -> wy³¹cz
	 *         l. ujemna   -> zmieñ stan
	 */
	if (dioda == 1)
		if (ustaw < 0)
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12); else
		if (ustaw == 0)
			GPIO_ResetBits(GPIOD, GPIO_Pin_12); else
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
	else
	if (dioda == 2)
		if (ustaw < 0)
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13); else
		if (ustaw == 0)
			GPIO_ResetBits(GPIOD, GPIO_Pin_13); else
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
	else
	if (dioda == 3)
		if (ustaw < 0)
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14); else
		if (ustaw == 0)
			GPIO_ResetBits(GPIOD, GPIO_Pin_14); else
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
	else
	if (dioda == 4)
		if (ustaw < 0)
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15); else
		if (ustaw == 0)
			GPIO_ResetBits(GPIOD, GPIO_Pin_15); else
			GPIO_SetBits(GPIOD, GPIO_Pin_15);

	return 0;
}


void dioda_sygnal(int nr_diody, int liczba)
{
	/*
	 * Zapala wybran¹ diodê podan¹ liczbê razy
	 */
	int i, a, licznik, x;

	x = 1000000;	//sta³a czasowa

	dioda(nr_diody,0);
	for(i=0;i<5*x;i++){a++;}
	for(licznik = 0; licznik < liczba; licznik++)
	{
		dioda(nr_diody,1);
		for(i=0;i<2*x;i++){a++;}
		dioda(nr_diody,0);
		for(i=0;i<2*x;i++){a++;}
	}
	for(i=0;i<3*x;i++){a++;}
}
