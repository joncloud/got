#ifndef MODERN_H_
#define MODERN_H_

#ifdef __llvm__

// Erase far / huge when compiling on modern platforms.
#define far
#define huge

// Map old function names to new ones.
#define farfree   free
#define farmalloc malloc
#define strcmpi   strcasecmp

#endif

#endif
