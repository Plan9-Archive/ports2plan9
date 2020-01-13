/* wrapper header for libnbcompat */

#include "../nbcompat.h"
#undef HAVE_SYS_QUEUE_H
#include "../nbcompat/queue.h"
#define HAVE_SYS_QUEUE_H

