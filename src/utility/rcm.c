#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include <r_type.h>
#include <r_proto.h>
#include <r_keys.h>
//===========================================================================
char b1[256];
char b2[512];
FILE *fp1,*fp2;
char *ctype[]={"Smarshing","Kabitzing","Blammerizing","Smooshing"};
char *csymbol="|/-\\";
//===========================================================================
int rcm_compress(char *src,char *dst,int length);
//===========================================================================
void main(int argc, char *argv[]){
long size,length;
int  sz,len,sn,scnt;
float per;

randomize();

printf("\r\n\r\nRCM - Compression Utility\r\n");
printf("Copyright 1993, Custom Software Engineering\r\n\r\n");

if(argc<3){
  printf("FORMAT: RCM INFILE OUTFILE\r\n\r\n");
  exit(0);
}
fp1=fopen(argv[1],"rb");
if(!fp1){
  printf("Unabale to Open File: %s\r\n\r\n",argv[1]);
  exit(0);
}
fp2=fopen(argv[2],"wb");
if(!fp1){
  fclose(fp1);
  printf("Unabale to Open File: %s\r\n\r\n",argv[2]);
  exit(0);
}

printf("%s File: %s....",ctype[random(4)],argv[1]);
size=0;
length=0;
sn=0;
scnt=0;
while(1){
     printf("\b%c",csymbol[sn%4]);
     scnt++;
     if(scnt>20){
       sn++;
       scnt=0;
     }
     len=fread(b1,1,256,fp1);
     if(!len) break;
     sz=rcm_compress(b1,b2,len);
     fwrite(b2,1,sz,fp2);
     length+=(long) len;
     size+=(long) sz;
}
fclose(fp1);
fclose(fp2);

printf("\r\n  Original Size=%ld\r\n",length);
printf("Compressed Size=%ld\r\n",size);

per=(float) length / 100.00;
per=(float) size / per;

printf("     Percentage=%.0f%%\r\n",per);
}
//===========================================================================
int rcm_compress(char *src,char *dst,int length){
char byte,cnt;
int  sz,i;

sz=0;
cnt=0;
for(i=0;i<length;i++){
   byte=*src;
   src++;
   if(byte!=*src){
     if(!cnt) goto store_it;
     if(cnt==1){
       *dst=byte;
       dst++;
       *dst=byte;
       dst++;
       sz+=2;
       cnt=0;
       continue;
     }
     else{
       *dst=254;
       dst++;
       *dst=byte;
       dst++;
       *dst=cnt+1;
       dst++;
       sz+=3;
       cnt=0;
       continue;
     }
   }
   cnt++;
   if(cnt>250){
     *dst=254;
     dst++;
     sz++;
     *dst=byte;
     dst++;
     sz++;
     *dst=cnt+1;
     dst++;
     sz++;
     cnt=0;
  }
  continue;
store_it:
   *dst=byte;
   dst++;
   sz++;
   if(byte==254){
     *dst=1;
     dst++;
     sz++;
     *dst=254;
     dst++;
     sz++;
  }
}
return sz;
}

