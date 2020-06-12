#pragma once

#include <time.h>

#ifndef _GPS_TIME_
#define _GPS_TIME_
typedef struct {        /* time struct */
   time_t time = 0;        /* time (s) expressed by standard time_t */
   double sec = 0.0;         /* fraction of second under 1 s */
} gtime_t;

gtime_t timeadd(gtime_t t, double sec);
gtime_t operator+(const gtime_t& t, double sec);
gtime_t operator+(double sec, const gtime_t& t);
double  timediff(gtime_t t1, gtime_t t2);
double operator-(const gtime_t& t1, const gtime_t& t2);
#endif
