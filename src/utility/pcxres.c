#include <stdio.h>
#include <dos.h>
#include <string.h>

#define SEQREG 0x03c4     /* sequencer register */
#define CPWER  0x03c5     /* color plane write enable register */
#define GRPCTL 0x03ce     /* graphics controller register */
#define CPRER  0x03cf     /* color plane read enable register */

union REGS in,out;
struct SREGS seg;

struct{
char manuf;           /* Paintbrush file header (128 bytes) */
char version;
char encode;
char bitpix;          /* bits per pixel */
int  x1;              /* picture dimensions */
int  y1;
int  x2;
int  y2;
int  hres;            /* video card horz. res. */
int  vres;            /* video card Vert. res. */
char palette[48];     /* palette info. (in triples) */
char vmode;
char nplanes;         /* number of planes */
int  byteline;        /* bytes per line */
char filler[60];
} pcx;

FILE *pcx_fp;
char pcx_buffer[255];
int pcx_ptr;
int pcx_error;
char pcx_plane[320];
int pcx_comp_ptr;
int ft;

void save_pcx(void);
void read_pcx_plane(int,int,int);
void get_pcx_palette(void);
int write_pcx_byte(char);
void compress_pcx_data(void);
int pcx_repeat_bytes(int);
void install(void interrupt (*faddr)(),int num);
void interrupt do_save(unsigned bp,unsigned di,unsigned si,unsigned ds,
                       unsigned es,unsigned dx,unsigned cx,unsigned bx,
                       unsigned ax);

/*=========================================================================*/
void main(){

install(do_save,5);
bdos(0x31,1500,0);

}
/*=========================================================================*/
void install(void interrupt (*faddr)(),int num){

setvect(num,faddr);
}
/*=========================================================================*/
void interrupt do_save(unsigned bp,unsigned di,unsigned si,unsigned ds,
                       unsigned es,unsigned dx,unsigned cx,unsigned bx,
                       unsigned ax){
save_pcx();
}
/*=========================================================================*/
void save_pcx(void){
int ret,yl;
int y_size;
int x1,x2,y1,y2;

pcx_fp=fopen("test.pcx","wb");                   /* open pic file */
if(!pcx_fp) return;

x1=0;
x2=319;
y1=0;
y2=199;

pcx.x1=x1;
pcx.y1=y1;
pcx.x2=x2;
pcx.y2=y2;
pcx.manuf=10;
pcx.version=5;
pcx.encode=1;
pcx.bitpix=1;
pcx.hres=180;
pcx.vres=180;
pcx.vmode=0;
pcx.nplanes=4;
pcx.byteline=((x2-x1)+1)/8;
if((x2-x1) % 8) pcx.byteline++;
get_pcx_palette();

ret=fwrite(&pcx,1,128,pcx_fp);                /* read header */
if(ret!=128){fclose(pcx_fp);return;}

pcx_ptr=0;

outport(GRPCTL,4);
y_size=(pcx.y2-pcx.y1)+1;
for(yl=y1;yl<(y1+y_size);yl++){
     read_pcx_plane(x1,yl,pcx.byteline);
     compress_pcx_data();
}
outport(GRPCTL,0x04);
outport(CPWER,0x0f);
if(pcx_ptr!=0) fwrite(pcx_buffer,1,pcx_ptr,pcx_fp);  /* flush buffer */
fclose(pcx_fp);
if(pcx_error) return;
return;
}
/*=========================================================================*/
void get_pcx_palette(){

int loop;
char byte;
char pal_info[16];

for(byte=0;byte<16;byte++){
   in.h.ah=0x10;
   in.h.al=0x07;
   in.h.bl=byte;
   int86(0x10,&in,&out);
   pal_info[byte]=out.h.bh;
}

for(loop=0;loop<48;loop+=3){          /* find RED value */
   byte=pal_info[loop/3];
   if((byte & 0x24)==0x24) pcx.palette[loop]=255;
   else if((byte & 0x04)==0x04) pcx.palette[loop]=170;
   else if((byte & 0x20)==0x20) pcx.palette[loop]=85;
   else pcx.palette[loop]=0;

   byte=pal_info[loop/3];
   if((byte & 0x12)==0x12) pcx.palette[loop+1]=255;
   else if((byte & 0x02)==0x02) pcx.palette[loop+1]=170;
   else if((byte & 0x10)==0x10) pcx.palette[loop+1]=85;
   else pcx.palette[loop+1]=0;

   byte=pal_info[loop/3];
   if((byte & 0x09)==0x09) pcx.palette[loop+2]=255;
   else if((byte & 0x01)==0x01) pcx.palette[loop+2]=170;
   else if((byte & 0x08)==0x08) pcx.palette[loop+2]=85;
   else pcx.palette[loop+2]=0;
}
}
/*=========================================================================*/
void read_pcx_plane(column,row,num_bytes)
int column,row,num_bytes;
{
int t,pcx_byte_ptr;
unsigned char far *video_add;
unsigned char far *temp_add;

pcx_byte_ptr=0;
if(row<200) video_add=(char far *) 0xa0000000L;
else{ video_add=(char far *) 0xa3e80000L;row-=200;}
row*=80;
video_add+=row;
video_add+=(column/8);
temp_add=video_add;

outport(GRPCTL,0x04);
outport(CPRER,0x00);
for(t=0;t<num_bytes;t++){
   outport(CPRER,0x00);
   pcx_plane[pcx_byte_ptr++]=*video_add;     /* read plane 0 data */
   video_add++;
}

video_add=temp_add;
outport(GRPCTL,0x04);
outport(CPRER,0x01);                        /* enable plane 1 only */
for(t=0;t<num_bytes;t++){
   outport(CPRER,0x01);
   pcx_plane[pcx_byte_ptr++]=*video_add;    /* read plane 1 data */
   video_add++;
}

video_add=temp_add;
outport(GRPCTL,0x04);
outport(CPWER,0x02);                        /* enable plane 2 only */
for(t=0;t<num_bytes;t++){
   outport(CPRER,0x02);
   pcx_plane[pcx_byte_ptr++]=*video_add;    /* read plane 2 data */
   video_add++;
}

video_add=temp_add;
outport(GRPCTL,0x04);
outport(CPWER,0x03);                        /* enable plane 3 only */
for(t=0;t<num_bytes;t++){
   outport(CPRER,0x03);
   pcx_plane[pcx_byte_ptr++]=*video_add;    /* read plane 3 data */
   video_add++;
}
}
/*=========================================================================*/
int write_pcx_byte(byte)
char byte;
{
int ret;

if(pcx_ptr==255){
  ret=fwrite(pcx_buffer,1,255,pcx_fp);
  ft+=255;
  if(ret!=255){pcx_error=1;return 0;}
  pcx_ptr=0;
}
pcx_buffer[pcx_ptr++]=byte;
return 1;
}
/*=========================================================================*/
void compress_pcx_data(){
int repeat,t;
char byte;
int old_ptr;

pcx_comp_ptr=0;
for(t=0;t<4;t++){
old_ptr=pcx_comp_ptr;
while(pcx_comp_ptr<(old_ptr+pcx.byteline)){
     repeat=pcx_repeat_bytes(old_ptr+pcx.byteline);
     if((!repeat) && ((pcx_plane[pcx_comp_ptr] & 192)==192)) repeat=1;
     if(repeat){
       byte=pcx_plane[pcx_comp_ptr];
       write_pcx_byte(repeat | 192);
       write_pcx_byte(byte);
       pcx_comp_ptr+=repeat;
     }
     else write_pcx_byte(pcx_plane[pcx_comp_ptr++]);
}
}
}
/*=========================================================================*/
int pcx_repeat_bytes(num_bytes)
int num_bytes;
{

int count;
int temp_ptr;
char byte;

byte=pcx_plane[pcx_comp_ptr];
count=1;
temp_ptr=pcx_comp_ptr+1;

while((count<63) && (temp_ptr<num_bytes)){
     if(byte!=pcx_plane[temp_ptr]) break;
     temp_ptr++;
     count++;
}
if(count==1) return 0;
return count;
}
