/**
  * @file    app.h
  * @brief   Main Application Header
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_H
#define APP_H


#include "app_error.h"
#include "cli.h"
#include "rfid.h"
#include "ui_led.h"


typedef struct  app_sts_s
{
        bool    msg             :       1;
	bool	wake            :       1;
	bool	                :       0;
} app_sts_t;

typedef struct  app_s
{
        size_t                  tout_msec;
        //bool                    evt_id;
        //bool                    evt_rfid;
        app_sts_t               sts;
} app_t;

/*
static  inline
uint32_t numberOfSetBits_1(                     uint32_t        v )
{
                        //uint32_t        v; // count bits set in this (32-bit value)
                        uint32_t        c; // store the total here
        static  const   int32_t         S[] = {1, 2, 4, 8, 16}; // Magic Binary Numbers
        static  const   int32_t         B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};


        c       = v - ((v >> 1) & B[0]);
        c       = ((c >> S[1]) & B[1]) + (c & B[1]);
        c       = ((c >> S[2]) + c) & B[2];
        c       = ((c >> S[3]) + c) & B[3];
        c       = ((c >> S[4]) + c) & B[4];

        return( c );
}
*/
/*
static  inline
uint32_t        numberOfSetBits(                        uint32_t        i )
{
     // Java: use >>> instead of >>
     // C or C++: use uint32_t
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}
*/

void    app_utility( void );

void    app_clock_config( void );

void    app_wake_hook( void );

void    app_wake(                               int32_t         tout_msec );

void    app_sleep( void );

void    app_cli(                                cli_t *         p );

void    app_rfid_hook_recv_half( void );

void    app_rfid_hook_recv_full( void );


#endif  //APP_H
