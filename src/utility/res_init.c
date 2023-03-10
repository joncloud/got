#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "modern.h"

#include "res_man.h"
#include "res_int.h"

FILE* res_fp;
RES_HEADER res_header[RES_MAX_ENTRIES];
int res_active = 0;
int res_changed;
char far* res_lzss_buff;

void res_init(char far* buff) {
  randomize();
  res_fp = 0;
  res_active = 1;
  res_changed = 0;
  res_lzss_buff = buff;
}

int res_open(const char* filename) {
  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!(res_fp = fopen(filename, "rb+"))) {
    return RES_CANT_OPEN;
  }
  if (!res_rentries()) {
    fclose(res_fp);
    return RES_CANT_READ;
  }
  res_changed = 0;
  return 1;
}

int res_close(void) {
  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (res_changed) {
    if (fseek(res_fp, 0l, SEEK_SET)) {
      return RES_CANT_SEEK;
    }
    if (!res_wentries()) {
      fclose(res_fp);
      return RES_CANT_WRITE;
    }
  }
  if (res_fp) {
    if (!fclose(res_fp)) {
      return 1;
    }
  }
  return RES_CANT_CLOSE;
}

void res_encrypt(char far* buff, long len, unsigned char key) {
  while (len) {
    len--;
    *buff ^= key;
    buff++;
    key++;
  }
}

void res_decrypt(char far* buff, long len, unsigned char key) {
  while (len) {
    len--;
    *buff ^= key;
    buff++;
    key++;
  }
}
