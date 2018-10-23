/**
  * @file    app_isr.c
  * @brief   Interrupt Service Routines
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "app.h"


extern  PCD_HandleTypeDef       hpcd_USB_FS;


void NMI_Handler( void );
void HardFault_Handler( void );
void SVC_Handler( void );
void PendSV_Handler( void );
void SysTick_Handler( void );
void DMA1_Channel2_3_IRQHandler( void );
void USB_IRQHandler( void );
void DMA1_Channel1_IRQHandler( void );
void DMA1_Channel2_3_IRQHandler( void );
void DMA1_Channel4_5_IRQHandler( void );



/**
 * @brief Hard Fault handler
 */
void    hard_fault_handler (                    uint32_t *      arg )
{
        volatile    uint32_t    stacked_r0      = (unsigned long) arg[0];
        volatile    uint32_t    stacked_r1      = (unsigned long) arg[1];
        volatile    uint32_t    stacked_r2      = (unsigned long) arg[2];
        volatile    uint32_t    stacked_r3      = (unsigned long) arg[3];
        volatile    uint32_t    stacked_r12     = (unsigned long) arg[4];
        volatile    uint32_t    stacked_lr      = (unsigned long) arg[5];
        volatile    uint32_t    stacked_pc      = (unsigned long) arg[6];
        volatile    uint32_t    stacked_psr     = (unsigned long) arg[7];


        printf( "[Hard fault handler]\n" );
        printf( "R0 = 0x%x\n", stacked_r0 );
        printf( "R1 = 0x%x\n", stacked_r1 );
        printf( "R2 = 0x%x\n", stacked_r2 );
        printf( "R3 = 0x%x\n", stacked_r3 );
        printf( "R12 = 0x%x\n", stacked_r12 );
        printf( "LR = 0x%x\n", stacked_lr );
        printf( "PC = 0x%x\n", stacked_pc );
        printf( "PSR = 0x%x\n\n", stacked_psr );
        printf( "Execute code from 0x%x\n\n", stacked_pc );
        printf( "See command before 0x%x\n\n", stacked_lr );

	__asm volatile ("bkpt #0\n");         // Break into the debugger
}


/******************************************************************************/
/*            Cortex-M0 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
* @brief This function handles Hard fault interrupt.
*/
/*
void HardFault_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
	asm volatile
	(
	        "TST	LR,		#4			\n"
	        "ITE	EQ					\n"
	        "MRSEQ	R0,		MSP			\n"
	        "MRSNE	R0,		PSP			\n"
	        "B		hard_fault_handler"
	);
        while( 1 );
	#endif //NDEBUG
}
*/


void HardFault_Handler(void)
{
/*
        asm volatile
        (
                "    MOV R0, LR                 \n"
                "    CMP R0, #4                 \n"
                "    BNE hf_psp                 \n"

                "hf_msp:                        \n"
                "    MRS R0, MSP                \n"
                "    B hard_fault_handler       \n"

                "hf_psp:                        \n"
                "    MRS R0, PSP                \n"
                "    B hard_fault_handler       \n"
                :                    // no output
                : [param]"r" (0)     // dummy param
                :                    // no clobbers
        );
*/

	__asm volatile ("bkpt #0\n");         // Break into the debugger
        volatile int i = 1;
        while( i );
}


/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler( void )
{
	#ifdef  NDEBUG
	NVIC_SystemReset();
	#else
        while( 1 );
	#endif //NDEBUG
}


/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler( void )
{
        HAL_IncTick();
        HAL_SYSTICK_IRQHandler();
        ui_led_sts_hook();
        app_wake_hook();
}


/**
* @brief This function handles USB global Interrupt / USB wake-up interrupt through EXTI line 18.
*/
void USB_IRQHandler( void )
{
        HAL_PCD_IRQHandler( &hpcd_USB_FS );
}


/**
* @brief This function handles DMA1 channel 2 and 3 interrupts.
*/
void DMA1_Channel2_3_IRQHandler( void )
{
        bsp_sampler_dma_isr();
}
