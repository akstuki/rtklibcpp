#pragma once

#include <time.h>

#ifndef _GPS_TIME_
#define _GPS_TIME_
typedef struct {        /* time struct */
   time_t time = 0;        /* time (s) expressed by standard time_t */
   double sec = 0.0;         /* fraction of second under 1 s */
} gtime_t;
#endif
