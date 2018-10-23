/**
  * @file    app_error.h
  * @brief   Application Error Routine
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_ERROR_H
#define APP_ERROR_H


#include "app_trace.h"

static
void    app_error(                      const   char *          file,
                                        const   int             line )
{
        #if defined( NDEBUG )
        bsp_system_reset();
        #else
        APP_TRACE( "error: line %d @ %s\n", line, file );
        while( 1 );
        #endif
}


#endif  //APP_ERROR_H
