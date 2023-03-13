#include <stdio.h>
#include <string.h>

#include "modern.h"

#ifdef modern

#include <stdlib.h>

#else

#include <alloc.h>

#endif

#include "res_man.h"
#include "lzss.h"

int res_extract_file(const char* fname, const char* name) {
  int  num, ret;
  char buff[16];
  FILE* fp;
  long total, size;
  char far* fb;
  char far* fbp;
  char ch;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!res_fp) {
    return RES_NOT_OPEN;
  }

  num = res_find_name(name);
  if (num < 0) {
    return RES_ENTRY_NOT_FOUND;
  }

  fp = fopen(fname, "wb");
  if (!fp) {
    return RES_CANT_OPEN_DST;
  }

  if (fseek(res_fp, res_header[num].offset, SEEK_SET)) {
    fclose(fp);
    return RES_CANT_SEEK;
  }

  total = res_header[num].length;
  ret = 1;

  if (!res_header[num].key) {
    while (total) {
      total--;
      if (fread(buff, 1, 1, res_fp) != 1) {
        break;
      }
      if (fwrite(buff, 1, 1, fp) != 1) {
        fclose(fp);
        ret = RES_CANT_WRITE;
        break;
      }
    }
  }
  else {
    fb = farmalloc((long)res_header[num].original_size);
    if (!fb) {
      fclose(fp);
      return RES_OUT_OF_MEMORY;
    }
    fbp = res_lzss_buff;
    size = total;
    while (size) {
      if (fread(&ch, 1, 1, res_fp) != 1) {
        fclose(fp);
        if (fb) {
          farfree(fb);
        }
        return RES_CANT_READ;
      }
      else {
        *fbp = ch;
        fbp++;
        size--;
      }
    }
    size = lzss_decompress(res_lzss_buff, fb, total);
    fbp = fb;
    while (size) {
      ch = *fbp;
      fbp++;
      size--;
      if (fwrite(&ch, 1, 1, fp) != 1) {
        fclose(fp);
        if (fb) {
          farfree(fb);
        }
        return RES_CANT_WRITE;
      }
    }
    if (fb) {
      farfree(fb);
    }
  }

  fclose(fp);
  return ret;
}
