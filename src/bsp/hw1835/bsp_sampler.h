/**
  * @file    bsp_sampler.h
  * @brief   Board Support Package - RFID Sampler services
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef  BSP_SAMPLER_H
#define  BSP_SAMPLER_H


#include <stdint.h>
#include "stm32f0xx_hal.h"





void bsp_sampler_init( void );

void bsp_sampler_enable(                        uint16_t *      data,
                                                uint16_t        cnt );

void bsp_sampler_disable( void );

void bsp_sampler_hook( void );

//void bsp_sampler_half_hook( void );

//void bsp_sampler_full_hook( void );

void bsp_sampler_dma_isr( void );


#endif	//BSP_SAMPLER_H
