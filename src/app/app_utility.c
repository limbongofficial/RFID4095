/**
  * @file    app_utility.c
  * @brief   Utility
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#include "app.h"


void    app_utility( void )
{
/*
        int     num_of_1;

        for( int i = 0; i < 256; i++ )
        {
                num_of_1        = numberOfSetBits( i );
                printf( "%04X:\t%5d\n", i, num_of_1 );
        }
*/

/*
        for( int i = 0; i < 256; i++ )
        {
                printf( "%04X:\t%5d\n", i, BitsSetTable256[ i ] );
        }
*/


        uint8_t         temp            = 0;
        int8_t          sum             = 0;
        size_t          count_of_0      = 0;
        size_t          count_of_2      = 0;
        size_t          count_of_4      = 0;
        size_t          count_of_6      = 0;
        size_t          count_of_8      = 0;
        size_t          count_of_err    = 0;


        for( int i = 0; i < 256; i++ )
        {
                temp    = i ^ 0x0F;
                sum     = 0;

                for( int j = 1; j < 256; j = j << 1 )
                {
                        sum     +=  (temp & j) ? 1 : -1;
                }

                switch( sum )
                {
                        case 0:
                                count_of_0++;
                                break;

                        case 2:
                        case -2:
                                count_of_2++;
                                break;

                        case 4:
                        case -4:
                                count_of_4++;
                                break;

                        case 6:
                        case -6:
                                count_of_6++;
                                break;

                        case 8:
                        case -8:
                                count_of_8++;
                                break;

                        default:
                                count_of_err++;
                                break;

                }

                //printf( "0x%02X, ", sum > 0 ? 1 : 0 );
                //printf( "%2d, ", sum );
                //printf( "%2d, ", sum >> 1 );
                //printf( "%d, ", sum * sum );
                //printf( "%d, ", (sum * sum) / 4 );
                //printf( "%d, ", (sum * sum) / 4 >= 4 ? 1 : 0 );

                printf( "%d, ", (sum > 3) || (sum < -3) ? 0 : 1 );


                if( (i & 0x0F) == 0x0F )
                {
                        printf( "\n" );
                }
        }

        printf( "count_of_0:\t%d\n",    count_of_0 );
        printf( "count_of_2:\t%d\n",    count_of_2 );
        printf( "count_of_4:\t%d\n",    count_of_4 );
        printf( "count_of_6:\t%d\n",    count_of_6 );
        printf( "count_of_8:\t%d\n",    count_of_8 );
        printf( "count_of_err:\t%d\n",  count_of_err );


        while( 1 );
}
