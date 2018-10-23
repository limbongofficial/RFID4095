/**
  * @file    bsp_led.h
  * @brief   Board Support Package - LED services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef  BSP_EM4095_H
#define  BSP_EM4095_H


#include	<stdbool.h>


void    bsp_em4095_init( void );

void	bsp_em4095_set_sleep(           const   bool            b );

void    bsp_em4095_set_mode_xmit( void );

void    bsp_em4095_set_mode_recv( void );


#endif	//BSP_EM4095_H
