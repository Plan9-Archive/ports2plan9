/* wrapper header for libnbcompat */

#include "nbcompat.h"
#undef HAVE_ERR_H
#include "nbcompat/err.h"
#define HAVE_ERR_H

