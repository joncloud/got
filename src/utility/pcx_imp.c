#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <dir.h>

#include <eg_proto.h>
#undef outportb
#undef inportb


//===========================================================================
char tempstr[255];
//===========================================================================
void main(int argc, char *argv[]){
FILE *fp;

setvga();
initgraf(18,0,0);

strcpy(tempstr,argv[1]);
strcat(tempstr,".pcx");
strupr(tempstr);
pcx_load(tempstr);



getch();
textmode(C80);
}
