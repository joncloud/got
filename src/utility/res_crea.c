#include <stdio.h>
#include <string.h>

#include "res_man.h"

int res_create(const char* filename) {
  FILE* fp;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (res_fp) {
    return RES_ALREADY_OPEN;
  }

  fp = fopen(filename, "rb");
  if (fp) {
    fclose(fp);
    return RES_ALREADY_EXISTS;
  }
  if (!(res_fp = fopen(filename, "wb"))) {
    return RES_CANT_CREATE;
  }

  memset(&res_header, 0, RES_MAX_ENTRIES * sizeof(RES_HEADER));
  res_encrypt((char far*)&res_header, RES_MAX_ENTRIES * sizeof(RES_HEADER), 128);

  if (fwrite(res_header, 1, RES_MAX_ENTRIES * sizeof(RES_HEADER),
             res_fp) != RES_MAX_ENTRIES * sizeof(RES_HEADER)) {
    fclose(res_fp);
    return RES_CANT_WRITE;
  }
  fclose(res_fp);
  res_changed = 0;
  return res_open(filename);
}
