#ifndef MODERN_H_
#define MODERN_H_

#ifdef __llvm__

// Erase far / huge when compiling on modern platforms.
#define modern
#define far
#define huge

// Map old function names to new ones.
#define farfree   free
#define farmalloc malloc
#define strcmpi   strcasecmp

char* strupr(char* s);

#define randomize()

#include <stdint.h>

// TODO
// #include <time.h>
// inline void randomize(void) { srand((unsigned) time(NULL)); }

#else

typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

#endif

#endif
