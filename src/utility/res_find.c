#include <stdio.h>
#include <string.h>

#include "res_man.h"

int res_find_name(const char* name) {
  int i;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!res_fp) {
    return RES_NOT_OPEN;
  }

  for (i = 0; i < RES_MAX_ENTRIES; i++) {
    if (!strcmpi(name, res_header[i].name)) {
      return i;
    }
  }
  return RES_ENTRY_NOT_FOUND;
}

int res_find_empty(void) {
  int i;

  if (!res_active) {
    return RES_NOT_ACTIVE;
  }
  if (!res_fp) {
    return RES_NOT_OPEN;
  }

  for (i = 0; i < RES_MAX_ENTRIES; i++) {
    if (res_header[i].length == 0) {
      return i;
    }
  }
  return RES_FULL;
}
