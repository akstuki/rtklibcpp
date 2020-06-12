#pragma once
#include <vector>
#include "gpstime.h"

#ifndef NFREQ
#define NFREQ       3                   /* number of carrier frequencies */
#endif
#define NFREQGLO    2                   /* number of carrier frequencies of GLONASS */

#ifndef NEXOBS
#define NEXOBS      0                   /* number of extended obs codes */
#endif

#ifdef OBS_100HZ
#define DTTOL       0.005               /* tolerance of time difference (s) */
#else
#define DTTOL       0.025               /* tolerance of time difference (s) */
#endif

class obsd_t {        /* observation data record */
public:
   gtime_t time;       /* receiver sampling time (GPST) */
   unsigned char sat, rcv; /* satellite/receiver number */
   unsigned char SNR[NFREQ + NEXOBS]; /* signal strength (0.25 dBHz) */
   unsigned char LLI[NFREQ + NEXOBS]; /* loss of lock indicator */
   unsigned char code[NFREQ + NEXOBS]; /* code indicator (CODE_???) */
   double L[NFREQ + NEXOBS]; /* observation data carrier-phase (cycle) */
   double P[NFREQ + NEXOBS]; /* observation data pseudorange (m) */
   float  D[NFREQ + NEXOBS]; /* observation data doppler frequency (Hz) */
   bool operator<(const obsd_t& r)  const {
      double tt = time-r.time;
      if (fabs(tt) > DTTOL) return tt < 0 ? -1 : 1;
      if (rcv != r.rcv) return (int)rcv - (int)r.rcv;
      return (int)sat - (int)r.sat;
   }
} ;

class obs_t {
public:
   int addobsdata(const obsd_t* data);

   int n = 0;            /* number of obervation data */
   std::vector<obsd_t> data;
};
