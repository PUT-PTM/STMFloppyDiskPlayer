#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "defines.h"
#include "tm_stm32f4_fonts.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "tm_stm32f4_fatfs.h"
#include <stdio.h>
#include <string.h>
void LED_GPIO_conf(){
		/* GPIOD Periph clock enable */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		GPIO_InitTypeDef  GPIO_InitStructure;
		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}
int main(void) {
    //Fatfs object
    FATFS FatFs;
    //File object
    FIL fil;
    //Free and total space
    uint32_t total, free;

    //Initialize system
    SystemInit();
    //Initialize delays
    TM_DELAY_Init();
    //Initialize LEDs
    LED_GPIO_conf();

    //Mount drive
    if (f_mount(&FatFs, "", 1) == FR_OK) {
        //Mounted OK, turn on RED LED
    	 GPIO_SetBits(GPIOD,GPIO_Pin_14);

        //Try to open file
        if (f_open(&fil, "1stfile.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            //File opened, turn off RED and turn on GREEN led
        	TM_DISCO_LedON(GPIO_Pin_12);
        	TM_DISCO_LedOff(GPIO_Pin_14);
            //If we put more than 0 characters (everything OK)
            if (f_puts("First string in my file\n", &fil) > 0) {
                if (TM_FATFS_DriveSize(&total, &free) == FR_OK) {
                    //Data for drive size are valid
                }

                //Turn on both leds
                TM_DISCO_LedON(GPIO_Pin_12|GPIO_Pin_14);
            }

            //Close file, don't forget this!
            f_close(&fil);
        }

        //Unmount drive, don't forget this!
        f_mount(0, "", 1);
    }

    while (1) {

    }
}
