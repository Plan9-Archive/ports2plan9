/* use local header */
#include "signal.h"
/* code conflicts with system header*/
#include <errno.h>

/*
 * BUG: doesn't work
 */

int
sigsuspend(sigset_t *set)
{
	errno = EINVAL;
	return -1;
}
