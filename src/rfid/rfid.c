/**
  * @file    rfid.c
  * @brief   RFID routines
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "rfid.h"


/*
999000000000001
0003 8C95 D021 7001h

0000000000000011100011001001010111010000001000010111000000000001b

00000000 00000011 10001100 10010101 11010000 00100001 01110000 00000001b

0000 0000 0000 0011 1000 1100 1001 0101 1101 0000 0010 0001 0111 0000 0000 0001b

LSB first
1000000000001110100001000000101110101001001100011100000000000000b
10000000 00001110 10000100 00001011 10101001 00110001 11000000 00000000b



2369343690657263812
0x20E19988887070C4h
0b0010000011100001100110011000100010001000011100000111000011000100
0b0001000100001110000110001000100010001000011100001100010001000100

*/

/*
985141000867414

0003 7FFB 0369 0E56h

0000000000000011011111111111101100000011011010010000111001010110b

00000000 00000011 01111111 11111011 00000011 01101001 00001110 01010110b


*/


#define RFID_OVRSMPL_FACTOR             8

//#define RFID_HEADER_MASK                ( (uint64_t) 0xF0F0F0F0 )
//#define RFID_HEADER_MASK                ( (uint64_t) 0x00000CCCCCCCCCC3 )
//#define RFID_HEADER_MASK                ( (uint64_t) 0x000003333333333C )

//#define RFID_HEADER_MASK                ( (uint64_t) 0x0F0F0F0F0F0F0FF0 )
#define RFID_HEADER_MASK_U64              ( (uint64_t) 0xF0F0F0F0F0F0F00F )

//#define RFID_HEADER_TRESHOLD            35
//#define RFID_HEADER_TRESHOLD            39
#define RFID_SOF_TRESHOLD               70

/*
static  const   uint8_t         rfid_decoder_bit_manchester[ 256 ] =
{
        0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
        0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00,
        0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
};
*/

/*
static  const   uint8_t         rfid_decoder_bit_diffmanchester[ 256 ] =
{
        0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0,
};
*/

static  const   uint8_t         rfid_decoder_bit_diffmanchester[ 256 ] =
{
        1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1,
};



static  const   uint8_t         rfid_count_of_ones_tbl08[ 256 ] =
{
        #   define B2(n) n,     n+1,     n+1,     n+2
        #   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
        #   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
        B6(0), B6(1), B6(1), B6(2)
};




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





/*
static const unsigned char BitsSetTable256[256] =
{
        #   define B2(n) n,     n+1,     n+1,     n+2
        #   define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
        #   define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
        B6(0), B6(1), B6(1), B6(2)
};

unsigned int v; // count the number of bits set in 32-bit value v
unsigned int c; // c is the total bits set in v

// Option 1:
c = BitsSetTable256[v & 0xff] +
    BitsSetTable256[(v >> 8) & 0xff] +
    BitsSetTable256[(v >> 16) & 0xff] +
    BitsSetTable256[v >> 24];

// Option 2:
unsigned char * p = (unsigned char *) &v;
c = BitsSetTable256[p[0]] +
    BitsSetTable256[p[1]] +
    BitsSetTable256[p[2]] +
    BitsSetTable256[p[3]];

// To initially generate the table algorithmically:
BitsSetTable256[0] = 0;
for (int i = 0; i < 256; i++)
{
  BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];
}
*/

/*
inline
static
uint8_t rfid_count_of_ones_32(                  uint32_t        i )
{
     i  =   i - ((i >> 1) & 0x55555555ul);
     i  =  (i & 0x33333333ul) + ((i >> 2) & 0x33333333ul);
     return( (((i + (i >> 4)) & 0x0F0F0F0Ful) * 0x01010101ul) >> 24 );
}
*/


inline
static
void    rfid_reset(                             rfid_t *        p )
{
        rfid_sts_t *    sts             = &( p->sts );


        sts->complete   =   false;
        sts->sof        =   false;
        p->bit_count    =   0;
        p->bit_idx      =   0;
        p->smpl_idx     =   0;
}


inline
static
bool    rfid_recv_sof(                          rfid_t *        p )
{
        size_t          sum     = 0;


        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 0] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 1] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 2] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 3] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 4] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 5] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 6] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 7] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 8] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[ 9] ^ 0x0F) & 0xFF ];
        sum             +=  rfid_count_of_ones_tbl08[ (p->raw[10] ^ 0xFF) & 0xFF ];

        p->sof[2]       =   p->sof[1];
        p->sof[1]       =   p->sof[0];
        p->sof[0]       =   sum;

        if(     p->sof[1] > RFID_SOF_TRESHOLD           &&
                p->sof[1] > p->sof[0]                   &&
                p->sof[1] > p->sof[2]                     )
        {
                return( true );
        }

        return( false );
}


inline
static
bool    rfid_recv_id(                           rfid_t *        p )
{
        if( p->smpl_idx < RFID_OVRSMPL_FACTOR )
        {
                p->smpl_idx++;
                return( false );
        }

        p->smpl_idx     =   0;


        if( p->bit_idx >= 9  )
        {
                p->bit_idx      =   0;
                return( false );
        }


        p->bit_idx++;
        p->tag.id       >>= 1;
        p->tag.id       |=  rfid_decoder_bit_diffmanchester[ 0xFF & (p->raw[10] ^ 0xFF ) ] ? 0x80000000 : 0x00000000;

        if( p->bit_count++ < 64 )
        {
                return( false );
        }

        p->sts.sof      =   0;
        p->sts.id       =   0;
        p->bit_count    =   0;

        return( true );
}


inline
static
bool    rfid_recv(                              rfid_t *        p )
{
        rfid_sts_t *    sts             = &( p->sts );


        if( sts->sof == false )
        {
                sts->sof        =   rfid_recv_sof( p );

                if( sts->sof == true )
                {
                        p->bit_count    =   0;
                }

                return( false );
        }


        if( sts->id == false )
        {
                sts->id =   rfid_recv_id( p );

                return( false );
        }


        return( true );
}


bool    rfid_recv_hook(                         rfid_t *        p,
                                                uint16_t *      data,
                                                uint16_t        cnt )
{
        rfid_sts_t *    sts             = &( p->sts );
        bool            ready;


        while( cnt-- )
        {
                p->raw[ 0]      >>=     1;
                p->raw[ 0]      |=      p->raw[1] & 1 ? 0x80 : 0x00;

                p->raw[ 1]      >>=     1;
                p->raw[ 1]      |=      p->raw[2] & 1 ? 0x80 : 0x00;

                p->raw[ 2]      >>=     1;
                p->raw[ 2]      |=      p->raw[3] & 1 ? 0x80 : 0x00;

                p->raw[ 3]      >>=     1;
                p->raw[ 3]      |=      p->raw[4] & 1 ? 0x80 : 0x00;

                p->raw[ 4]      >>=     1;
                p->raw[ 4]      |=      p->raw[5] & 1 ? 0x80 : 0x00;

                p->raw[ 5]      >>=     1;
                p->raw[ 5]      |=      p->raw[6] & 1 ? 0x80 : 0x00;

                p->raw[ 6]      >>=     1;
                p->raw[ 6]      |=      p->raw[7] & 1 ? 0x80 : 0x00;

                p->raw[ 7]      >>=     1;
                p->raw[ 7]      |=      p->raw[8] & 1 ? 0x80 : 0x00;

                p->raw[ 8]      >>=     1;
                p->raw[ 8]      |=      p->raw[9] & 1 ? 0x80 : 0x00;

                p->raw[ 9]      >>=     1;
                p->raw[ 9]      |=      p->raw[10] & 1 ? 0x80 : 0x00;

                p->raw[10]      >>=     1;
                p->raw[10]      |=      *data++ & (1 << 7) ? 0x80: 0x00;


                ready   =   rfid_recv( p );

                if( ready )
                {
                        //ui_led_sts_flash( UI_LED_FLSH_SHRT_TCKS );
                        sts->sof        =   false;
                        sts->id         =   false;
                        break;
                }
        }

        return( ready );
}
