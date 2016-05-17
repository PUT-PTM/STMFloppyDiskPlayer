#include "diody.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "FatFs_SD/ff.h"



FATFS g_sFatFs;
FRESULT fresult;
FIL plik,plik2,usta;

typedef unsigned char BYTE;
typedef unsigned long	DWORD;
static volatile BYTE Timer1, Timer2;
unsigned int d, f;

/* Definitions for MMC/SDC command */
#define CMD0 (0x40+0) /* GO_IDLE_STATE */
#define CMD1 (0x40+1) /* SEND_OP_COND */
#define CMD8 (0x40+8) /* SEND_IF_COND */
#define CMD9 (0x40+9) /* SEND_CSD */
#define CMD10 (0x40+10) /* SEND_CID */
#define CMD12 (0x40+12) /* STOP_TRANSMISSION */
#define CMD16 (0x40+16) /* SET_BLOCKLEN */
#define CMD17 (0x40+17) /* READ_SINGLE_BLOCK */
#define CMD18 (0x40+18) /* READ_MULTIPLE_BLOCK */
#define CMD23 (0x40+23) /* SET_BLOCK_COUNT */
#define CMD24 (0x40+24) /* WRITE_BLOCK */
#define CMD25 (0x40+25) /* WRITE_MULTIPLE_BLOCK */
#define CMD41 (0x40+41) /* SEND_OP_COND (ACMD) */
#define CMD55 (0x40+55) /* APP_CMD */
#define CMD58 (0x40+58) /* READ_OCR */

BYTE buffer[4096];	// Bufor przechowuj¹cy kopiowane dane
static
BYTE rcvr_spi();

static
BYTE wait_ready (void);
static
void xmit_spi (BYTE Data);
static
BYTE send_cmd (
    BYTE cmd, /* Command byte */
    DWORD arg /* Argument */
);
void ini_spi();
void ini_karta_sd();
int start_sd(void);
void otwarcie_pliku(void);
void plik_wav();
char* intToStr(int n, char *str);
int min(int a, int b);
