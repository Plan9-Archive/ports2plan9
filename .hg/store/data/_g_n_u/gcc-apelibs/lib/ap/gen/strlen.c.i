         R   Q       ,��������mdIk��:8y�g�*#!�            u#include <string.h>

size_t
strlen(const char *s)
{

	return strchr(s, 0) - s;
}
