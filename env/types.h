#include <stdint.h>

typedef void none;

#ifndef __cplusplus
typedef unsigned char bool;
#endif
typedef unsigned char byte;
typedef unsigned int  uint;

//typedef ssize_t  ssize;       // no support in Arduino
typedef size_t   usize;

typedef int8_t    s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uint8_t   u8;
#ifndef __AVR
typedef uint16_t u16;         // already defined in "USBAPI.h"
#endif
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    real;
typedef float    r32;
typedef double   r64;
