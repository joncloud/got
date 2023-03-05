#ifndef LZSS_H_
#define LZSS_H_

long lzss_decompress(char far* src, char far* dst, long len);
unsigned int lzss_compress(long origsize, char far* src, char far* dst);

#endif
