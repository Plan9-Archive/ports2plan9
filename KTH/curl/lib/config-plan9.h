/* manually added definitions requested during compilation on Plan9 */

#include "curl_config.h"

#define HAVE_POSIX_STRERROR_R 1

#define TRUE 1
#define FALSE 0

#ifndef EISCONN
#define EISCONN EISCON
#endif

#define FD_SETSIZE LONG_MAX






