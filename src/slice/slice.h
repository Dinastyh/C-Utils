#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>
#include <string.h>

#include "aliases.h"
#include "colors.h"

#define SLICE_DEF(type, name)                                                  \
  struct slice_##name {                                                        \
    type *data;                                                                \
    size_t len;                                                                \
  };

struct slice_void {
  size_t len;
  void *data;
};

SLICE_DEF(u8, u8)
SLICE_DEF(u32, u32)
SLICE_DEF(u64, u64)
SLICE_DEF(i64, i64)
SLICE_DEF(int, int)
SLICE_DEF(char *, string)
SLICE_DEF(double, double)
SLICE_DEF(bool, bool)
SLICE_DEF(size_t, size_t)

static inline void __nop(void) { return; }

#define SLICE_MAKE(_type, _data, _len) ((_type){.data = _data, .len = _len})

#define SLICE_VOID(slice)                                                      \
  (struct slice_void) {                                                        \
    .len = sizeof(*((slice).data)) * (slice).len, .data = (slice).data         \
  }

#define SLICE_SUB(slice, start, end)                                           \
  ((__typeof__(slice)){.data = (slice).data + (start), .len = (end) - (start)})

#define SLICE_SHIFT(slice, amount)                                             \
  ((__typeof__(slice)){.data = (slice).data + (amount),                        \
                       .len = (slice).len - (amount)})

#define SLICE_MEMSET(slice, val)                                               \
  do {                                                                         \
    __typeof__(slice) S = (slice);                                             \
    memset((S).data, val, (S).len);                                            \
  } while (0)

#define SLICE_MEMCPY(dst, src)                                                 \
  do {                                                                         \
    __typeof__(src) SRC = (src);                                               \
    __typeof__(dst) DST = (dst);                                               \
    memcpy((DST).data, (SRC).data, (SRC).len);                                 \
  } while (0)

#define SLICE_EQUAL(dst, src)                                                  \
  ((((src).len == (dst).len &&                                                 \
             (memcmp((dst).data, (src).data, (src).len) == 0)                  \
         ? 1                                                                   \
         : 0)))

#define SLICE_PRINT(slice)                                                     \
  do {                                                                         \
    for (size_t i = 0; i < (slice).len; i++) {                                 \
      fprintf(stderr, i == 0 ? "[ %02x" : " %02x", (slice).data[i]);           \
      fflush(stderr);                                                          \
    }                                                                          \
    puts(" ]\n");                                                              \
  } while (0)

#define SLICE_CMP_PRINT(ref, out)                                              \
  do {                                                                         \
    printf("out: [");                                                          \
    for (size_t i = 0; i < out.len; i++) {                                     \
      if (i != 0)                                                              \
        putchar(' ');                                                          \
      if (i > ref.len || ref.data[i] != out.data[i])                           \
        printf(RED "%02x" CRST, out.data[i]);                                  \
      else                                                                     \
        printf("%02x", out.data[i]);                                           \
      fflush(stdout);                                                          \
    }                                                                          \
    printf("]\nref: [");                                                       \
    for (size_t i = 0; i < ref.len; i++) {                                     \
      if (i != 0)                                                              \
        putchar(' ');                                                          \
      if (i >= out.len || ref.data[i] != out.data[i])                          \
        printf(RED "%02x" CRST, ref.data[i]);                                  \
      else                                                                     \
        printf("%02x", ref.data[i]);                                           \
      fflush(stdout);                                                          \
    }                                                                          \
    puts("]\n");                                                               \
  } while (0)

#endif // SLICE_H
