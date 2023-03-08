#ifndef MODERN_H_
#define MODERN_H_

#ifdef __llvm__

// Erase far / huge when compiling on modern platforms.
#define far
#define huge

#define strcmpi strcasecmp

#endif

#endif
