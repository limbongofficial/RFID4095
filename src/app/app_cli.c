/**
  * @file    app_cli.c
  * @brief   App Command Line Interface
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdio.h>
#include <stdbool.h>
#include "usbd_cdc_if.h"
#include "bsp.h"
#include "app.h"


/**
 * @brief CLI command.
 */
void    app_cli(                                cli_t *         p )
{
        switch( p->cmd_idx )
        {
                case CLI_CMD_IDX_RESET:
                case CLI_CMD_IDX_R:
                        cli_send( "OK\n\r" );
                        break;

                case CLI_CMD_IDX_WAKE:
                case CLI_CMD_IDX_W:
                        app_wake( p->arg );
                        cli_send( "OK\n\r" );
                        break;

                case CLI_CMD_IDX_SLEEP:
                case CLI_CMD_IDX_S:
                        app_sleep();
                        cli_send( "OK\n\r" );
                        break;

                case CLI_CMD_IDX_INVALID:
                default:
                        cli_send( "ERROR\n\r" );
                        break;
        }
}
