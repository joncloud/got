#include "res_int.h"

#include <stdio.h>
#include <string.h>

#ifdef modern
int res_rentries(void) {
  uint8_t buffer[23 * RES_MAX_ENTRIES];
  if (fread(buffer, 23, RES_MAX_ENTRIES, res_fp) != RES_MAX_ENTRIES) {
    return 0;
  }
  res_decrypt((char far*)buffer, (23 * RES_MAX_ENTRIES), 128);

  uint8_t* tmp = buffer;
  for (int i = 0; i < RES_MAX_ENTRIES; i += 1) {
    memcpy(res_header[i].name, tmp, 9);
    tmp += 9;
    res_header[i].offset = *(uint32_t*)(tmp);
    tmp += 4;
    res_header[i].length = *(uint32_t*)(tmp);
    tmp += 4;
    res_header[i].original_size = *(uint32_t*)(tmp);
    tmp += 4;
    res_header[i].key = *(uint16_t*)(tmp);
    tmp += 2;
  }
  return 1;
}

int res_wentries(void) {
  uint8_t buffer[23 * RES_MAX_ENTRIES];
  uint8_t* tmp = buffer;

  for (int i = 0; i < RES_MAX_ENTRIES; i += 1) {
    memcpy(tmp, res_header[i].name, 9);
    tmp += 9;
    *(uint32_t*)(tmp) = res_header[i].offset;
    tmp += 4;
    *(uint32_t*)(tmp) = res_header[i].length;
    tmp += 4;
    *(uint32_t*)(tmp) = res_header[i].original_size;
    tmp += 4;
    *(uint16_t*)(tmp) = res_header[i].key;
    tmp += 2;
  }

  res_encrypt((char far*)&buffer, RES_MAX_ENTRIES * 23, 128);
  if (fwrite(buffer, 23, RES_MAX_ENTRIES, res_fp) != RES_MAX_ENTRIES) {
    return 0;
  }
  return 1;
}
#else
int res_rentries(void) {
  if (fread(&res_header, 1, RES_MAX_ENTRIES * sizeof(RES_HEADER),
             res_fp) != RES_MAX_ENTRIES * sizeof(RES_HEADER)) {
    return 0;
  }
  res_decrypt((char far*)&res_header, RES_MAX_ENTRIES * sizeof(RES_HEADER), 128);
  return 1;
}

int res_wentries(void) {
  res_encrypt((char far*)&res_header, RES_MAX_ENTRIES * sizeof(RES_HEADER), 128);
  if (fwrite(&res_header, 1, RES_MAX_ENTRIES * sizeof(RES_HEADER),
              res_fp) != RES_MAX_ENTRIES * sizeof(RES_HEADER)) {
    return 0;
  }
  return 1;
}
#endif
