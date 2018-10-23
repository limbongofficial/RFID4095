/**
  * @file    ui_led.h
  * @brief   User Interface - LED Services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef  UI_LED_H
#define  UI_LED_H


#include	<stdbool.h>
#include	<string.h>
#include	"config.h"
#include	"bsp_led.h"
#include	"bsp.h"


#define	UI_LED_FLSH_SHRT_TCKS           ( ((uint32_t) CFG_UI_LED_FLSH_SHRT_mSEC * CFG_UI_SYSTICK_HZ) / 1000 )
#define	UI_LED_FLSH_LONG_TCKS           ( ((uint32_t) CFG_UI_LED_FLSH_LONG_mSEC * CFG_UI_SYSTICK_HZ) / 1000 )


/**
  * @brief   Single LED
  */
typedef    void ( * ui_led_init_t )( void );
typedef    bool ( * ui_led_get_t )( void );
typedef    void ( * ui_led_set_t )(     const   bool    color );


typedef	struct	ui_led_s
{
	ui_led_init_t           init;
	ui_led_set_t            set;
	ui_led_get_t            get;
	size_t                  tick;
} ui_led_t;


bool ui_led_hook(                       ui_led_t *              p );

void ui_led_toggle(                     ui_led_t *              p );

void ui_led_set(                        ui_led_t *              p,
                                const   bool                    mode );

void ui_led_flash(                      ui_led_t *              p,
                                        size_t                  len );


bool ui_led_sts_hook( void );

void ui_led_sts_init( void );

void ui_led_sts_toggle(                 void );

void ui_led_sts_set(            const   bool                    mode );

void ui_led_sts_flash(          const   size_t                  len );


typedef struct  ui_s
{
	ui_led_t        led[1];
} ui_t;

void	ui_led_init(                    ui_led_t *              p );

#endif	//UI_LED_H
