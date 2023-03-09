#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "res_man.h"

int res_replace_file(const char* fname, const char* name, int encode_flag) {
  res_delete_file(name);
  res_add_file(fname, name, encode_flag);
  return 1;
}
