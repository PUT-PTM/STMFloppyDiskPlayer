#include "karta_sd.h"

int tab1[30000]; //bufor dzwiêku
int petla;
int wym_tab;
int /*ile,*/i;

static// Odebranie bajtu z SD
BYTE rcvr_spi()
{
   BYTE Data = 0;

   while( !( SPI2->SR & SPI_SR_TXE ));
   SPI2->DR = 0xFF;
   while( !( SPI2->SR & SPI_SR_RXNE ));
   Data = SPI2->DR;

   return Data;
}

static
BYTE wait_ready (void)
{
   BYTE res;

   Timer2 = 50; /* Wait for ready in timeout of 500ms */
   rcvr_spi();
   do
      res = rcvr_spi();
   while ((res != 0xFF) && Timer2);

   return res;
}

static// Wyslanie bajtu do SD
void xmit_spi (BYTE Data)
{
   BYTE nought;
   while( !( SPI2->SR & SPI_SR_TXE ));
   SPI2->DR = Data;
   while( !( SPI2->SR & SPI_SR_RXNE ));
   nought = SPI2->DR;
}

static
BYTE send_cmd (
   BYTE cmd, /* Command byte */
   DWORD arg /* Argument */
)
{
   BYTE n, res;

   if (wait_ready() != 0xFF) return 0xFF;

   /* Send command packet */
   xmit_spi(cmd); /* Command */
   xmit_spi((BYTE)(arg >> 24)); /* Argument[31..24] */
   xmit_spi((BYTE)(arg >> 16)); /* Argument[23..16] */
   xmit_spi((BYTE)(arg >> 8)); /* Argument[15..8] */
   xmit_spi((BYTE)arg); /* Argument[7..0] */

   n = 0;
   if (cmd == CMD0) n = 0x95; /* CRC for CMD0(0) */
   if (cmd == CMD8) n = 0x87; /* CRC for CMD8(0x1AA) */
   xmit_spi(n);
   /* Receive command response */
   if (cmd == CMD12) rcvr_spi(); /* Skip a stuff byte when stop reading */
   n = 10; /* Wait for a valid response in timeout of 10 attempts */
   do
      res = rcvr_spi();
   while ((res & 0x80) && --n);

   return res; /* Return with the response value */
}



void ini_spi()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // zegar dla portu GPIO z ktorego wykorzystane zostana piny do SPI (MOSI, MISO, SCK)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // zegar dla portu GPIO z ktorego wykorzystany zostanie pin do SPI (CS)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); // zegar dla modulu SPI2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;


	//inicjalizacja pinow wykorzystywanych do SPI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// SPI SCK, MISO, MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// konfigurcja pinu CS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	// ustawienie pinu w stan wysoki
	GPIO_SetBits(GPIOE, GPIO_Pin_3);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2); // SCK
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2); // MISO
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2); // MOSI

	// konfiguracja SPI w trybie MASTER
	SPI_InitTypeDef SPI_InitStructure;
	SPI_I2S_DeInit(SPI2);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(SPI2, &SPI_InitStructure);

	// Uruchomienie SPI2
	SPI_Cmd(SPI2, ENABLE);

	// Ustawienie pinu CS w stan niski
	GPIO_ResetBits(GPIOE, GPIO_Pin_3);

}

void ini_karta_sd()
{
	int i;
	ini_spi();

	// Wyslanie x10 danych 0xFF
	for(i=0; i<10; i++)
	{
		SPI_I2S_SendData(SPI2, 0xFF);
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	}

	// Wyslanie komendy CMD0 do karty SD
	send_cmd(CMD0, 0);

	fresult = f_mount(0, &g_sFatFs);
}



int start_sd(void)
{
   SystemInit();
   ini_karta_sd();

   return 0;
}

int otwarcie_pliku(void)
{
	/*
	 * Funkcja do testowania biblioteki FATFS i pod³¹czenia karty
	 * "miga" diod¹, której numer znajdzie w pliku "liczba.txt"
	 */
	FIL plik;
	char znak;
	WORD ile_bajtow;

	// Otwarcie do odczytu pliku bitmapy
	fresult = f_open (&plik, "liczba.txt", FA_READ);
	//dioda_ok(fresult);

	fresult = f_read (&plik, &znak, 1, &ile_bajtow);
	//dioda_ok(fresult);

	// Zamyka plik
	fresult = f_close (&plik);
	//dioda_ok(fresult);
	
	if(znak == '1')	return 1;
	else
	if(znak == '2')	return 2;
	else
	if(znak == '3')	return 3;
	else
	if(znak == '4')	return 4;
}
/*
void plik_wav()
{
	char znak;
	WORD ile_bajtow;
	u8 temp[44];		//pomijane dane z pliku .Wav
	u16 rozmiar_probki,probka;
	u32 rozmiar_danych,czestotliwosc;
	int j,ile;//,i;;
	char liczba[5];		//do zamiany int->str

	dioda(1,0);
	dioda(2,0);
	dioda(3,0);
	dioda(4,0);


	// Otwarcie do odczytu pliku .wav
	fresult = f_open (&plik, "s30.wav", FA_READ);
	dioda_ok(fresult);

	//opuszczamy 24 bajty
	fresult = f_read (&plik, &temp[0], 24, &ile_bajtow);
	//pobieramy czêstotliwosc
	fresult = f_read (&plik, &czestotliwosc, 4, &ile_bajtow);
	//opuszczamy 4 bajty
	fresult = f_read (&plik, &temp[0], 4, &ile_bajtow);
	//pobieramy wielkosc probki
	fresult = f_read (&plik, &rozmiar_probki, 2, &ile_bajtow);
	//opuszczamy 6 bajtów
	fresult = f_read (&plik, &temp[0], 6, &ile_bajtow);
	//pobieramy rozmiar danych
	fresult = f_read (&plik, &rozmiar_danych, 4, &ile_bajtow);

	//otwarcie pliku .txt
	fresult = f_open (&plik2,"jedkru.TXT", FA_CREATE_ALWAYS | FA_WRITE);

	dioda(1,1); //w³¹czenie diody

	//ile = rozmiar_danych/rozmiar_probki;
	ile = 0; for(i=0;i<(rozmiar_danych/rozmiar_probki);i++) ile++;

	//zapis danych o pliku do pliku tekstowego
	fresult = f_write(&plik2, "Czêstotliwosc  :", 15, &ile_bajtow);
	fresult = f_write(&plik2, intToStr(czestotliwosc,liczba), 5, &ile_bajtow);
	fresult = f_write(&plik2, "Rozmiar danych :", 15, &ile_bajtow);
	fresult = f_write(&plik2, intToStr(rozmiar_danych,liczba), 5, &ile_bajtow);
	fresult = f_write(&plik2, " | Rozmiar próbki :", 18, &ile_bajtow);
	fresult = f_write(&plik2, intToStr(rozmiar_probki,liczba), 5, &ile_bajtow);
	fresult = f_write(&plik2, " | Liczba próbek  :", 18, &ile_bajtow);
	fresult = f_write(&plik2, intToStr(ile,liczba), 5, &ile_bajtow);

	//zamkniecie pliku .txt
    fresult = f_close (&plik2);

//	int petla;
//	int wym_tab;
	wym_tab = 0; for(i=0;i<30000;i++) wym_tab++; //wym_tab = 30000;

	while(ile>0)
	{
		if(wym_tab > ile) petla = ile; else petla = wym_tab;

		//buforowanie
		for(i=0;i<petla;i++)
		{
			//dioda_sygnal(3,1);
			fresult = f_read (&plik, (u8*) &probka,rozmiar_probki, &ile_bajtow);
			tab1[i] = probka;
		}

		//odtwarzanie
		for(i=0;i<petla;i++)
		{
			wyslij_dziwek(tab1[i]);
			wyslij_dziwek(tab1[i]);
		}

		ile = ile - petla;
	}
	dioda(1,0);




	//zamkniêcie pliku .wav
    fresult = f_close (&plik);
	dioda_ok(fresult);
}
*/
char* intToStr(int n, char *str)
{
     int i = 0;
     for(i=0;i<5;i++)
    	 str[i] = 0;


     str[4] = ((n/1) %10) + 48;
     str[3] = ((n/10) %10) + 48;
     str[2] = ((n/100) %10) + 48;
     str[1] = ((n/1000) %10) + 48;
     str[0] = ((n/10000) %10) + 48;

     return str;
}

int min(int a, int b)
{
	if(a > b)
		return b;
	else
		return a;
}
