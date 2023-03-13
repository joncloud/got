#include "modern.h"

#include <ctype.h>
#include <string.h>

char* strupr(char* s) {
  char* tmp = s;

  for (;*tmp;++tmp) {
    *tmp = toupper((unsigned char) *tmp);
  }

  return s;
}
