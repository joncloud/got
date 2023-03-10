#include <stdio.h>
#include <string.h>
#include <mem.h>
#include <dos.h>

#include "res_man.h"

long res_read(const char* name, char far* buff) {
  int num, bytes;
  size_t len;
  size_t total;
  char bf[256];
  char far* p;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!res_fp) {
    return RES_NOT_OPEN;
  }

  num = res_find_name(name);
  if (num < 0) {
    return RES_CANT_FIND;
  }

  if (fseek(res_fp, res_header[num].offset, SEEK_SET)) {
    return RES_CANT_SEEK;
  }
  len = (size_t)res_header[num].length;

  total = 0;
  if (!res_header[num].key) {
    p = buff;
  }
  else {
    p = res_lzss_buff;
  }

  while (total < len) {
    if (((len - total) > 255) && (len > 255)) {
      bytes = fread(bf, 1, 256, res_fp);
    }
    else {
      bytes = fread(bf, 1, len - total, res_fp);
    }
    if (!bytes) break;
    total += bytes;
    movedata(FP_SEG(bf), FP_OFF(bf), FP_SEG(p), FP_OFF(p), bytes);
    p += bytes;
  }
  if (res_header[num].key) {
    res_decode(buff, len);
  }
  return res_header[num].original_size;
}
