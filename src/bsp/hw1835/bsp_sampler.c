/**
  * @file    bsp_sampler.c
  * @brief   Board Support Package - RFID Sampler routines
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "bsp_sampler.h"


static  TIM_HandleTypeDef       htim;
static  DMA_HandleTypeDef       hdma;


extern  void    app_rfid_hook_recv_half( void );
extern  void    app_rfid_hook_recv_full( void );


static
void bsp_sampler_half_hook(             DMA_HandleTypeDef *     hdma )
{
        //APP_TRACE( "half\n" );
        app_rfid_hook_recv_half();
}


static
void bsp_sampler_full_hook(             DMA_HandleTypeDef *     hdma )
{
        //APP_TRACE( "full\n" );
        app_rfid_hook_recv_full();
}


static
void bsp_sampler_init_timebase( void )
{
        __HAL_RCC_TIM2_CLK_ENABLE();

        htim.Instance                   = TIM2;
        htim.Init.Prescaler             = 48;
        htim.Init.CounterMode           = TIM_COUNTERMODE_UP;
        //htim.Init.Period                = ( 10000 );
        //htim.Init.Period                = ( 1000000 / 125 );
        //htim.Init.Period                = ( 1000000 / 16000 );
        //htim.Init.Period                = ( 1000000 / 32000 );
        htim.Init.Period                = ( 1000000 / 31250 );
        //htim.Init.Period                = ( 1000000 / 15625 );
        //htim.Init.Period                = ( 1000000 / 7813 );
        htim.Init.ClockDivision         = TIM_CLOCKDIVISION_DIV1;
        htim.Init.AutoReloadPreload     = TIM_AUTORELOAD_PRELOAD_DISABLE;

        if( HAL_TIM_Base_Init( &htim ) != HAL_OK )
        {
                app_error( __FILE__, __LINE__ );
        }
/*
        if( HAL_TIM_PWM_Init( &htim ) != HAL_OK )
        {
                app_error( __FILE__, __LINE__ );
        }
*/
}


static
void bsp_sampler_init_dma( void )
{
        __HAL_RCC_DMA1_CLK_ENABLE();

        hdma.Init.Direction             = DMA_PERIPH_TO_MEMORY;
        hdma.Init.PeriphInc             = DMA_PINC_DISABLE;
        hdma.Init.MemInc                = DMA_MINC_ENABLE;
        hdma.Init.PeriphDataAlignment   = DMA_PDATAALIGN_HALFWORD;
        hdma.Init.MemDataAlignment      = DMA_MDATAALIGN_HALFWORD;
        hdma.Init.Mode                  = DMA_CIRCULAR;
        hdma.Init.Priority              = DMA_PRIORITY_HIGH;
        hdma.Instance                   = DMA1_Channel2;

        __HAL_LINKDMA( &htim, hdma[ TIM_DMA_ID_UPDATE ], hdma );
        HAL_DMA_Init( htim.hdma[ TIM_DMA_ID_UPDATE ] );

        //hdma.XferHalfCpltCallback       = bsp_sampler_half_hook;
        //hdma.XferCpltCallback           = bsp_sampler_full_hook;

        if( HAL_OK != HAL_DMA_RegisterCallback( &hdma, HAL_DMA_XFER_HALFCPLT_CB_ID, bsp_sampler_half_hook ) )
        {
                app_error( __FILE__, __LINE__ );
        }

        if( HAL_OK != HAL_DMA_RegisterCallback( &hdma, HAL_DMA_XFER_CPLT_CB_ID, bsp_sampler_full_hook ) )
        {
                app_error( __FILE__, __LINE__ );
        }

        HAL_NVIC_SetPriority(   DMA1_Channel2_3_IRQn, 0, 0 );
        HAL_NVIC_EnableIRQ(     DMA1_Channel2_3_IRQn);
}


static
void bsp_sampler_init_io( void )
{
/*
	GPIO_InitTypeDef        gpio_led_sd     =   {    .Pin       =    GPIO_PIN_4,
	                                                 .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                                 .Pull      =    GPIO_NOPULL,
	                                                 .Speed     =    GPIO_SPEED_FREQ_LOW };

	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_Init( GPIOA, &gpio_led_sd );
*/

        //GPIO_InitTypeDef        GPIO_InitStruct;
        //if( htim->Instance == TIM14 )
        {
                /**TIM14 GPIO Configuration
                PA4     ------> TIM14_CH1
                */
/*
                GPIO_InitStruct.Pin             = GPIO_PIN_4;
                GPIO_InitStruct.Mode            = GPIO_MODE_AF_PP;
                GPIO_InitStruct.Pull            = GPIO_NOPULL;
                GPIO_InitStruct.Speed           = GPIO_SPEED_FREQ_LOW;
                GPIO_InitStruct.Alternate       = GPIO_AF4_TIM14;
                HAL_GPIO_Init( GPIOA, &GPIO_InitStruct );
*/
        }

}


/**
 * @brief Sampelr initialization
 */

void bsp_sampler_init( void )
{
        bsp_sampler_init_timebase();
        bsp_sampler_init_dma();
        bsp_sampler_init_io();
}


/**
 * @brief Sampler
 */
void bsp_sampler_enable(                        uint16_t *      data,
                                                uint16_t        cnt )
{
        //if( HAL_TIM_PWM_Start( &htim, TIM_CHANNEL_1 ) != HAL_OK)
        //if( HAL_TIM_PWM_Start_DMA( &htim, TIM_CHANNEL_1á uint32_t *pData, uint16_t Length ) != HAL_OK)
        //if( HAL_TIM_PWM_Start( &htim, TIM_CHANNEL_1 ) != HAL_OK)
        //if( HAL_TIM_Base_Start_DMA( &htim, (uint32_t *) data, cnt ) != HAL_OK )
        {
                //app_error( __FILE__, __LINE__ );
        }

        //htim.hdma[ TIM_DMA_ID_UPDATE ]->XferCpltCallback        = TIM_DMAPeriodElapsedCplt;
        //htim->hdma[ TIM_DMA_ID_UPDATE ]->XferErrorCallback      = TIM_DMAError ;


        HAL_DMA_Start_IT(               htim.hdma[ TIM_DMA_ID_UPDATE ],
                        (uint32_t)      &( GPIOA->IDR ),
                        (uint32_t)      data,
                                        cnt );

        __HAL_TIM_ENABLE_DMA(   &htim, TIM_DMA_UPDATE ); //Enable the TIM Update DMA request
        __HAL_TIM_ENABLE(       &htim );                 //Enable the Peripheral
}


/**
 * @brief Sampler
 */
void bsp_sampler_disable( void )
{
        __HAL_TIM_DISABLE( &htim );

        HAL_DMA_Abort_IT( htim.hdma[ TIM_DMA_ID_UPDATE ] );
}


/**
 * @brief Sampler Hook
 */
void bsp_sampler_hook( void )
{

}


void bsp_sampler_dma_isr( void )
{
        HAL_DMA_IRQHandler( htim.hdma[ TIM_DMA_ID_UPDATE ] );
}
