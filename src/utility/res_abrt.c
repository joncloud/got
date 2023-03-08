#include <stdio.h>

#include "res_man.h"

int res_abort(void) {
  if (!res_active) {
    return RES_NOT_ACTIVE;
  }

  if (res_fp) {
    if (!fclose(res_fp)) {
      return 1;
    }
  }

  return RES_CANT_CLOSE;
}
