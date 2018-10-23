/**
  * @file    cli_hook.c
  * @brief   Command Line Interface Hook
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include <stdlib.h>
#include "cli.h"


static const cli_cmd_t cli_cmd[] =
{
	{ CLI_CMD_IDX_WAKE,     "wake",    }, { CLI_CMD_IDX_W,     "w",       },
	{ CLI_CMD_IDX_SLEEP,    "sleep",   }, { CLI_CMD_IDX_S,     "s",       },
	{ CLI_CMD_IDX_RESET,    "reset",   }, { CLI_CMD_IDX_R,     "r",       },
	//{ CLI_CMD_IDX_CONFIG,   "config",  }, { CLI_CMD_IDX_C,     "c",       },
	//{ CLI_CMD_IDX_BAUD,     "baud",    }, { CLI_CMD_IDX_B,     "b",       },
	//{ CLI_CMD_IDX_HELP,     "help",    }, { CLI_CMD_IDX_H,     "h",       },
	{ CLI_CMD_IDX_INVALID,	"invalid", },
};


/**
 * @brief CLI hook command.
 */
static
bool cli_hook_cmd(                              cli_t *         p )
{
		bool	resp	=    false;
		size_t	idx;
	const	size_t	idx_max	=    sizeof(cli_cmd) / sizeof(cli_cmd_t);
	const	size_t	buf_max	=    sizeof(p->buf) / sizeof(cli_str_t);


	if( p->state == CLI_STATE_CMD )
        {
		for( idx = 0; idx < idx_max - 1; idx++ )
                {
			int miss        =   strncmp( cli_cmd[idx].str, p->buf, buf_max );

			if( miss == 0 )
                        {
				break;
			}
		}

		p->cmd_idx      =   ( cli_cmd_idx_t ) idx;
		p->len          =   0;
		p->state        =   CLI_STATE_ARG;
	}

	return resp;
}


/**
 * @brief CLI hook argument.
 */
static
bool cli_hook_arg(                              cli_t *         p )
{
        bool    resp;


	switch( p->state )
        {
                case CLI_STATE_ARG:
                {
                        p->arg          =   atoi( p->buf );
                        resp            =   true;
                        break;
                }

                case CLI_STATE_CMD:
                {
                        cli_hook_cmd( p );
                        resp            =   true;
                        break;
                }

                default:
                {
                        resp            =   false;
                        break;
                }
	}

	p->state        =   CLI_STATE_CMD;
	p->len          =   0;

	return( resp );
}


/**
 * @brief CLI hook.
 */
bool cli_hook(                                  cli_t *         p,
                                                char            c )
{
	bool            resp;
	const   size_t  buf_size        = sizeof(p->buf) / sizeof(cli_str_t);


	switch( c )
        {
                case    ',':
                {
                        *(p->buf + p->len)      = '\0';
                        resp                    = cli_hook_cmd( p );
                        break;
                }

                case    '\r':
                {
                        // TODO: p->arg may still containe previous arg value
                        *(p->buf + p->len)      = '\0';
                        resp                    = cli_hook_arg(p);
                        break;
                }

                default:
                {
                        if( p->len < buf_size )
                        {
                                *(p->buf + p->len++)    = c;
                        }
                        resp                    = false;
                        break;
                }
	}

	return resp;
}
