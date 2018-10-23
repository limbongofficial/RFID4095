/**
  * @file    ui_led.c
  * @brief   User Interface - LED Services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include	"ui_led.h"


/**
 * @brief LED SysTick Hook.
 */
bool ui_led_hook(                       ui_led_t *              p )
{
	bool            resp            =   false;

	if( p->tick > 0 )
	{
		p->tick--;

		if( p->tick == 0 )
		{
			ui_led_toggle( p );
			resp    =   true;
		}
	}

	return( resp );
}


/**
 * @brief LED Toggle.
 */
void ui_led_toggle(                     ui_led_t *              p )
{
	const   bool    led_sts =   p->get();

	p->set( led_sts ? false : true );
}


/**
 * @brief LED Control.
 */
void ui_led_set(                        ui_led_t *              p,
                                const   bool                    mode )
{
	p->set( mode );
}


/**
 * @brief LED Flash.
 */
void ui_led_flash(                      ui_led_t *              p,
                                        size_t                  len )
{
	if( p->tick == 0 )
	{
		ui_led_toggle( p );
	}

	p->tick         =   len;
}


void	ui_led_init(                    ui_led_t *              p )
{
	p->init();
}
