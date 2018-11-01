/**
  * @file    bsp_em4095.h
  * @brief   Board Support Package - EM4095 routines
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include	<string.h>
#include	"bsp.h"
#include	"bsp_em4095.h"


/**
 * @brief LED pin initialization
 */
void bsp_em4095_init( void )
{
        GPIO_InitTypeDef        pin_shdn        =   {    .Pin       =    GPIO_PIN_2,
	                                                 .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                                 .Pull      =    GPIO_NOPULL,
	                                                 .Speed     =    GPIO_SPEED_FREQ_LOW };

        GPIO_InitTypeDef        pin_mode        =   {    .Pin       =    GPIO_PIN_6,
	                                                 .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                                 .Pull      =    GPIO_NOPULL,
	                                                 .Speed     =    GPIO_SPEED_FREQ_LOW };

        GPIO_InitTypeDef        pin_clk         =   {    .Pin       =    GPIO_PIN_5,
	                                                 .Mode      =    GPIO_MODE_INPUT,
	                                                 .Pull      =    GPIO_NOPULL,
	                                                 .Speed     =    GPIO_SPEED_FREQ_LOW };

        GPIO_InitTypeDef        pin_data        =   {    .Pin       =    GPIO_PIN_7,
	                                                 .Mode      =    GPIO_MODE_INPUT,
	                                                 .Pull      =    GPIO_NOPULL,
	                                                 .Speed     =    GPIO_SPEED_FREQ_LOW };


	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_Init( GPIOA, &pin_clk          );
	HAL_GPIO_Init( GPIOA, &pin_data         );
	HAL_GPIO_Init( GPIOA, &pin_shdn         );
	HAL_GPIO_Init( GPIOA, &pin_mode         );
}


/**
 * @brief Pin Sleep Control
 */
void	bsp_em4095_set_sleep(           const   bool            b )
{
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_2,  b ? GPIO_PIN_SET : GPIO_PIN_RESET );
}


/**
 * @brief Pin Mode Control
 */
static
void    bsp_em4095_set_mode(            const   bool            b )
{
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_6,  b ? GPIO_PIN_SET : GPIO_PIN_RESET );
	//return( HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_4 ) ? true : false );
}


/**
 * @brief Xmit Mode
 */
void    bsp_em4095_set_mode_xmit( void )
{
        bsp_em4095_set_mode( true );
}


/**
 * @brief Recv Mode
 */
void    bsp_em4095_set_mode_recv( void )
{
        bsp_em4095_set_mode( false );
}
