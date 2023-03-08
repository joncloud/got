#include <stdio.h>

#include "res_man.h"
#include "lzss.h"

long res_encode(char far* buff, long length) {
  return lzss_compress(length, buff, res_lzss_buff);
}

long res_decode(char far* buff, long len) {
  return lzss_decompress(res_lzss_buff, buff, len);
}
