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


typedef struct  app_s
{
        size_t                  tout_msec;
        bool                    evt_id;
} app_t;


void    app_clock_config( void );

void    app_wake_hook( void );

void    app_wake(                               int32_t         tout_msec );

void    app_sleep( void );

void    app_cli(                                cli_t *         p );

void    app_rfid_hook_recv_half( void );

void    app_rfid_hook_recv_full( void );


#endif  //APP_H
