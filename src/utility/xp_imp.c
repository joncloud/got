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


void write_rim(int x1,int y1,int i);
int  select_rim(int *nx,int *ny);
//===========================================================================
char tempstr[255];
char rim_buff[262*4];
//===========================================================================
void main(int argc, char *argv[]){
int x,y,i;


if(argc<2){
  printf("\r\n\r\n FORMAT: IMP <picture (.PCX is assumed)> <starting RIM # (1 if not given)>\r\n");
  printf("EXAMPLE: IMP thor1 5\r\n");
  exit(0);
}
setmcga();
initgraf(19,0,0);

i=1;
if(argc>2) i=atoi(argv[2]);

strcpy(tempstr,"\\game\\pcx\\");
strcat(tempstr,argv[1]);
strcat(tempstr,".pcx");
pcx_load(tempstr);

while(select_rim(&x,&y)){
     write_rim(x,y,i);
     i++;
}
textmode(C80);
}
//===========================================================================
void write_rim(int x1,int y1,int num){
int *p;
int x,y,r,i;
int pos,t;
FILE *fp;
char s[21];

memset(rim_buff,0,262*4);

pos=0;
p=(int *) rim_buff;

for(t=0;t<4;t++){
  *p=4;
  p++;
  *p=16;
  p++;
  *p=0;
  p++;
  p=p+128;

  pos+=6;

  for(r=0;r<4;r++){
    for(y=0;y<16;y++){
       for(x=0;x<16;x+=4){
          rim_buff[pos++]=readpix(x1+x+r,y1+y);
       }
    }
  }
  x1+=16;
  for(i=0;i<256;i++) rim_buff[(t*262)+i+6]^=i;
}

strcpy(tempstr,"\\game\\rim\\pcx");
itoa(num,s,10);
strcat(tempstr,s);
strcat(tempstr,".rim");
fp=fopen(tempstr,"wb");
if(!fp){
  printf("ERROR\r\n");
  getch();
  return;
}
fwrite(rim_buff,262*4,1,fp);
fclose(fp);

}
//===========================================================================
int select_rim(int *nx, int *ny){
static int x=0;
static int y=0;
int ox,oy;
int key;

//x=0;
//y=0;

typedot(1);
eg_rectangle(x,y,x+63,y+15,255,0,-1);

while(1){
     ox=x;
     oy=y;
     key=getch();
     if(key==0) key=getch();
       switch(key){
             case 72:   //up
                  y-=16;
                  break;
             case 80:  //down
                  y+=16;
                  break;
             case 75:   //left
                  x-=16;;
                  break;
             case 77:  //right
                  x+=16;
                  break;
             case 56:   //^up
                  y--;
                  break;
             case 50:  //^down
                  y++;
                  break;
             case 52:   //^left
                  x--;
                  break;
             case 54:  //^right
                  x++;
                  break;
             case 27: return 0;  //ESC
             case 13:           //CR
                  *nx=x;
                  *ny=y;
                  eg_rectangle(ox,oy,ox+63,oy+15,255,0,-1);
                  return 1;
     }
     if(x<0) x=0;
     if(x>(320-63)) x=320-63;
     if(y<0) y=0;
     if(y>(200-15)) y=200-15;
     eg_rectangle(ox,oy,ox+63,oy+15,255,0,-1);
     eg_rectangle(x,y,x+63,y+15,255,0,-1);
}
}

