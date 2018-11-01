/**
  * @file    app.c
  * @brief   Main Application
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "stm32f0xx_hal.h"
#include "app.h"


#define RFID_RAW_SIZEOF         128


        uint16_t                rfid_raw[2][ RFID_RAW_SIZEOF ];
        rfid_t                  rfid;
        cli_t                   cli;
        app_t                   app;


void    app_rfid_hook_recv_half( void )
{
        app.sts.msg     =   rfid_recv_hook( &rfid, rfid_raw[1], RFID_RAW_SIZEOF );
}


void    app_rfid_hook_recv_full( void )
{
        app.sts.msg     =   rfid_recv_hook( &rfid, rfid_raw[1], RFID_RAW_SIZEOF );
}


void    app_wake(                               int32_t         tout_msec )
{
        app.tout_msec   =   tout_msec;
        app.sts.wake    =   true;
        ui_led_sts_set( false );
}


void    app_sleep( void )
{
        app.tout_msec   =   0;
        ui_led_sts_set( true );
}


void    app_wake_hook( void )
{
        if( app.tout_msec > 0 )
        {
                app.tout_msec--;

                if( app.tout_msec == 0 )
                {
                        ui_led_sts_set( true );
                }
        }
}


/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main( void )
{
        uint16_t        id;
        char            str[16];

        app_clock_config();

        //app_utility();

        HAL_Init();

        ui_led_sts_init();
        ui_led_sts_set( true );
        MX_USB_DEVICE_Init();
        rfid_init();
        rfid_recv_start( rfid_raw[0], RFID_RAW_SIZEOF*2 );


        while( 1 )
        {
                if( app.sts.msg )
                {
                        app.sts.msg     =   false;
                        ui_led_sts_flash( UI_LED_FLSH_SHRT_TCKS );
                        //printf( "%016X\r\n", rfid.tag.id );
                        //printf( "%016X%016X\r\n", rfid.tag.id >> 16, (rfid.tag.id & 0xFFFF) );
                        __disable_interrupt();
                        //printf( "%08X %08X %08X %08X\r\n", rfid.tag.id >> 48, rfid.tag.id >> 32, rfid.tag.id >> 16, (rfid.tag.id & 0xFFFF) );

/*
                        id      =   rfid.tag.id >> 48;
                        printf( "%04X ", id );

                        id      =   rfid.tag.id >> 32;
                        printf( "%04X ", id );

                        id      =   rfid.tag.id >> 16;
                        printf( "%04X ", id );

                        id      =   rfid.tag.id >>  0;
                        printf( "%04X ", id );

                        printf( "\n" );
*/
                        __enable_interrupt();
                }

/*
                HAL_Delay( 1000 );

                if( app.evt_id )
                {
                        app.evt_id      =   false;
                        snprintf( id_str, sizeof(id_str), "%08X\r\n", id++ );
                        cli_send( id_str );
                }
*/
        }
}
