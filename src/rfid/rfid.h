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


typedef enum    rfid_state_e
{
        RFID_STATE_IDLE         = 0,
        RFID_STATE_RECV,
} rfid_state_t;

typedef struct  rfid_sts_s
{
        bool                    sof;
        bool                    id;
        bool                    crc;
        bool                    complete;
} rfid_sts_t;

typedef struct  rfid_tag_s
{
        uint64_t                id;
        uint16_t                crc;
} rfid_tag_t;

typedef struct  rfid_s
{
        //rfid_state_t            state;
        rfid_sts_t              sts;
        uint8_t                 raw[11];
        int32_t                 sof[3];
        uint8_t                 group[8];
        rfid_tag_t              tag;
        //size_t                  cnt_smpl;
        size_t                  smpl_idx;
        size_t                  bit_idx;
        size_t                  bit_count;
        //size_t                  idx;
} rfid_t;


void    rfid_init( void );

void    rfid_recv_start(                        uint16_t *      data,
                                                uint16_t        cnt );

bool    rfid_recv_hook(                         rfid_t *        p,
                                                uint16_t *      data,
                                                uint16_t        cnt );


#endif  //RFID_H
