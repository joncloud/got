#include <stdio.h>
#include <string.h>

#include "res_man.h"

int res_delete_file(const char* name) {
  int num;

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
  memset(&res_header[num], 0, sizeof(RES_HEADER));
  res_changed = 1;
  return 1;
}
