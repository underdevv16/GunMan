#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

#endif

// This #ifndef and #endif are known as 'Include guards' and are used to make sure that the same thing is not
// included multiple times by the compiler at complie time.