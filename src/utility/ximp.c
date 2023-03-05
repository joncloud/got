int  pcx_imp(void);
void import_rim(int x1,int y1);
int  select_rim(int *nx,int *ny);
//===========================================================================
extern char tempstr[255];
extern char pic[4][300];
char far *buffer=NULL;
char far *pal=NULL;
//===========================================================================
int pcx_imp(void){
int x,y,ret;

//pcx_load(tempstr);

ret=select_rim(&x,&y);
if(ret) import_rim(x,y);
return ret;
}
//===========================================================================
void import_rim(int x1,int y1){
int *p;
int x,y,r;
int pos,t;

memset(pic,0,1200);

for(t=0;t<4;t++){
  p=(int *) &pic[t];
  *p=4;
  p++;
  *p=16;
  p++;
  *p=0;
  p++;
  pos=6;

  for(r=0;r<4;r++){
    for(y=0;y<16;y++){
       for(x=0;x<16;x+=4){
          pic[t][pos++]=xpoint(x1+x+r,y1+y,PAGE0);
       }
    }
  }
  x1+=16;
}
}
//===========================================================================
int select_rim(int *nx, int *ny){
static int x=0;
static int y=0;
int ox,oy;
int key;


xbox(x,y,x+63,y+15,255,PAGE0);

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
                  xbox(ox,oy,ox+63,oy+15,255,PAGE0);
                  return 1;
     }
     if(x<0) x=0;
     if(x>(320-63)) x=320-63;
     if(y<0) y=0;
     if(y>(240-15)) y=240-15;
     xbox(ox,oy,ox+63,oy+15,255,PAGE0);
     xbox(x,y,x+63,y+15,255,PAGE0);
}
}

