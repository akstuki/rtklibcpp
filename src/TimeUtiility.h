#pragma once

#include <time.h>

#ifndef PI
#define PI          3.1415926535897932  /* pi */
#endif

class gtime_t {
public:
   gtime_t(int week, double sec);
   time_t time=0;        /* time (s) expressed by standard time_t */
   double sec=0.0;         /* fraction of second under 1 s */
   
   void time2epoch(double* ep) const;
};

/* time and string functions -------------------------------------------------*/
double  str2num(const char* s, int i, int n);
int     str2time(const char* s, int i, int n, gtime_t* t);
void    time2str(gtime_t t, char* str, int n);
gtime_t epoch2time(const double* ep);
void    time2epoch(gtime_t t, double* ep);
gtime_t gpst2time(int week, double sec);
double  time2gpst(gtime_t t, int* week);
gtime_t gst2time(int week, double sec);
double  time2gst(gtime_t t, int* week);
gtime_t bdt2time(int week, double sec);
double  time2bdt(gtime_t t, int* week);
char* time_str(gtime_t t, int n);

gtime_t timeadd(gtime_t t, double sec);
gtime_t operator+(const gtime_t& t, double sec);
gtime_t operator+(double sec, const gtime_t& t);
double  timediff(gtime_t t1, gtime_t t2);
double operator-(const gtime_t& t1, const gtime_t& t2);
gtime_t gpst2utc(gtime_t t);
gtime_t utc2gpst(gtime_t t);
gtime_t gpst2bdt(gtime_t t);
gtime_t bdt2gpst(gtime_t t);
gtime_t timeget(void);
void    timeset(gtime_t t);
double  time2doy(gtime_t t);
double  utc2gmst(gtime_t t, double ut1_utc);
int read_leaps(const char* file);
int adjgpsweek(int week);
unsigned int tickget(void);
void sleepms(int ms);


