/**
  * @file    app_clock.c
  * @brief   Configure MCU clock tree
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include <stdbool.h>
#include "app.h"
#include "bsp.h"


void    app_clock_config( void )
{
        RCC_OscInitTypeDef              osc;
        RCC_ClkInitTypeDef              clk;
        RCC_PeriphCLKInitTypeDef        pck;


        osc.OscillatorType      =   RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
        osc.HSEState            =   RCC_HSE_ON;
        osc.HSI48State          =   RCC_HSI48_ON;
        osc.PLL.PLLState        =   RCC_PLL_ON;
        osc.PLL.PLLSource       =   RCC_PLLSOURCE_HSE;
        osc.PLL.PLLMUL          =   RCC_PLL_MUL12;
        osc.PLL.PREDIV          =   RCC_PREDIV_DIV4;

        if( HAL_RCC_OscConfig( &osc ) != HAL_OK )
        {
                app_error( __FILE__, __LINE__ );
        }


        clk.ClockType           =   RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
        clk.SYSCLKSource        =   RCC_SYSCLKSOURCE_PLLCLK;
        clk.AHBCLKDivider       =   RCC_SYSCLK_DIV1;
        clk.APB1CLKDivider      =   RCC_HCLK_DIV1;

        if( HAL_RCC_ClockConfig( &clk, FLASH_LATENCY_1 ) != HAL_OK )
        {
                app_error( __FILE__, __LINE__ );
        }


        pck.PeriphClockSelection        =   RCC_PERIPHCLK_USB;
        pck.UsbClockSelection           =   RCC_USBCLKSOURCE_HSI48;

        if( HAL_RCCEx_PeriphCLKConfig( &pck ) != HAL_OK )
        {
                app_error( __FILE__, __LINE__ );
        }


        HAL_SYSTICK_Config( HAL_RCC_GetHCLKFreq() / 1000 );
        HAL_SYSTICK_CLKSourceConfig( SYSTICK_CLKSOURCE_HCLK );

        HAL_NVIC_SetPriority( SysTick_IRQn, 0, 0 );
}
