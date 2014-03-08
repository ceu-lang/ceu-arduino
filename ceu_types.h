#ifndef _CEU_TYPES_H
#define _CEU_TYPES_H

#include <stdint.h>

#ifndef CEU_WORD
#define CEU_WORD
typedef unsigned int  word;
#endif

typedef unsigned int  uint;

#ifndef CEU_BYTE
#define CEU_BYTE
typedef unsigned char byte;
#endif

typedef int64_t  s64;
typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t    s8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t   u8;

typedef float    f32;
typedef double   f64;

#endif
