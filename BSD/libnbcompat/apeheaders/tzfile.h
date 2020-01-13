/* header wrapper for libnbcompat */

#include "nbcompat.h"
#undef HAVE_TZFILE_H
#include "nbcompat/tzfile.h"
#define HAVE_TZFILE_H