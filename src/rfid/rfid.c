/**
  * @file    rfid.c
  * @brief   RFID routines
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "rfid.h"


//#define RFID_HEADER_MASK                ( (uint64_t) 0xF0F0F0F0 )
//#define RFID_HEADER_MASK                ( (uint64_t) 0x00000CCCCCCCCCC3 )
//#define RFID_HEADER_MASK                ( (uint64_t) 0x000003333333333C )

//#define RFID_HEADER_MASK                ( (uint64_t) 0x0F0F0F0F0F0F0FF0 )
#define RFID_HEADER_MASK                ( (uint64_t) 0x0F0F0F0F0F0F0F0F )


//#define RFID_HEADER_TRESHOLD            35
#define RFID_HEADER_TRESHOLD            39


void    rfid_init( void )
{
        bsp_em4095_init();
        bsp_sampler_init();
}


void    rfid_recv_start(                        uint16_t *      data,
                                                uint16_t        cnt )
{
        bsp_em4095_set_sleep( false );
        bsp_em4095_set_mode_recv();
        bsp_sampler_enable( data, cnt );
}


void    rfid_recv_hook(                         rfid_t *        p,
                                                uint16_t *      data,
                                                uint16_t        cnt )
{
        bool            sample;
        uint64_t        sum;

        while( cnt-- )
        {
                sample          =   *data++ & (1 << 6) ? true : false;
                p->raw          <<= 1;
                p->raw          |=  sample ? 1 : 0;
                sum             =   p->raw ^ RFID_HEADER_MASK;
                //sum             =   (p->raw & (uint64_t) 0x00000FFFFFFFFFFF)^ RFID_HEADER_MASK;

                p->level        =   0;

                for( int i = 0; i < 64; i++ )
                {
                        p->level        +=  (sum & 1) ? 1 : -1;
                        sum             >>= 1;
                }

                //if( p->level > 31 || p->level < -31 )
                //if( p->level > RFID_HEADER_TRESHOLD || p->level < -RFID_HEADER_TRESHOLD )
                if( p->level > RFID_HEADER_TRESHOLD )
                //if( p->level < -RFID_HEADER_TRESHOLD )
                {
                        ui_led_sts_flash( UI_LED_FLSH_SHRT_TCKS );
                }
        }
}
