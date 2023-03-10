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

#ifdef _WIN32
#define strcmpi   _stricmp
#endif

char* strupr(char* s);

#define randomize()

#include <stdint.h>

// TODO
// #include <time.h>
// inline void randomize(void) { srand((unsigned) time(NULL)); }

#else

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

#endif

#endif
