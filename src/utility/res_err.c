#include <stdio.h>
#include <stdlib.h>

#include "res_man.h"

char* res_error(int num) {
  char* res_msg[] = {
    "OK","\aRES_NOT_ACTIVE","\aRES_CANT_OPEN","\aRES_CANT_CLOSE",
    "\aRES_CANT_WRITE","\aRES_CANT_READ","\aRES_ENTRY_NOT_FOUND",
    "\aRES_ALREADY_OPEN","\aRES_FULL","\aRES_CANT_SEEK",
    "\aRES_NOT_OPEN","\aRES_CANT_CREATE","\aRES_CANT_FIND",
    "\aRES_ALREADY_EXISTS","\aRES_CANT_OPEN_SRC","\aRES_CANT_OPEN_DST",
    "\aRES_SRC_TOO_LARGE","\aRES_OUT_OF_MEMORY",
  };

  if (num == 1) {
    num--;
  }
  return res_msg[abs(num)];
}
