/**
  * @file    cli.h
  * @brief   Command Line Interface
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef  CLI_H
#define  CLI_H


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"

typedef char cli_str_t;

typedef enum    cli_cmd_idx_e
{
        CLI_CMD_IDX_RESET = 0,
        CLI_CMD_IDX_R,
        CLI_CMD_IDX_WAKE,
        CLI_CMD_IDX_W,
        CLI_CMD_IDX_SLEEP,
        CLI_CMD_IDX_S,
        //CLI_CMD_IDX_CONFIG,
        //CLI_CMD_IDX_C,
        //CLI_CMD_IDX_BAUD,
        //CLI_CMD_IDX_B,
	//CLI_CMD_IDX_HELP,
	//CLI_CMD_IDX_H,
	CLI_CMD_IDX_INVALID,
} cli_cmd_idx_t;


typedef enum    cli_state_e
{
	CLI_STATE_CMD = 0,
	CLI_STATE_ARG,
} cli_state_t;

typedef struct  cli_s
{
	cli_state_t     state;
	cli_cmd_idx_t   cmd_idx;
	size_t          len;
	int32_t         arg;
	cli_str_t       buf[ CFG_CLI_STRLEN_OCT ];
} cli_t;

typedef struct  cli_cmd_s
{
	cli_cmd_idx_t idx;
	cli_str_t *str;
} cli_cmd_t;


void cli_init( cli_t *p );

bool cli_hook( cli_t *p, char c );

void    cli_send(                       const   char *          str );


#endif	//CLI_H
