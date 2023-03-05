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
#include <r_proto.h>

typedef struct{                 //size=512
       char icon[12][20];       //0   grid of icons
       char bg_color;           //240 background color
       char reset;              //241 1=reset all doors, enemies ,etc
       char actor_type[16];     //242 type of enemies (12 max)
       int  actor_x[16];        //254 X coor of enemies
       int  actor_y[16];        //278 Y coor of enemies
       char static_obj[30];     //302 static objects (treasure, keys,etc)
       int  static_x[30];       //332 X coor of static objects
       int  static_y[30];       //392 Y coor of static objects
       char new_level[10];      //452 level jump for icon 200-204
       char new_level_loc[10];  //462 grid location to jump in to
       char area;               //472 game area (1=forest,etc)
       char future[19];         //473
} LEVEL;
//===========================================================================
char tempstr[255];
#define COLOR 64
//===========================================================================
void main(void){
int i,r,x,y,l;
LEVEL scrn;

setmcga();
initgraf(19,0,0);
clearscr(0);

//for(i=0;i<156;i+=12) eg_line(60+0,28+i,60+199,28+i,COLOR);
//for(i=0;i<220;i+=20) eg_line(60+i,28+0,60+i,28+144,COLOR);

for(i=0;i<120;i++){
   x=i%10;
   y=i/10;
   file_read("ressd11.dat",&scrn,128l+(long) (i*sizeof(LEVEL)),sizeof(LEVEL));
   for(r=0;r<12;r++){
      for(l=0;l<20;l++){
        if(l==0 || l==19 || r==0 || r==11){
          if(scrn.icon[r][l]<140){
            eg_dot(60+(x*20)+l,28+(y*12)+r,COLOR);
          }
        }
      }
   }
}
printf("Press [Esc] to Abort, [Enter] to Print");
if(getch()!=27){
  eg_rectangle(0,0,319,12,0,1,-1);
  setprnth();
  devcdump(0,3,0,0,1,1,0);
}
textmode(C80);
}
