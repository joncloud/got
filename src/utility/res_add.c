#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modern.h"

#ifndef modern
#include <alloc.h>
#endif

#include "res_man.h"

int res_add_file(const char* fname, const char* name, int encode_flag) {
  int  num, ret;
  char buff[16];
  FILE* fp;
  long total;
  char far* fb;
  char far* fbp;
  long size;
  char ch;
  long osize;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!res_fp) {
    return RES_NOT_OPEN;
  }

  if (res_find_name(name) >= 0) {
    return RES_ALREADY_EXISTS;
  }
  fp = fopen(fname, "rb");
  if (!fp) {
    return RES_CANT_OPEN_SRC;
  }

  num = res_find_empty();
  if (num < 0) {
    fclose(fp);
    return RES_FULL;
  }
  if (fseek(res_fp, 0l, SEEK_END)) {
    fclose(fp);
    return RES_CANT_SEEK;
  }
  res_header[num].offset = ftell(res_fp);

  if (encode_flag) {
    res_header[num].key = 1;
  }
  else {
    res_header[num].key = 0;
  }

  strncpy(res_header[num].name, name, 9);

  total = 0;
  if (!encode_flag) {
    while (1) {
      if (fread(buff, 1, 1, fp) != 1) {
        ret = 1;
        osize = total;
        break;
      }
      if (fwrite(buff, 1, 1, res_fp) != 1) {
        ret = RES_CANT_WRITE;
        osize = total;
        break;
      }
      total++;
    }
  }
  else {
    fb = farmalloc(65000l);
    if (!fb) {
      fclose(fp);
      return RES_OUT_OF_MEMORY;
    }
    fbp = fb;
    size = 0;
    while (1) {
      if (fread(&ch, 1, 1, fp) != 1) {
        break;
      }
      else {
        size++;
        *fbp = ch;
        fbp++;
      }
    }
    osize = size;
    if (size == 0) {
      fclose(fp);
      if (fb) {
        farfree(fb);
      }
      return RES_CANT_READ;
    }
    size = res_encode(fb, size);
    total = size;
    fbp = res_lzss_buff;
    while (1) {
      ch = *fbp;
      fbp++;
      size--;
      if (fwrite(&ch, 1, 1, res_fp) != 1) {
        fclose(fp);
        if (fb) {
          farfree(fb);
        }
        return RES_CANT_WRITE;
      }
      if (size <= 0) {
        break;
      }
    }
    if (fb) {
      farfree(fb);
    }
    ret = 1;
  }
  res_header[num].original_size = osize;
  res_header[num].length = total;
  fclose(fp);
  res_changed = 1;
  return ret;
}
