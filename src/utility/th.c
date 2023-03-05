//#define TESTING 1
#define COMPILING 1

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <alloc.h>
#include <dir.h>

#include <maskim.h>
#include <modex.h>
#include <sbc.h>
#include <sbcvoice.h>

#undef outportb
#undef inportb
//==========================================================================
//typedefs & defines
 
typedef struct{
   MaskedImage *pic[4][4]; //pointers to objects
   int  width;             //width-1 in pixels
   int  height;            //height-1 in pixels
   int  x;                 //current x
   int  y;                 //current y
   int  dir;               //current dir (U,D,L,R,still)
   int  last_x[2];         //
   int  last_y[2];         //
   int  last_dir;          //
   int  speed;             //
   int  move;              //type of movement (0=none,1=player control);
   char used;
   int  x_inc;
   int  y_inc;
   int  next;
   int  num_pics;
   int  count;
   char strength;
   char health;
   char vunerable;
   char shot_cnt;
   char mono;
   char frame_speed;
   char frame_count;
   char type;
   int  money;
   int  keys;
   char future[10];
} XOBJECT;

#define PAGES 0u
#define PAGE0 3840u
#define PAGE1 19200u
#define PAGE2 34560u
#define PAGE3 49920u   //57600l
#define X_MAX  319
#define Y_MAX  191
#define THOR 0
#define UP     72
#define DOWN   80
#define LEFT   75
#define RIGHT  77
#define HOME   71
#define PGUP   73
#define END    79
#define PGDN   81
#define ESC     1
#define SPACE  57
#define ALT    56
#define CTRL   29
//==========================================================================
//internal prototypes
int  init_thor(void);
int  read_spr_file(char *filename);
void exit_code(void);
int  get_movement(XOBJECT *obj);
void move_object(int num);
void erase_object(int num);
int  movement_one(XOBJECT *obj);
int  movement_two(XOBJECT *obj);
int  movement_three(XOBJECT *obj);
int  movement_four(XOBJECT *obj);
void thor_shoots(void);
void xprint(int x,int y,char *string,int color,unsigned int page);
int  check_for_hit(XOBJECT *obj,int num);
void object_destroyed(int num);
int  overlap(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
int  object_damaged(XOBJECT *obj,int strength);
void display_health(void);
void interrupt keyboard_int();              // interrupt prototype
void interrupt (*old_keyboard_int)(void);   // interrupt function pointer
void interrupt timer_int();              // interrupt prototype
void interrupt (*old_timer_int)(void);   // interrupt function pointer
void next_frame(XOBJECT *obj);
void build_level(int current_level);
int  check_movement(int x,int y,XOBJECT *obj);
void display_money(void);
void display_keys(void);
void add_jewel(int x,int y);
int  open_door(int x,int y);
void copy_image(int x1,int y1,int x2,int y2,char *buff1,char *buff2);
void load_palette(void);
int reverse_direction(XOBJECT *obj);
void output_sound(char far* buff,int priority);
void split_screen(void);
int load_bg_pics(void);
int load_sd_data(void);
//==========================================================================
//global variables

union REGS in,out;
struct SREGS seg;
char byte;
unsigned int word;

int sound_cnt;
int sound_level;
int sound_playing;

int *sound_ptr;
int sound_shoot[]={5000,1,5500,1,6000,1,6500,1,7000,1,0,0};
int sound_good[]= {2000,9,1000,9,500,9,0,0};
int sound_hit[]=  {5000,2, 0,2, 5000,2, 0,2, 5000,2, 5000,2, 0,2, 5000,2, 0,2, 5000,2,
                   5000,2, 0,2, 5000,2, 0,2, 5000,2,0,0};
int sound_thit[]= {3000,2, 0,2, 3000,2, 0,2, 3000,2, 3000,2, 0,2, 3000,2, 0,2, 3000,2,
                   3000,2, 0,2, 3000,2, 0,2, 3000,2, 0,0};

int sound_door[]= {500,2,1000,2,1500,2,2000,2,2500,2,3000,2,3500,3,4000,3,
                   4500,3,5000,3,5500,3,6000,4,6500,4,7000,4,7500,4,0,0};

/*
char level[][20]={
{6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,4},
{12,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,7},
{12,0,0,0,12,0,0,0,0,0,0,7,0,0,0,0,0,0,0,7},
{12,0,0,0,0,0,0,12,0,0,0,7,0,0,0,0,0,0,0,7},
{11,11,11,11,14,0,0,0,0,0,0,6,3,1,3,3,3,3,3,7},
{12,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{12,0,0,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{12,0,0,0,8,0,0,0,0,0,12,12,12,12,12,12,12,12,12,7},
{11,9,9,9,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{12,0,0,0,0,0,0,0,0,0,12,12,12,12,12,12,12,0,0,7},
{12,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,12,0,0,7},
{12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,6}
};
char background[17][275];
*/

unsigned int page[3]={PAGE0,PAGE1,PAGE2};
char thor_pic[16][275];
char thor_mask[16][275];

char monster_pic[16][275];
char monster_mask[16][275];

char thorshot_pic[16][196];
char thorshot_mask[16][196];

char potion_red_pic[275];
char potion_mask[275];

char key_pic[160];
char key_mask[160];

char jewel_blue_pic[80];
char jewel_blue_mask[80];
char jewel_red_pic[80];
char jewel_red_mask[80];

#define NUM_OBJECTS 22
XOBJECT *object[NUM_OBJECTS];   //0     = thor
                                //1-3   = thor shots
                                //4-8   = monster
                                //9-13  = monster shots
                                //14-21 = immovable (keys,jewels,etc)
XOBJECT thor;
XOBJECT thorshot;
XOBJECT monster[9];
XOBJECT monster_shot[5];
XOBJECT jewel[7];
XOBJECT key[3];
XOBJECT potion[1];

char text[60][72];

unsigned int display_page;
unsigned int draw_page;
int pge;
int exit_flag;
char key_flag[100];
char break_code;
char scan_code;
char byte;
int bg_color;
int sound_priority;

static MaskedImage thor_image[16];
static MaskedImage thorshot_image[16];
static MaskedImage monster_image[16];
static MaskedImage key_image;
static MaskedImage potion_red_image;
static MaskedImage jewel_blue_image;
static MaskedImage jewel_red_image;
extern char  far *music_buffer;
extern char  far *music_ptr;
extern char far *vbuff;
char far *voice_ow[3];
char far *voice_swish;
char far *voice_yah;
char far *voice_creek;
char far *voice_ouch;
char far *voice_drink;
char far *bg_buff;
char far *bg_pics;
char bg_header[200];

struct sdd{
       char icon[12][20];
       char bg_color;
       char future[271];
};
struct sdd scrn;
char far *sd_data;
char sd_header[128];
int current_level;
//==========================================================================
void main(void){
int i;
unsigned int u;
FILE *fp;
int x,y,sx;
char buff[255];
char ch;

#ifdef COMPILING
  chdir("\\thor");
#endif

if(!load_bg_pics()) exit(0);
if(!load_sd_data()) exit(0);

sound_cnt=sound_level=sound_playing=0;
sound_priority=255;

#ifndef TESTING
outportb(0x43,0x36);              //00110110B
word=11190;
byte=word;
outportb(0x40,byte);       //set timer tick to 10ms
word=word >> 8;
byte=word;
outportb(0x40,byte);
#endif

//printf("FAR HEAP=%lu",farcoreleft());
//getch();
//bg_buff=farmalloc(61500u);
//if(!bg_buff){
//  printf("No Memory");
//  exit(0);
//}

load_voice_file("swish.voc");
voice_swish=vbuff;
if(!voice_swish) exit(0);

load_voice_file("ow.voc");
voice_ow[0]=vbuff;
if(!voice_ow[0]) exit(0);

load_voice_file("getoff1.voc");
voice_ow[1]=vbuff;
if(!voice_ow[1]) exit(0);

load_voice_file("nothurt1.voc");
voice_ow[2]=vbuff;
if(!voice_ow[2]) exit(0);

load_voice_file("drink.voc");
voice_drink=vbuff;
if(!voice_drink) exit(0);

load_voice_file("yah.voc");
voice_yah=vbuff;
if(!voice_yah) exit(0);

load_voice_file("creek.voc");
voice_creek=vbuff;
if(!voice_creek) exit(0);

load_voice_file("ouch.voc");
voice_ouch=vbuff;
if(!voice_ouch) exit(0);

if(!init_sbv()) exit(0);
ctvm_speaker(1);

memset(text,0x00,60*72);
memset(key_flag,0,100);

fp=fopen("text.dat","rb");
if(!fp) exit(0);
for(i=0;i<60;i++){
   if(fread(text[i],72,1,fp) !=1){
     fclose(fp);
     exit_code();
     printf("Cannot Read File: TEXT.DAT\r\n");
     exit(0);
   }
}
fclose(fp);

xsetmode();
load_palette();

bg_color=92;

randomize();

exit_flag=0;
if(!init_thor()){exit_code();exit(0);}

//setup backgrounds
xfillrectangle(0,0,320,Y_MAX+1,PAGE0,bg_color);

for(i=0;i<6;i++){
   xfillrectangle(0+i,0+i,320-i,47-i,PAGES,(19+ i)*(i!=4));
}
for(i=0;i<2;i++){
   xfillrectangle(56+i,8+i,108-i,13-i,PAGES,(19+i)*(i!=1));
//   xfillrectangle(56+i,207,108-i,214-i,PAGE0,(19+i)*(i!=1));
//   xfillrectangle(56+i,216+i,108-i,223-i,PAGE0,(19+i)*(i!=1));

   xfillrectangle(261+i,6+i,275-i,28-i,PAGES,(19+i)*(i!=1));
   xfillrectangle(275+i,6+i,289-i,28-i,PAGES,(19+i)*(i!=1));
   xfillrectangle(289+i,6+i,303-i,28-i,PAGES,(19+i)*(i!=1));
}
xprint(8,8,"HEALTH",20,PAGES); //198
//xprint(16,207,"EXPER",21,PAGE0);
//xprint(16,216,"MAGIC",21,PAGE0);

xfillrectangle(58,32,84,41,PAGES,0);
xprint(8,33,"JEWELS",20,PAGES);

old_keyboard_int=getvect(0x09);
setvect(0x09,keyboard_int);
break_code=1;

#ifndef TESTING
old_timer_int=getvect(0x1c);
setvect(0x1c,timer_int);
#endif
thor.dir=3;

sbfm_init();

#ifndef TESTING
outportb(0x43,0x36);              //00110110B
word=11190;
byte=word;
outportb(0x40,byte);       //set timer tick to 10ms
word=word >> 8;
byte=word;
outportb(0x40,byte);
#endif

split_screen();

current_level=14;
play_cmf_file("castle.CMF") ;
start_music();

gloop:
build_level(current_level);

xcopyd2d(0, 0, 320, Y_MAX+1, 0, 0,PAGE0, PAGE1,320,320);
xcopyd2d(0, 0, 320, Y_MAX+1, 0, 0,PAGE1, PAGE2,320,320);

display_health();
display_money();

pge=0;

while(1){
  if(!sbfm_read_status()){
   start_music();
   #ifndef TESTING
   outportb(0x43,0x36);              //00110110B
   word=11190;
   byte=word;
   outportb(0x40,byte);       //set timer tick to 10ms
   word=word >> 8;
   byte=word;
   outportb(0x40,byte);
   #endif
  }
  display_page=page[pge];
  pge=pge^1;
  draw_page=page[pge];
  xshowpage(display_page);
  for(i=13;i>=0;i--) erase_object(i);
  for(i=21;i>=0;i--) move_object(i);
  if(exit_flag){
    if(exit_flag<3) break;
    goto gloop;
  }
}
farfree(voice_swish);
farfree(voice_ow[0]);
farfree(voice_ow[1]);
farfree(voice_ow[2]);
farfree(voice_ouch);
farfree(voice_creek);
farfree(voice_yah);


if(exit_flag==1){
  load_voice_file("odin.voc");
  voice_yah=vbuff;
  output_sound(voice_yah,1);
  while(ct_voice_status);
  farfree(voice_yah);
}
while(ct_voice_status);
sbfm_terminate() ;
byte=inportb(0x61);   //sound off
byte &= 0xfc;
outportb(0x61,byte);
xshowpage(PAGE0);

setvect(0x09,old_keyboard_int);
#ifndef TESTING
setvect(0x1c,old_timer_int);
#endif
exit_code();
ctvm_terminate() ;
exit(0);
}
//===========================================================================
void interrupt keyboard_int(){

scan_code=inportb(0x60);
byte=inportb(0x61);
byte |= 0x80;
outportb(0x61,byte);
byte &= 0x7f;
outportb(0x61,byte);
if(scan_code & 0x80) key_flag[scan_code & 0x7f]=0;
else key_flag[scan_code & 0x7f]=1;
outportb(0x20,0x20);
}
//===========================================================================
void copy_image(int x1,int y1,int x2,int y2,char *buff1,char *buff2){
int x,y,i,p;

i=0;
for(y=y1;y<=y2;y++){
   for(x=x1;x<=x2;x++){
      p=xpoint(x,y,PAGE0);
      buff1[i]=p;
      if(p!=0 && p!=15) buff2[i]=1;
      i++;
   }
}
}
//===========================================================================
int init_thor(void){
int i,r;
unsigned int a;
char rim_buff[1200];
FILE *fp;

xfillrectangle(0,0,320,Y_MAX+1,PAGE0,0);
memset((char *) thor_pic,0,16*275);

fp=fopen("thoru.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);

copy_image(0,0,15,15,thor_pic[0],thor_mask[0]);
copy_image(16,0,31,15,thor_pic[1],thor_mask[1]);
copy_image(32,0,47,15,thor_pic[2],thor_mask[2]);
copy_image(48,0,63,15,thor_pic[3],thor_mask[3]);

fp=fopen("thord.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);

copy_image(0,0,15,15,thor_pic[4],thor_mask[4]);
copy_image(16,0,31,15,thor_pic[5],thor_mask[5]);
copy_image(32,0,47,15,thor_pic[6],thor_mask[6]);
copy_image(48,0,63,15,thor_pic[7],thor_mask[7]);

fp=fopen("thorl2.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);

copy_image(0,0,15,15,thor_pic[8],thor_mask[8]);
copy_image(16,0,31,15,thor_pic[9],thor_mask[9]);
copy_image(32,0,47,15,thor_pic[10],thor_mask[10]);
copy_image(48,0,63,15,thor_pic[11],thor_mask[11]);

fp=fopen("thorr2.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);

copy_image(0,0,15,15,thor_pic[12],thor_mask[12]);
copy_image(16,0,31,15,thor_pic[13],thor_mask[13]);
copy_image(32,0,47,15,thor_pic[14],thor_mask[14]);
copy_image(48,0,63,15,thor_pic[15],thor_mask[15]);

fp=fopen("hammeru.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);
copy_image(0,0,13,13,thorshot_pic[0],thorshot_mask[0]); //up
copy_image(16,0,29,13,thorshot_pic[1],thorshot_mask[1]);
copy_image(32,0,45,13,thorshot_pic[2],thorshot_mask[2]);
copy_image(48,0,61,13,thorshot_pic[3],thorshot_mask[3]);

fp=fopen("hammerd.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);
copy_image(0,0,13,13,thorshot_pic[4],thorshot_mask[4]); //down
copy_image(16,0,29,13,thorshot_pic[5],thorshot_mask[5]);
copy_image(32,0,45,13,thorshot_pic[6],thorshot_mask[6]);
copy_image(48,0,61,13,thorshot_pic[7],thorshot_mask[7]);

fp=fopen("hammerl.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);
copy_image(0,0,13,13,thorshot_pic[8],thorshot_mask[8]); //left
copy_image(16,0,29,13,thorshot_pic[9],thorshot_mask[9]);
copy_image(32,0,45,13,thorshot_pic[10],thorshot_mask[10]);
copy_image(48,0,61,13,thorshot_pic[11],thorshot_mask[11]);

fp=fopen("hammerr.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);
copy_image(0,0,13,13,thorshot_pic[12],thorshot_mask[12]); //right
copy_image(16,0,29,13,thorshot_pic[13],thorshot_mask[13]);
copy_image(32,0,45,13,thorshot_pic[14],thorshot_mask[14]);
copy_image(48,0,61,13,thorshot_pic[15],thorshot_mask[15]);

xfillrectangle(0,0,320,Y_MAX+1,PAGE0,0);
fp=fopen("ghost1.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);

copy_image(0,0,15,15,monster_pic[0],monster_mask[0]);
copy_image(16,0,31,15,monster_pic[1],monster_mask[1]);
copy_image(48,0,63,15,monster_pic[2],monster_mask[2]);


//if(!read_spr_file("keypot.spr")) return 0;

fp=fopen("jewels1.rim","rb");
for(i=0;i<4;i++){
   fread(rim_buff,262,1,fp);
   for(r=0;r<256;r++) rim_buff[r+6]^=r;
   xput(0+(i*16),0,PAGE0,rim_buff);
}
fclose(fp);

copy_image(0,0,8,15,key_pic,key_mask);
copy_image(16,0,21,9,jewel_blue_pic,jewel_blue_mask);
copy_image(32,0,37,9,jewel_red_pic,jewel_red_mask);
copy_image(48,0,63,15,potion_red_pic,potion_mask);

a=PAGE3;
for(i=0;i<16;i++){
     r=xcreatmaskimage2(&thor_image[i], a,
      thor_pic[i], 16, 16, thor_mask[i]);
      if(!r){
        exit_code();
        printf("Couldn't get memory\n");
        exit(0);
      }
      a+=r;
}
for(i=0;i<16;i++){
   r=xcreatmaskimage2(&thorshot_image[i], a,
    thorshot_pic[i], 14, 14, thorshot_mask[i]);
    if(!r){
      exit_code();
      printf("Couldn't get memory\n");
      exit(0);
    }
    a+=r;
}

for(i=0;i<3;i++){
     r=xcreatmaskimage2(&monster_image[i], a,
      monster_pic[i], 16,16, monster_mask[i]);
      if(!r){
        exit_code();
        printf("Couldn't get memory\n");
        exit(0);
      }
      a+=r;
}

r=xcreatmaskimage2(&potion_red_image, a,
  potion_red_pic, 16,16, potion_mask);
if(!r){
  exit_code();
  printf("Couldn't get memory\n");
  exit(0);
}
a+=r;

r=xcreatmaskimage2(&key_image, a,
  key_pic, 9,16, key_mask);
if(!r){
  exit_code();
  printf("Couldn't get memory\n");
  exit(0);
}
a+=r;
r=xcreatmaskimage2(&jewel_blue_image, a,
  jewel_blue_pic, 6,10, jewel_blue_mask);
if(!r){
  exit_code();
  printf("Couldn't get memory\n");
  exit(0);
}
a+=r;
r=xcreatmaskimage2(&jewel_red_image, a,
  jewel_red_pic, 6,10, jewel_red_mask);
if(!r){
  exit_code();
  printf("Couldn't get memory\n");
  exit(0);
}
a+=r;

for(i=0;i<4;i++){
   thor.num_pics=4;
   thor.pic[i][0]=&thor_image[0+(i*4)];
   thor.pic[i][1]=&thor_image[1+(i*4)];
   thor.pic[i][2]=&thor_image[2+(i*4)];
   thor.pic[i][3]=&thor_image[3+(i*4)];
   thor.next=0;
}
thor.x_inc=2;
thor.y_inc=2;

thor.width=15;
thor.height=15;
thor.x=98;
thor.y=100;
thor.dir=4;
thor.last_x[0]=98;
thor.last_y[0]=100;
thor.last_dir=4;
thor.speed=1;
thor.move=1;
thor.used=1;
thor.strength=3;
thor.health=50;
thor.vunerable=20;
thor.shot_cnt=20;
thor.count=thor.speed;
thor.frame_speed=4;
thor.frame_count=1;
thor.money=0;
thor.type=1;
object[0]=&thor;

//thor shots

for(i=0;i<4;i++){
   thorshot.pic[i][0]=&thorshot_image[0+(i*4)];
   thorshot.pic[i][1]=&thorshot_image[1+(i*4)];
   thorshot.pic[i][2]=&thorshot_image[2+(i*4)];
   thorshot.pic[i][3]=&thorshot_image[3+(i*4)];
}
   thorshot.num_pics=4;
   thorshot.next=0;
   thorshot.x_inc=4;
   thorshot.y_inc=4;
thorshot.width=13;
thorshot.height=13;
thorshot.x=0;
thorshot.y=0;
thorshot.dir=0;
thorshot.last_x[0]=0;
thorshot.last_y[1]=0;
thorshot.last_dir=0;
thorshot.speed=1;
thorshot.move=3;
thorshot.used=0;
thorshot.strength=10;
thorshot.health=1;
thorshot.frame_speed=4;
thorshot.frame_count=4;
thorshot.count=thorshot.speed;
thorshot.type=3;
object[1]=&thorshot;

for(i=0;i<4;i++){
   monster[0].num_pics=4;
   monster[0].pic[i][0]=&monster_image[0];
   monster[0].pic[i][1]=&monster_image[1];
   monster[0].pic[i][2]=&monster_image[0];
   monster[0].pic[i][3]=&monster_image[2];
   monster[0].x_inc=2;
   monster[0].next=0;
   monster[0].y_inc=2;
}
monster[0].width=15;
monster[0].height=15;
monster[0].used=1;
monster[0].speed=2;
monster[0].strength=2;
monster[0].health=10;
monster[0].mono=1;
monster[0].last_x[0]=0;
monster[0].last_y[0]=0;
monster[0].count=monster[0].speed;
monster[0].frame_count=5;
monster[0].frame_speed=5;
monster[0].type=2;

memcpy(&monster[1],&monster[0],sizeof(XOBJECT));
memcpy(&monster[2],&monster[0],sizeof(XOBJECT));
memcpy(&monster[3],&monster[0],sizeof(XOBJECT));
memcpy(&monster[4],&monster[0],sizeof(XOBJECT));

memcpy(&monster[5],&monster[0],sizeof(XOBJECT));
memcpy(&monster[6],&monster[0],sizeof(XOBJECT));
memcpy(&monster[7],&monster[0],sizeof(XOBJECT));
memcpy(&monster[8],&monster[0],sizeof(XOBJECT));

monster[0].x=280;
monster[0].y=30;
monster[0].dir=2;
monster[0].move=4;
object[4]=&monster[0];

monster[1].x=270;
monster[1].y=154;
monster[1].dir=3;
monster[1].move=4;
object[5]=&monster[1];

monster[2].x=160;
monster[2].y=90;
monster[2].dir=2;
monster[2].move=4;
object[6]=&monster[2];

monster[3].x=160;
monster[3].y=130;
monster[3].dir=3;
monster[3].move=4;
object[7]=&monster[3];

monster[4].x=80;
monster[4].y=115;
monster[4].dir=2;
monster[4].move=4;
object[8]=&monster[4];

monster[5].x=76;
monster[5].y=115;
monster[5].dir=3;
monster[5].move=4;
object[9]=&monster[5];

monster[6].x=80;
monster[6].y=115;
monster[6].dir=0;
monster[6].move=4;
object[10]=&monster[6];

monster[7].x=78;
monster[7].y=115;
monster[7].dir=2;
monster[7].move=4;
object[11]=&monster[7];

monster[8].x=82;
monster[8].y=115;
monster[8].dir=2;
monster[8].move=4;
object[12]=&monster[8];

jewel[0].num_pics=1;
jewel[0].pic[0][0]=&jewel_blue_image;
jewel[0].x_inc=0;
jewel[0].next=0;
jewel[0].y_inc=0;
jewel[0].last_x[0]=0;
jewel[0].last_y[0]=0;
jewel[0].width=5;
jewel[0].height=9;
jewel[0].move=0;
jewel[0].used=0;
jewel[0].dir=0;
jewel[0].mono=1;
jewel[0].speed=0;
jewel[0].count=0;
jewel[0].frame_count=0;
jewel[0].frame_speed=0;
memcpy(&jewel[1],&jewel[0],sizeof(XOBJECT));
memcpy(&jewel[2],&jewel[0],sizeof(XOBJECT));
memcpy(&jewel[3],&jewel[0],sizeof(XOBJECT));
memcpy(&jewel[4],&jewel[0],sizeof(XOBJECT));
memcpy(&jewel[5],&jewel[0],sizeof(XOBJECT));
memcpy(&jewel[6],&jewel[0],sizeof(XOBJECT));

key[0].num_pics=1;
key[0].pic[0][0]=&key_image;
key[0].x_inc=0;
key[0].next=0;
key[0].y_inc=0;
key[0].last_x[0]=0;
key[0].last_y[0]=0;
key[0].width=8;
key[0].height=15;
key[0].move=0;
key[0].used=0;
key[0].dir=0;
key[0].mono=1;
key[0].speed=0;
key[0].count=0;
key[0].frame_count=0;
key[0].frame_speed=0;
memcpy(&key[1],&key[0],sizeof(XOBJECT));
memcpy(&key[2],&key[0],sizeof(XOBJECT));
key[0].x=294;
key[0].y=160;
key[0].type=7;
key[0].used=1;
object[14]=&key[0];

key[1].x=294;
key[1].y=22;
key[1].type=7;
key[1].used=1;
object[15]=&key[1];

potion[0].num_pics=1;
potion[0].pic[0][0]=&potion_red_image;
potion[0].x_inc=0;
potion[0].next=0;
potion[0].y_inc=0;
potion[0].last_x[0]=0;
potion[0].last_y[0]=0;
potion[0].width=15;
potion[0].height=15;
potion[0].move=0;
potion[0].used=0;
potion[0].dir=0;
potion[0].mono=1;
potion[0].speed=0;
potion[0].count=0;
potion[0].frame_count=0;
potion[0].frame_speed=0;

potion[0].x=18;
potion[0].y=110;
potion[0].type=8;
potion[0].used=1;
object[16]=&potion[0];
return 1;
}
//===========================================================================
int read_spr_file(char *filename){
int i,x,y,sx,sy;
char ch;
FILE *fp;

fp=fopen(filename,"rb");
if(!fp) return 0;

x=y=0;
sx=sy=0;
fread(&sx,1,1,fp);
fread(&sy,1,1,fp);

for(i=0;i<(sx*sy);i++){
   if(fread(&ch,1,1,fp)!=1){
     fclose(fp);
     return 0;
   }
   xpset(x,y,0,ch);
   y++;
   if(y>=sy){
     y=0;
     x++;
   }
}
fclose(fp);
return 1;
}
//===========================================================================
void exit_code(void){
union REGS regset;

byte=inportb(0x61);   //sound off
byte &= 0xfc;
outportb(0x61,byte);

outportb(0x43,0x36);              //00110110B
word=65535u;
byte=word;
outportb(0x40,byte);
word=word >> 8;
byte=word;
outportb(0x40,byte);
setvect(0x09,old_keyboard_int);
#ifndef TESTING
setvect(0x1c,old_timer_int);
#endif
#ifdef COMPILING
  chdir("\\bc");
#endif
if(bg_pics) farfree(bg_pics);
regset.x.ax = 0x0003; int86(0x10, &regset, &regset);
}
//===========================================================================
void next_frame(XOBJECT *obj){
int next;

obj->frame_count--;
if(obj->frame_count<=0){
  next=obj->next;
  next++;
  if(next >= obj->num_pics) next=0;
  obj->next=next;
  obj->frame_count=obj->frame_speed;
}
}
//===========================================================================
int get_movement(XOBJECT *obj){
int d;

switch(obj->move){
      case 1:
           d=movement_one(obj);
           break;
      case 2:
           d=movement_two(obj);
           break;
      case 3:
           d=movement_three(obj);
           break;
      case 4:
           d=movement_four(obj);
           break;
      case 6:
           d=movement_six(obj);
           break;
      case 0:
           return obj->dir;
}
return d;
}
//===========================================================================
int movement_one(XOBJECT *obj){
int d,x,y;

d=obj->dir;

if(key_flag[ALT]) thor_shoots();

if(key_flag[ESC]){
    exit_flag=2;
}
x=obj->x;
y=obj->y;
if(key_flag[UP] && key_flag[LEFT]){
    d=2;
    y-=obj->y_inc;
    x-=obj->x_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;

}
if(key_flag[UP] && key_flag[RIGHT]){
    d=3;
    y-=obj->y_inc;
    x+=obj->x_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;
}
if(key_flag[DOWN] && key_flag[LEFT]){
    d=2;
    y+=obj->y_inc;
    x-=obj->x_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;
}
if(key_flag[DOWN] && key_flag[RIGHT]){
    d=3;
    y+=obj->y_inc;
    x+=obj->x_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;
}
if(key_flag[RIGHT]){
    d=3;
    x+=obj->x_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;
}
if(key_flag[LEFT]){
    d=2;
    x-=obj->x_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;
}
if(key_flag[DOWN]){
    d=1;
    y+=obj->y_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
x=obj->x;
y=obj->y;
}
if(key_flag[UP]){
    d=0;
    y-=obj->y_inc;
    if(check_movement(x,y,obj)){ next_frame(obj);return d;}
}
return d;

if(check_movement(x,y,obj)) next_frame(obj);
return d;
}
//===========================================================================
int check_movement(int x,int y,XOBJECT *obj){
int x1,y1,x2,y2;

if(x > (X_MAX-obj->width)){
  if(obj->type==1){
    current_level++;
    exit_flag=3;
    return 0;
  }
  x=(320-obj->width);
}
if(y > (Y_MAX-obj->height)){
  if(obj->type==1){
    current_level+=10;
    exit_flag=4;
    return 0;
  }
  y=(Y_MAX-obj->height);
}
if(x <=0){
  if(obj->type==1){
    current_level--;
    exit_flag=5;
    return 0;
  }
  x=0;
}
if(y <=0){
  if(obj->type==1){
    current_level-=10;
    exit_flag=6;
    return 0;
  }
}
x2=((x+obj->width)-2)/16;
y2=((y+obj->height))/16;
x1=(x+2)/16;
y1=((y+obj->height)-4)/16;
//x1=(x+2)/16;
//y1=(y+2)/16;
if(obj->type==1){
  if(scrn.icon[y1][x1]>0 && !(scrn.icon[y1][x1] & 16)) return 0;
  if(scrn.icon[y2][x1]>0 && !(scrn.icon[y2][x1] & 16)) return 0;
  if(scrn.icon[y1][x2]>0 && !(scrn.icon[y1][x2] & 16)) return 0;
  if(scrn.icon[y2][x2]>0 && !(scrn.icon[y2][x2] & 16)) return 0;
//  if(scrn.icon[y1][x1]==1) if(!open_door(x1,y1)) return 0;
//  else if(scrn.icon[y2][x1]==1) if(!open_door(x1,y2)) return 0;
//  else if(scrn.icon[y1][x2]==1) if(!open_door(x2,y1)) return 0;
//  else if(scrn.icon[y2][x2]==1) if(!open_door(x2,y2)) return 0;
}
else{
  if(scrn.icon[y1][x1]!=0) return 0;
  if(scrn.icon[y2][x1]!=0) return 0;
  if(scrn.icon[y1][x2]!=0) return 0;
  if(scrn.icon[y2][x2]!=0) return 0;
}
obj->x=x;
obj->y=y;
return 1;
}
//===========================================================================
int movement_two(XOBJECT *obj){
int d;

d=obj->dir;

if(d==3){
  obj->x+=obj->x_inc;
  if(obj->x > (X_MAX-obj->width)){
    obj->x=(320-obj->width);
    return 2;
  }
}
if(d==2){
  obj->x-=obj->x_inc;
  if(obj->x <=0){
    obj->x=0;
    return 3;
  }
}
next_frame(obj);
return d;
}
//===========================================================================
int movement_three(XOBJECT *obj){
int d,x,y;

d=obj->dir;

x=obj->x;
y=obj->y;
if(!check_movement(x,y,obj)){
  d=reverse_direction(obj);
  thorshot.move=6;
  return d;
}
if(d==3) x+=obj->x_inc;
else if(d==2) x-=obj->x_inc;
else if(d==0) y-=obj->y_inc;
else if(d==1) y+=obj->y_inc;

if(!check_movement(x,y,obj)){
//  obj->x=x;
//  obj->y=y;
  d=reverse_direction(obj);
  thorshot.move=6;
  return d;
}
next_frame(obj);
return d;
}
//===========================================================================
int movement_four(XOBJECT *obj){
int d,x1,y1,f;

d=obj->dir;

x1=obj->x;
y1=obj->y;

f=0;
if(x1>(thor.x+obj->x_inc)) {x1-=obj->x_inc;d=2;f=1;}
else if(x1<thor.x-obj->x_inc) {x1+=obj->x_inc;d=3;f=1;}
if(f) f=check_movement(x1,y1,obj);
if(!f){
  x1=obj->x;
  if(y1<thor.y-obj->y_inc) {y1+=obj->y_inc;d=1;f=1;}
  else if(y1>thor.y+obj->y_inc) {y1-=obj->y_inc;d=0;f=1;}
}
if(f) check_movement(x1,y1,obj);
next_frame(obj);

return d;
}
//===========================================================================
int movement_six(XOBJECT *obj){
int x1,y1,xd,yd,d;
static int toggle=0;

x1=obj->x;
y1=obj->y;
xd=yd=0;
d=obj->dir;

if(x1>(thor.x+obj->x_inc)) xd=-1;
else if(x1<thor.x-obj->x_inc) xd=1;

if(y1<thor.y-obj->y_inc) yd=1;
else if(y1>thor.y+obj->y_inc) yd=-1;

if(xd==0 && yd==1) d=1;
else if(xd==0 && yd==-1) d=0;
else if(xd==1 && yd==0) d=3;
else if(xd==-1 && yd==0) d=2;

if(xd!=0 && yd!=0){
    x1+=((obj->x_inc-1)*xd);
    y1+=((obj->y_inc-1)*yd);
    if(check_movement(x1,y1,obj)){
      next_frame(obj);
      return d;
    }
//  else return obj->dir;
}
x1=obj->x;
y1=obj->y;

if(toggle){
  toggle^=1;
  if(xd){
    x1+=(obj->x_inc*xd);
    if(check_movement(x1,y1,obj)){
      next_frame(obj);
      return d;
    }
    x1=obj->x;
  }
  y1+=(obj->y_inc*yd);
  check_movement(x1,y1,obj);
    next_frame(obj);
//  }
  return d;
}
else{
  toggle^=1;
  if(yd){
    y1+=(obj->y_inc*yd);
    if(check_movement(x1,y1,obj)){
      next_frame(obj);
      return d;
    }
    y1=obj->y;
  }
  x1+=(obj->x_inc*xd);
  check_movement(x1,y1,obj);
    next_frame(obj);
//  }
  return d;
}
next_frame(obj);
return d;
}
//===========================================================================
void move_object(int num){
int i;
XOBJECT *obj;

if(object[num]->used!=1) return;
obj=object[num];

if(obj->vunerable!=0) obj->vunerable--;
if(obj->vunerable==35 && num==0){
  in.h.al=0x10;
  in.h.ah=0x10;
  in.x.bx=6;
  in.h.dh=0xaa/4;
  in.h.ch=0x55/4;
  in.h.cl=0x00;
  int86(0x10,&in,&out);
}
if(obj->shot_cnt!=0) obj->shot_cnt--;
obj->count--;
if(obj->count<=0){
  obj->count=obj->speed;
  i=get_movement(obj);
  if(i==-1){
    object_destroyed(num);
    return;
  }
  else if(i!=obj->dir){
    obj->dir=i;
    if(!obj->mono){
      obj->next=0;
      obj->frame_count=obj->frame_speed;
    }
  }
}
else i=obj->dir;

if(check_for_hit(obj,num)) return;

obj->x &= 0xfffe;
xcopyd2dmasked2(obj->width+1,obj->height+1,
               obj->x,obj->y,obj->pic[i][obj->next],
               draw_page);
obj->last_x[pge]=obj->x;
obj->last_y[pge]=obj->y;
}
//===========================================================================
void object_destroyed(int num){
unsigned int p;

erase_object(num);
p=draw_page;
draw_page=display_page;
object[num]->last_x[pge]=object[num]->last_x[pge^1];
object[num]->last_y[pge]=object[num]->last_y[pge^1];
erase_object(num);
draw_page=p;
object[num]->used=0;
if(num>3 && num<9) add_jewel(object[num]->x,object[num]->y);
}
//===========================================================================
void erase_object(int num){
int x,y;
unsigned int a;

if(object[num]->used==1){
  x=object[num]->last_x[pge];
  y=object[num]->last_y[pge];
    a=PAGE2;
    xcopyd2d(x,y,x+object[num]->width+1,y+object[num]->height+1,
            x,y,a,draw_page, 320,320);
}
}
//===========================================================================
void thor_shoots(void){

//if(thor.shot_cnt!=0) return;

//for(i=0;i<3;i++){
   if(object[1]->used!=1){
     object[1]=&thorshot;
     thorshot.used=1;
     thorshot.dir=thor.dir;
     thorshot.x=thor.x+2;
     thorshot.y=thor.y+2;
     thorshot.move=3;
     thor.shot_cnt=20;
//     sound_ptr=sound_shoot;
//     sound_cnt=1;
//     sound_level=1;
     output_sound(voice_swish,255);
     return;
   }
//}
}
//===========================================================================
void xprint(int x,int y,char *string,int color,unsigned int page){
char ch;
char str[3];

str[2]=0;
x &= 0xfc;
while(*string){
   ch=*string++;
   if(ch=='/' && *(string+2)=='/'){
     str[0]=*string++;
     str[1]=*string++;
     string++;
     color=atoi(str);
     continue;
   }
   if(ch>32 && ch<91) xtext(x,y,page,text[ch-33],color);
   x+=8;
}
}
//===========================================================================
int check_for_hit(XOBJECT *obj,int num){
int i,x1,y1,x2,y2;

if(num==0){  //thor
     x1=thor.x;
     y1=thor.y;
     x2=thor.x+obj->width;
     y2=thor.y+obj->height;
     for(i=14;i<22;i++){
        if(object[i]->used==1){
          if(overlap(object[i]->x,object[i]->y,object[i]->x+object[i]->width,
                     object[i]->y+object[i]->height,x1,y1,x2,y2)){
            if(object[i]->type==5){
//              sound_ptr=sound_good;
//              sound_cnt=1;
//              sound_level=1;
              output_sound(voice_yah,2);
              thor.money++;
              display_money();
            }
            else if(object[i]->type==6){
//              sound_ptr=sound_good;
//              sound_cnt=1;
//              sound_level=1;
              output_sound(voice_yah,2);
              thor.money+=10;
              display_money();
            }
            else if(object[i]->type==7){
//              sound_ptr=sound_good;
//              sound_cnt=1;
//              sound_level=1;
              output_sound(voice_yah,2);
              thor.keys++;
              display_keys();
            }
            else if(object[i]->type==8){
//              sound_ptr=sound_good;
//              sound_cnt=1;
//              sound_level=1;
              output_sound(voice_drink,1);
              thor.health+=10;
              if(thor.health>50) thor.health=50;
              display_health();
            }
            object_destroyed(i);
            return 0;
          }
        }
     }
}
else if(num<4){  //thor shots
     if(obj->used!=1) return 0;
     if(num!=1) return 0;
     x1=obj->x;
     y1=obj->y;
     x2=obj->x+obj->width;
     y2=obj->y+obj->height;
     if(thorshot.move==6){
       if(overlap(x1,y1,x2,y2,object[0]->x,object[0]->y,
                  object[0]->x+object[0]->width,
                  object[0]->y+object[0]->height)){
         object_destroyed(1);
         thorshot.used=0;
         return 1;
       }
     }
     for(i=4;i<9;i++){
        if(object[i]->used==1){
          if(overlap(x1,y1,x2,y2,object[i]->x,object[i]->y,
                     object[i]->x+object[i]->width,
                     object[i]->y+object[i]->height)){
//            sound_ptr=sound_hit;
//            sound_cnt=1;
//            sound_level=1;
            output_sound(voice_ouch,1);
            if(object_damaged(object[i],obj->strength)){
              object_destroyed(i);
            }
            thorshot.move=6;
            obj->dir=reverse_direction(obj);
            return 0;
          }
        }
     }
}
else if(num<9){  //monster
     if(object[0]->vunerable!=0) return 0;
     x1=obj->x;
     y1=obj->y;
     x2=obj->x+obj->width;
     y2=obj->y+obj->height;
     if(overlap(x1,y1,x2,y2,object[0]->x,object[0]->y,
                object[0]->x+object[0]->width,
                object[0]->y+object[0]->height)){
//       sound_ptr=sound_thit;
//       sound_cnt=1;
//       sound_level=1;
         in.h.al=0x10;
         in.h.ah=0x10;
         in.x.bx=6;
         in.h.dh=0xff/4;
         in.h.ch=0xff/4;
         in.h.cl=0xff/4;
         int86(0x10,&in,&out);
         output_sound(voice_ow[random(3)],1);
       if(object_damaged(object[0],obj->strength)){
         object[0]->health=0;
         object_destroyed(0);
         exit_flag=1;
       }
       object[0]->vunerable=40;
       display_health();
       return 1;
     }
}
else{  //monster shots
  return 0;
}
return 0;
}
/*=========================================================================*/
int point_within(int x,int y,int x1,int y1,int x2,int y2){

if((x<x1) || (x>x2) || (y<y1) || (y>y2)) return 0;
return 1;
}
//===========================================================================
int  overlap(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){

if(point_within(x1,y1,x3,y3,x4,y4)) return 1;
if(point_within(x2,y2,x3,y3,x4,y4)) return 1;
if(point_within(x1,y2,x3,y3,x4,y4)) return 1;
if(point_within(x2,y1,x3,y3,x4,y4)) return 1;
return 0;
}
//===========================================================================
int  object_damaged(XOBJECT *obj,int strength){

if(obj->health<=strength) return 1;
obj->health-=strength;
return 0;
}
//===========================================================================
void display_health(void){
int h;

h=object[0]->health  + 57;

if(h!=57) xfillrectangle(h+1,7,107,12,PAGES,0);
xfillrectangle(57,7,h,12,PAGES,12);
//if(h!=57) xfillrectangle(h+1,199,107,204,PAGE1,0);
//xfillrectangle(57,199,h,204,PAGE1,12);
}
//===========================================================================
void build_level(int level){
int x,y;


movedata(FP_SEG(sd_data+(level*512)),FP_OFF(sd_data+(level*512)),
         FP_SEG(&scrn),FP_OFF(&scrn),512);

xfillrectangle(0,0,320,192,PAGE0,scrn.bg_color);
for(y=0;y<12;y++){
   for(x=0;x<20;x++)
      if(scrn.icon[y][x]!=0){
        xfput(x*16,y*16,PAGE0,(char far *) (bg_pics+(scrn.icon[y][x]*262)));
   }
}
}
//===========================================================================
void display_money(void){
char s[21];

if(thor.money>999) thor.money=999;
xfillrectangle(58,32,84,41,PAGES,0);
//xfillrectangle(58,224,84,233,PAGE1,0);
itoa(thor.money,s,10);
xprint(60,33,s,15,PAGES);
//xprint(60,225,s,15,PAGE1);
}
//===========================================================================
void display_keys(void){
int i;

for(i=0;i<2;i++){
   xfillrectangle(261+i,6+i,275-i,28-i,PAGES,(19+i)*(i!=1));
   xfillrectangle(275+i,6+i,289-i,28-i,PAGES,(19+i)*(i!=1));
   xfillrectangle(289+i,6+i,303-i,28-i,PAGES,(19+i)*(i!=1));

//   xfillrectangle(261+i,198+i,275-i,220-i,PAGE1,(19+i)*(i!=1));
//   xfillrectangle(275+i,198+i,289-i,220-i,PAGE1,(19+i)*(i!=1));
//   xfillrectangle(289+i,198+i,303-i,220-i,PAGE1,(19+i)*(i!=1));
}
for(i=0;i<thor.keys;i++){
   xcopyd2dmasked(0,0, 9,16,264+(i*14),8,&key_image,PAGES,320);
//   xcopyd2dmasked(0,0, 9,16,264+(i*14),200,&key_image,display_page,320);
}
}
//===========================================================================
void add_jewel(int x,int y){
int i;

for(i=14;i<21;i++){
   if(object[i]->used!=1){
     object[i]=&jewel[i-14];
     if(random(10)<5){
       object[i]->type=5;
       object[i]->pic[0][0]=&jewel_blue_image;
     }
     else{
       object[i]->type=6;
       object[i]->pic[0][0]=&jewel_red_image;
     }
     object[i]->used=1;
     object[i]->dir=0;
     object[i]->x=x;
     object[i]->y=y;
     return;
   }
}
}
//===========================================================================
int open_door(int x,int y){

if(thor.keys<=0) return 0;

//sound_ptr=sound_door;
//sound_cnt=1;
//sound_level=1;
output_sound(voice_creek,2);
scrn.icon[y][x]=0;
xfillrectangle(x*16,y*16,(x+1)*16,(y+1)*16,PAGE0,bg_color);
xfillrectangle(x*16,y*16,(x+1)*16,(y+1)*16,PAGE1,bg_color);
xfillrectangle(x*16,y*16,(x+1)*16,(y+1)*16,PAGE2,bg_color);
thor.keys--;
display_keys();
return 1;
}
//===========================================================================
void interrupt timer_int(void){

return;
if(sound_level>0){
  sound_cnt--;
  if(sound_cnt>0) return;
  word=*sound_ptr++;
  sound_cnt=*sound_ptr++;
  if(sound_cnt==0){
    sound_level=0;
    byte=inportb(0x61);
    byte &= 0xfc;
    outportb(0x61,byte);
    return;
  }
  if(word){
    byte=inportb(0x61);
    byte |= 3;
    outportb(0x61,byte);
    outportb(0x43,0xb6);              //10110110B
    byte=word;
    outportb(0x42,byte);
    word=word >> 8;
    byte=word;
    outportb(0x42,byte);
  }
  else{
      byte=inportb(0x61);
      byte &= 0xfc;
      outportb(0x61,byte);
  }
}
}
//===========================================================================
void load_palette(void){
int i;
char buff[1000];
FILE *fp;


fp=fopen("xsprite.pal","rb");
if(!fp) return;

i=fread(buff,768,1,fp);
if(i!=1){fclose(fp);return;}

in.h.al=0x10;
in.h.ah=0x10;
for(i=0;i<256;i++){
   in.x.bx=i;
   in.h.dh=buff[i*3]/4;
   in.h.ch=buff[(i*3)+1]/4;
   in.h.cl=buff[(i*3)+2]/4;
   int86(0x10,&in,&out);
}
fclose(fp);
}
//===========================================================================
int reverse_direction(XOBJECT *obj){

if(obj->dir==0) return 1;
if(obj->dir==1) return 0;
if(obj->dir==2) return 3;
if(obj->dir==3) return 2;
return 5;
}
//===========================================================================
void output_sound(char far* buff,int priority){

if(ct_voice_status){
  if(priority<=sound_priority){
    ctvm_stop();
    output_voice(buff);
    sound_priority=priority;
  }
}
else{
  output_voice(buff);
  sound_priority=priority;
}
}
//===========================================================================
void split_screen(void){

asm{

mov dx,0x03d4
mov al,0x18
out dx,al
inc dx
mov ax,128
out dx,al
dec dx
mov al,7
out dx,al
inc dx
in  al,dx
or  al,0x10
//and al,0xef
out dx,al
dec dx
mov al,9
out dx,al
inc dx
in  al,dx
and al,0xbf
out dx,al
}
}
//===========================================================================
int load_bg_pics(void){
       FILE *fp;
       unsigned int  total,bytes,i;
       char buff[256];
       char far *p;

     bg_pics=0;
     total=0;
     fp=fopen("bgpics.dat","rb");
     if(!fp) return 0;
     fread(bg_header,200,1,fp);
     bg_pics=farmalloc(52600l);
     if(!bg_pics){ fclose(fp); return 0;}
     p=bg_pics;
     while(1){
          bytes=fread(buff,1,256,fp);
          if(bytes==0) break;
          total+=bytes;
          for(i=0;i<bytes;i++) if(buff[i]==15) buff[i]=0;
          movedata(FP_SEG(buff),FP_OFF(buff),FP_SEG(p),FP_OFF(p),bytes);
          p+=bytes;
     }
     fclose(fp) ;
     if(total<52399l) return 0;
     return 1;
}
//===========================================================================
int load_sd_data(void){
       FILE *fp;
       int i;
       unsigned int  total,bytes;
       char buff[256];
       char far *p;

     sd_data=0;
     total=0;
     fp=fopen("scrndata.dat","rb");
     if(!fp) return 0;
     fread(sd_header,128,1,fp);
     sd_data=farmalloc(61440l);
     if(!sd_data){ fclose(fp); return 0;}
     p=sd_data;
     while(1){
          bytes=fread(buff,1,256,fp);
          if(bytes==0) break;
          total+=bytes;
          movedata(FP_SEG(buff),FP_OFF(buff),FP_SEG(p),FP_OFF(p),bytes);
          p+=bytes;
     }
     fclose(fp) ;
     if(total<61439l) return 0;
     return 1;
}
