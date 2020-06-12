#include "obs_t.h"
#include <malloc.h>

int obs_t::addobsdata(const obsd_t* d)
{
   data.push_back(*d);
   ++n;
   return 1;
}
