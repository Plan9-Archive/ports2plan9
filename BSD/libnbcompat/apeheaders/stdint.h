/*
*This header wrapper is included in libnbcompat
*libnbcompat does not provide this functionality
*but many packages using libnbcompat will assume 
*the presence of stdint.h
*/

#include <inttypes.h>
#define u_int32_t uint32_t
#define u_int16_t uint16_t
#define u_long unsigned long
#define u_int unsigned int
#define u_char uint8_t
#define u_short uint16_t
#define double long





