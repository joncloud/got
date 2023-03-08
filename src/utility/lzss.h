#ifndef LZSS_H_
#define LZSS_H_

#include "modern.h"

long lzss_decompress(char far* src, char far* dst, long len);
long lzss_compress(long origsize, char far* src, char far* dst);

#endif
