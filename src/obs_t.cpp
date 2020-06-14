#include "obs_t.h"
#include <malloc.h>

obsd_t::obsd_t()
{
   for (int j = 0; j < NFREQ+ NEXOBS; j++) {
      L[j] = P[j] = 0.0;
      D[j] = 0.0;
      SNR[j] = LLI[j] = code[j] = 0;
   }
}
int obs_t::addobsdata(const obsd_t* d)
{
   data.push_back(*d);
   return 1;
}

int obs_t::count() const
{
   return data.size();
}

int obs_t::obsindex(const gtime_t& time, int sat)
{
   int i, j;

   for (i = 0; i < count(); i++) {
      if (data[i].sat == sat) return i; /* field already exists */
   }
   if (i >= MAXOBS) return -1; /* overflow */

   /* add new field */
   obsd_t obs_tmp;
   obs_tmp.time = time;
   obs_tmp.sat = sat;
   data.push_back(obs_tmp);

   return i;
}
