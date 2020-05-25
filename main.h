#ifndef MY_MAIN_H
#define MY_MAIN_H

#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t  i8;

typedef float  r32;
typedef double r64;

#define pi 3.14159265358979323846
#define array_count(arr) (sizeof(arr) / sizeof(arr[0]))
#define swap(a, b) \
do \
{  \
u8 temp[sizeof(a) == sizeof(b) ? sizeof(a) : -1]; \
memcpy(temp, &a, sizeof(a)); \
memcpy(&a,   &b, sizeof(a)); \
memcpy(&b, temp, sizeof(a)); \
} while(0)


#include "math.h"

struct model {
    v4 color;
    v3 origin;
    u32 nr_vertices;
    v3 vertices[64];
    u32 nr_indices;
    u32 indices[64];
};

#endif