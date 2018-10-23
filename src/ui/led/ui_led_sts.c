/**
  * @file    ui_led_sts.c
  * @brief   User Interface - Status LED
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include	"ui_led.h"


	ui_led_t        ui_led_sts      =   {   .init           =   bsp_led_sts_init,
	                                        .get            =   bsp_led_sts_get,
	                                        .set            =   bsp_led_sts_set,
	                                        .tick           =   0 };


/**
 * @brief Status LED init.
 */
void ui_led_sts_init( void )
{
        ui_led_init( &ui_led_sts );
}


/**
 * @brief Status LED SysTick Hook.
 */
bool ui_led_sts_hook( void )
{
	bool            resp    =   ui_led_hook( &ui_led_sts );

	return( resp );
}


/**
 * @brief LED Toggle.
 */
void ui_led_sts_toggle( void )
{
	ui_led_toggle( &ui_led_sts );
}


/**
 * @brief LED Control.
 */
void ui_led_sts_set(            const   bool                    mode )
{
	ui_led_set( &ui_led_sts, mode );
}


/**
 * @brief LED Flash.
 */
void ui_led_sts_flash(          const   size_t                  len )
{
	ui_led_flash( &ui_led_sts, len );
}
