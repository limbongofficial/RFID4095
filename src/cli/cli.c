/**
  * @file    cli.c
  * @brief   Command Line Interface
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include "usbd_cdc_if.h"

//#include "bsp_uart.h"
#include "cli.h"


/**
 * @brief CLI initialization.
 */
void    cli_init(                               cli_t *         p )
{
	memset( p, 0, sizeof(cli_t) );
}


/**
 * @brief CLI send.
 */
void    cli_send(                       const   char *          str )
{
        size_t          len     = strlen( str );
        size_t          tout    = 10;
        uint8_t         resp;


        if( len > CFG_CLI_STRLEN_OCT )
        {
                len     =   CFG_CLI_STRLEN_OCT;
        }

        do
        {
                resp    =   CDC_Transmit_FS( (uint8_t *) str, len );

                if( tout-- )
                {
                        break;
                }
        }
        while( resp != USBD_OK );
}
