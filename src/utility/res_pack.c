#include <stdio.h>
#include <string.h>

#include "modern.h"

#ifdef modern
#ifndef _WIN32
#include <unistd.h>
#endif
#endif

#include "res_man.h"

int res_pack(const char* filename) {
  int  num, new_num, nb;
  long bytes, b;
  long new_offset;
  char buff[2048];
  char name[16];
  FILE* fp;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!res_fp) {
    return RES_NOT_OPEN;
  }

  fp = fopen("res_@@@@.tmp","wb");
  if (!fp) {
    return RES_CANT_OPEN_DST;
  }

  if (fwrite(&res_header, 1, RES_MAX_ENTRIES * sizeof(RES_HEADER), fp)
             != RES_MAX_ENTRIES * sizeof(RES_HEADER)) {
    fclose(fp);
    return RES_CANT_WRITE;
  }
  new_offset = (long)(RES_MAX_ENTRIES * sizeof(RES_HEADER));
  new_num = 0;

  for (num = 0; num < RES_MAX_ENTRIES; num++) {
    if (res_header[num].length == 0) {
      continue;
    }
    strcpy(name, res_header[num].name);
    while (strlen(name) < 8) {
      strcat(name, " ");
    }
    printf("\r\nPacking: %s  Size:%.6u...", name, res_header[num].length);
    if (fseek(res_fp, res_header[num].offset, SEEK_SET)) {
      fclose(fp);
      return RES_CANT_SEEK;
    }
    bytes = res_header[num].length;
    b = bytes;
    while (1) {
      if (b > 2047) {
        nb = fread(buff, 1, 2048, res_fp);
      }
      else if (b == 0) {
        break;
      }
      else {
        nb = fread(buff, 1, (int)b, res_fp);
      }
      fwrite(buff, 1, nb, fp);
      b -= (long)nb;
    }
    memcpy(&res_header[new_num], &res_header[num], sizeof(RES_HEADER));
    res_header[new_num].offset = new_offset;
    new_offset += bytes;
    new_num++;
    printf("DONE");
  }
  while (new_num < RES_MAX_ENTRIES) {
    memset(&res_header[new_num], 0, sizeof(RES_HEADER));
    new_num++;
  }
  res_encrypt((char far*)&res_header, RES_MAX_ENTRIES * sizeof(RES_HEADER), 128);

  fseek(fp, 0l, SEEK_SET);
  if (fwrite(&res_header, 1, RES_MAX_ENTRIES * sizeof(RES_HEADER), fp)
             != RES_MAX_ENTRIES * sizeof(RES_HEADER)) {
    fclose(fp);
    return RES_CANT_WRITE;
  }
  fclose(fp);
  fclose(res_fp);
  unlink(filename);
  rename("res_@@@@.tmp", filename);
  printf("\r\n");
  return res_open(filename);
}
