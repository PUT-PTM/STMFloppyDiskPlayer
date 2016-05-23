/** \file vectors.c
 * \brief STM32 vector table and __Default_Handler()
 * \details STM32 vector table and __Default_Handler()
 * \author Freddie Chopin
 * \compiler: arm-none-eabi-gcc 4.3.3
******************************************************************************/

/*------------------------------------------------------------------------*//**
* \brief Default interrupt handler.
* \details Default interrupt handler, used for interrupts that don't have their
* own handler defined.
*//*-------------------------------------------------------------------------*/

static void __Default_Handler(void) __attribute__ ((interrupt));
static void __Default_Handler(void)
{
	while (1);
}
/*
+=============================================================================+
| assign all unhandled interrupts to the default handler
+=============================================================================+
*/

// Reset_Handler is defined as symbol in startup.S

// Non-maskable interrupt (RCC clock security system)
void NMI_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// All class of fault
void HardFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Memory management
void MemManage_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Pre-fetch fault, memory access fault
void BusFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Undefined instruction or illegal state
void UsageFault_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x1C
void __Reserved_0x1C_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x20
void __Reserved_0x20_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x24
void __Reserved_0x24_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x28
void __Reserved_0x28_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// System service call via SWI instruction
void SVC_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Debug monitor
void DebugMon_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Reserved 0x34
void __Reserved_0x34_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Pendable request for system service
void PendSV_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// System tick timer
void SysTick_Handler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Window watchdog interrupt
void WWDG_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// PVD through EXTI line detection interrupt
void PVD_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Tamper interrupt
void TAMPER_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RTC global interrupt
void RTC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Flash global interrupt
void FLASH_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RCC global interrupt
void RCC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line0 interrupt
void EXTI0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line1 interrupt
void EXTI1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line2 interrupt
void EXTI2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line3 interrupt
void EXTI3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line4 interrupt
void EXTI4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream0 global interrupt
void DMA1_Stream0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream1 global interrupt
void DMA1_Stream1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream2 global interrupt
void DMA1_Stream2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream3 global interrupt
void DMA1_Stream3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream4 global interrupt
void DMA1_Stream4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream5 global interrupt
void DMA1_Stream5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream6 global interrupt
void DMA1_Stream6_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// ADC1, ADC2 and ADC3 global interrupt
void ADC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN1 TX interrupts
void CAN1_TX_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN1 RX0 interrupts
void CAN1_RX0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN1 RX1 interrupt
void CAN1_RX1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN1 SCE interrupt
void CAN1_SCE_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line[9:5] interrupts
void EXTI9_5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 break interrupt and TIM9 global interrupt
void TIM1_BRK_TIM9_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 update interrupt and TIM10 global interrupt
void TIM1_UP_TIM10_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 trigger and commutation interrupts and TIM11 global interrupt
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM1 capture compare interrupt
void TIM1_CC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM2 global interrupt
void TIM2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM3 global interrupt
void TIM3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM4 global interrupt
void TIM4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C1 event interrupt
void I2C1_EV_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C1 error interrupt
void I2C1_ER_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C2 event interrupt
void I2C2_EV_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C2 error interrupt
void I2C2_ER_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SPI1 global interrupt
void SPI1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SPI2 global interrupt
void SPI2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART1 global interrupt
void USART1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART2 global interrupt
void USART2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART3 global interrupt
void USART3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// EXTI Line[15:10] interrupts
void EXTI15_10_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// RTC alarm through EXTI line interrupt
void RTCAlarm_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USB On-The-Go FS Wakeup through EXTI line interrupt
void OTG_FS_WKUP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM8 break interrupt and TIM12 global interrupt
void TIM8_BRK_TIM12_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM8 update interrupt and TIM13 global interrupt
void TIM8_UP_TIM13_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM8 trigger and commutation interrupts and TIM14 global interrupt
void TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM8 capture compare interrupt
void TIM8_CC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA1 Stream7 global interrupt
void DMA1_Stream7_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// FSMC global interrupt
void FSMC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SDIO global interrupt
void SDIO_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM5 global interrupt
void TIM5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// SPI3 global interrupt
void SPI3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART4 global interrupt
void USART4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART5 global interrupt
void USART5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM6 global interrupt, DAC1 and DAC2 undeerun error interrupt
void TIM6_DAC_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// TIM7 global interrupt
void TIM7_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 0 global interrupt
void DMA2_Stream0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 1 global interrupt
void DMA2_Stream1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 2 global interrupt
void DMA2_Stream2_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 3 global interrupt
void DMA2_Stream3_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 4 global interrupt
void DMA2_Stream4_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// ETH global interrupt
void ETH_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Ethernet Wakeup EXTI line interrupt
void ETH_WKUP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN2 TX interrupts
void CAN2_TX_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN2 RX0 interrupts
void CAN2_RX0_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN2 RX1 interrupt
void CAN2_RX1_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CAN2 SCE interrupt
void CAN2_SCE_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USB On The Go FS global interrupt
void OTG_FS_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 5 global interrupt
void DMA2_Stream5_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 6 global interrupt
void DMA2_Stream6_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DMA2 Stream 7 global interrupt
void DMA2_Stream7_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USART 6 global interrupt
void USART6_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C3 event interrupt
void I2C3_EV_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// I2C3 error interrupt
void I2C3_ER_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USB On The Go HS End Point 1 Out global interrupt
void OTG_HS_EP1_OUT_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USB On The Go HS End Point 1 In global interrupt
void OTG_HS_EP1_IN_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USB On The Go HS Wakeup through EXTI interrupt
void OTG_HS_WKUP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// USB On The Go HS  global interrupt
void OTG_HS_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// DCMI global interrupt
void DCMI_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// CRYP crypto global interrupt
void CRYP_IRQHandler(void) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// Hash and Rng global interrupt
void HASH_RNG_IRQHandler( void ) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

// FPU global interrupt
void FPU_IRQHandler( void ) __attribute__ ((interrupt, weak, alias("__Default_Handler")));

/*
+=============================================================================+
| Vector table
+=============================================================================+
*/

extern const char __main_stack_end;			// imported main stack end (from linker script)

void Reset_Handler(void);					// import the address of Reset_Handler()

void (* const vectors[])(void) __attribute__ ((section(".vectors"))) = {
		(void (*)(void))&__main_stack_end,	// Main stack end address
		Reset_Handler,						// Reset
		NMI_Handler,						// Non-maskable interrupt (RCC clock security system)
		HardFault_Handler,					// All class of fault
		MemManage_Handler,					// Memory management
		BusFault_Handler,					// Pre-fetch fault, memory access fault
		UsageFault_Handler,					// Undefined instruction or illegal state
		__Reserved_0x1C_Handler,			// Reserved 0x1C
		__Reserved_0x20_Handler,			// Reserved 0x20
		__Reserved_0x24_Handler,			// Reserved 0x24
		__Reserved_0x28_Handler,			// Reserved 0x28
		SVC_Handler,						// System service call via SWI instruction
		DebugMon_Handler,					// Debug monitor
		__Reserved_0x34_Handler,			// Reserved 0x34
		PendSV_Handler,						// Pendable request for system service
		SysTick_Handler,					// System tick timer
		WWDG_IRQHandler,					// Window watchdog interrupt
		PVD_IRQHandler,						// PVD through EXTI line detection interrupt
		TAMPER_IRQHandler,					// Tamper interrupt
		RTC_IRQHandler,						// RTC global interrupt
		FLASH_IRQHandler,					// Flash global interrupt
		RCC_IRQHandler,						// RCC global interrupt
		EXTI0_IRQHandler,					// EXTI Line0 interrupt
		EXTI1_IRQHandler,					// EXTI Line1 interrupt
		EXTI2_IRQHandler,					// EXTI Line2 interrupt
		EXTI3_IRQHandler,					// EXTI Line3 interrupt
		EXTI4_IRQHandler,					// EXTI Line4 interrupt
		DMA1_Stream0_IRQHandler,			// DMA1 Stream0 global interrupt
		DMA1_Stream1_IRQHandler,			// DMA1 Stream1 global interrupt
		DMA1_Stream2_IRQHandler,			// DMA1 Stream2 global interrupt
		DMA1_Stream3_IRQHandler,			// DMA1 Stream3 global interrupt
		DMA1_Stream4_IRQHandler,			// DMA1 Stream4 global interrupt
		DMA1_Stream5_IRQHandler,			// DMA1 Stream5 global interrupt
		DMA1_Stream6_IRQHandler,			// DMA1 Stream6 global interrupt
		ADC_IRQHandler,			            // ADC1, ADC2 and ADC3 global interrupt
		CAN1_TX_IRQHandler,			        // CAN1 TX interrupts
		CAN1_RX0_IRQHandler,			    // CAN1 RX0 interrupts
		CAN1_RX1_IRQHandler,				// CAN1 RX1 interrupt
		CAN1_SCE_IRQHandler,				// CAN1 SCE interrupt
		EXTI9_5_IRQHandler,					// EXTI Line[9:5] interrupts
		TIM1_BRK_TIM9_IRQHandler,			// TIM1 break and TIM9 global interrupt
		TIM1_UP_TIM10_IRQHandler,		    // TIM1 update and TIM10 global interrupt
		TIM1_TRG_COM_TIM11_IRQHandler,	    // TIM1 trigger and commutation interrupts and TIM11 global interrupt
		TIM1_CC_IRQHandler,					// TIM1 capture compare interrupt
		TIM2_IRQHandler,					// TIM2 global interrupt
		TIM3_IRQHandler,					// TIM3 global interrupt
		TIM4_IRQHandler,					// TIM4 global interrupt
		I2C1_EV_IRQHandler,					// I2C1 event interrupt
		I2C1_ER_IRQHandler,					// I2C1 error interrupt
		I2C2_EV_IRQHandler,					// I2C2 event interrupt
		I2C2_ER_IRQHandler,					// I2C2 error interrupt
		SPI1_IRQHandler,					// SPI1 global interrupt
		SPI2_IRQHandler,					// SPI2 global interrupt
		USART1_IRQHandler,					// USART1 global interrupt
		USART2_IRQHandler,					// USART2 global interrupt
		USART3_IRQHandler,					// USART3 global interrupt
		EXTI15_10_IRQHandler,				// EXTI Line[15:10] interrupts
		RTCAlarm_IRQHandler,				// RTC alarm through EXTI line interrupt
		OTG_FS_WKUP_IRQHandler,				// USB On-The-Go FS Wakeup through EXTI line interrupt
		TIM8_BRK_TIM12_IRQHandler,			// TIM8 break interrupt and TIM12 global interrupt
		TIM8_UP_TIM13_IRQHandler,			// TIM8 update interrupt and TIM13 global interrupt
		TIM8_TRG_COM_TIM14_IRQHandler,		// TIM8 trigger and commutation interrupts and TIM14 global interupt
		TIM8_CC_IRQHandler,					// TIM8 capture compare interrupt
		DMA1_Stream7_IRQHandler,			// DMA1 Stream7 global interrupt
		FSMC_IRQHandler,					// FSMC global interrupt
		SDIO_IRQHandler,					// SDIO global interrupt
		TIM5_IRQHandler,					// TIM5 global interrupt
		SPI3_IRQHandler,					// SPI3 global interrupt
		USART4_IRQHandler,					// USART4 global interrupt
		USART5_IRQHandler,					// USART5 global interrupt
		TIM6_DAC_IRQHandler,				// TIM6 global interrupt, DAC1 and DAC2 underrun error interrupt
		TIM7_IRQHandler,					// TIM7 global interrupt
		DMA2_Stream0_IRQHandler,			// DMA2 Stream0 global interrupt
		DMA2_Stream1_IRQHandler,			// DMA2 Stream1 global interrupt
		DMA2_Stream2_IRQHandler,			// DMA2 Stream2 global interrupt
		DMA2_Stream3_IRQHandler, 			// DMA2 Stream3 global interrupt
		DMA2_Stream4_IRQHandler,            // DMA2 Stream4 global interrupt
		ETH_IRQHandler,                     // Ethernet global interrupt
		ETH_WKUP_IRQHandler,                // Ethernet Wakeup through EXTI line interrupt
		CAN2_TX_IRQHandler,			        // CAN2 TX interrupts
		CAN2_RX0_IRQHandler,			    // CAN2 RX0 interrupts
		CAN2_RX1_IRQHandler,				// CAN2 RX1 interrupt
		CAN2_SCE_IRQHandler,				// CAN2 SCE interrupt
		OTG_FS_IRQHandler,                  // USB On The Go FS global interrupt
		DMA2_Stream5_IRQHandler,            // DMA2 Stream5 global interrupt
		DMA2_Stream6_IRQHandler,            // DMA2 Stream6 global interrupt
		DMA2_Stream7_IRQHandler,            // DMA2 Stream7 global interrupt
		USART6_IRQHandler,                  // USART6 global interrupt
		I2C3_EV_IRQHandler,                 // I2C3 event interrupt
		I2C3_ER_IRQHandler,                 // I2C3 error interrupt
		OTG_HS_EP1_OUT_IRQHandler,          // USB On The Go HS End Point 1 Out global interrupt
		OTG_HS_EP1_IN_IRQHandler,           // USB On The Go HS End Point 1 In global interrupt
		OTG_HS_WKUP_IRQHandler,             // USB On The Go HS Wakeup through EXTI interrupt
		OTG_HS_IRQHandler,                  // USB On The Go Hs global interrupt
		DCMI_IRQHandler,                    // DCMI global interrupt
		CRYP_IRQHandler,                    // CRYP crypto global interrupt
		HASH_RNG_IRQHandler,                // Hash and Rng global interrupt
		FPU_IRQHandler                      // FPU global interrupt
};

/******************************************************************************
* END OF FILE
******************************************************************************/
