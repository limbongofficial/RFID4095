/**
  * @file    rfid.h
  * @brief   RFID routines header
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef RFID_H
#define RFID_H


#include <stdint.h>
#include "bsp_sampler.h"
#include "bsp_em4095.h"
#include "app_trace.h"


typedef struct  rfid_s
{
        int32_t         level;
        uint64_t        raw;
        //int32_t         test[256];
} rfid_t;



void    rfid_init( void );

void    rfid_recv_start(                        uint16_t *      data,
                                                uint16_t        cnt );

void    rfid_recv_hook(                         rfid_t *        p,
                                                uint16_t *      data,
                                                uint16_t        cnt );


#endif  //RFID_H
