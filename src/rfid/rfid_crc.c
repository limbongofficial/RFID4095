/**
  * @file    rfid_crc.c
  * @brief   RFID CRC Calculate
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "rfid.h"


uint16_t rfid_crc(                      const   uint8_t *       data,
                                                size_t          size    )
{
        uint16_t        carry;
        uint16_t        crc     = 0xFFFF;


        while( size-- )
        {
                unsigned j = 8;

                crc     ^= (uint16_t) *data++;

                while(j--)
                {
                        carry   =   crc & 0x0001;
                        crc     >>= 1;

                        if( carry )
                        {
                                crc     ^= 0xA001;
                        }
                }
        }

        return( (crc >> 8) | (crc << 8) );
}
