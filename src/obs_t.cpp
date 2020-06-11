#include "obs_t.h"
#include <malloc.h>

int obs_t::addobsdata(const obsd_t* d)
{
   _data.push_back(*d);
   data = &_data[0];
   n++;
   return 1;
}
