#include <stdio.h>
#include <string.h>

#include "res_man.h"

int res_rename_file(const char* oldname, const char* newname) {
  int num;

  num = res_find_name(oldname);
  if (num < 0) {
    return RES_ENTRY_NOT_FOUND;
  }

  memset(res_header[num].name, 0, 9);
  strcpy(res_header[num].name, newname);
  res_changed = 1;
  return 1;
}
