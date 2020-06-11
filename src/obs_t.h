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

typedef struct {        /* observation data record */
   gtime_t time;       /* receiver sampling time (GPST) */
   unsigned char sat, rcv; /* satellite/receiver number */
   unsigned char SNR[NFREQ + NEXOBS]; /* signal strength (0.25 dBHz) */
   unsigned char LLI[NFREQ + NEXOBS]; /* loss of lock indicator */
   unsigned char code[NFREQ + NEXOBS]; /* code indicator (CODE_???) */
   double L[NFREQ + NEXOBS]; /* observation data carrier-phase (cycle) */
   double P[NFREQ + NEXOBS]; /* observation data pseudorange (m) */
   float  D[NFREQ + NEXOBS]; /* observation data doppler frequency (Hz) */
} obsd_t;

class obs_t {
public:
   int addobsdata(const obsd_t* data);

   int n = 0;            /* number of obervation data */
   int nmax = 0;         /* number of obervation data/allocated */
   obsd_t* data = 0;     /* observation data records */
   std::vector<obsd_t> _data;
};
