#include <string.h>
#include <conio.h>
#include <string.h>

#include "eg_proto.h"
#undef outportb
#undef inportb
#include "pcx.h"

//===========================================================================
char tempstr[255];
//===========================================================================
void main(int argc, char *argv[]) {
  (void)argc;

  setvga();
  initgraf(18, 0, 0);

  strcpy(tempstr, argv[1]);
  strcat(tempstr, ".pcx");
  strupr(tempstr);
  pcx_load(tempstr);

  getch();
  textmode(C80);
}
