#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

#include "res_man.h"
//==========================================================================
int res_write(char *name,char far *buff,long length,int encode_flag){
int num;
long total,size;
char bf[256];
int  bytes;
char far *p;

if(!res_active) return RES_NOT_ACTIVE;
if(!res_fp) return RES_NOT_OPEN;

if(res_find_name(name)>=0) return RES_ALREADY_EXISTS;

num=res_find_empty();
if(num<0) return RES_FULL;

if(fseek(res_fp,0l,SEEK_END)) return RES_CANT_SEEK;
res_header[num].offset=ftell(res_fp);

if(encode_flag){
   res_header[num].key=1;
   size=res_encode(buff,length);
   p=res_lzss_buff;
}
else{
  res_header[num].key=0;
  size=length;
  p=buff;
}
strncpy(res_header[num].name,name,9);
res_header[num].length=size;
res_header[num].original_size=length;

total=0;
while(total<size){
     if(((size-total) >255) && (size > 255)) bytes=256;
     else bytes=(int) (size-total);
     if(!bytes) break;
     movedata(FP_SEG(p),FP_OFF(p),FP_SEG(bf),FP_OFF(bf),bytes);
     if(fwrite(bf,1,bytes,res_fp)!=bytes) return RES_CANT_WRITE;
     total+=bytes;
     p+=bytes;
}
res_changed=1;
return 1;
}
