/**
  * @file    bsp_led.h
  * @brief   Board Support Package - LED services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef  BSP_LED_H
#define  BSP_LED_H


#include	<stdbool.h>


void    bsp_led_sts_init( void );

bool    bsp_led_sts_get( void );

void	bsp_led_sts_set(                const   bool            color );


#endif	//BSP_LED_H
