//#define TESTING 1
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <dir.h>
#include <ctype.h>
#include <conio.h>

#include <maskim.h>
#include <modex.h>
#include <xmouse.h>
//==========================================================================
//typedefs & defines

#define PAGE0  0
#define PAGE1  19200
#define PAGE2  38400u
#define PAGE3  57600u
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

#define NUM_OBJECTS 32

#define MSHIDE xmouse_hide(mx,my)
#define MSSHOW xmouse_show(mx,my)
#define MLB xmouse_lb
#define MRB xmouse_rb
#define MPX xmouse_x
#define MPY xmouse_y

typedef struct{                    //size=40
       char move;                  //movement pattern (0=none)
       char width;                 //physical width
       char height;                //physical height
       char directions;            //1,2 or 4 (1=uni-directional)
       char frames;                //# frames per direction
       char frame_speed;           //# cycles between frame changes
       char frame_sequence[4];     //sequence
       char speed;                 //move every Nth cycle
       char size_x;                 //non-physical padding on X coor
       char size_y;                 //non-phsyical padding on Y coor
       char strength;              //hit strength
       char health;                //
       char num_moves;             //# of moves every <speed> cycles
       char shot_type;             //actor # of shot
       char shot_pattern;          //func number to decide to shoot
       char shots_allowed;         //# shots allowed on screen
       char solid;                 //1=solid (not ghost,etc)
       char flying;                //
       char rating;                //rnd(100) < rating = jewel
       char type;                  //actor (0=thor,1=hammer,2=enemy,3=shot)
       char name[9];               //actors name
       char func_num;              //special function when thor touches
       char func_pass;             //value to pass to func
       int  magic_hurts;           //bitwise magic hurts flags
       char future1[4];
} ACTOR_NFO;

typedef struct {                     //size=16373
       char pic[16][256];            //4096
       char shot[4][256];            //1024
       ACTOR_NFO actor_info;         //40
       ACTOR_NFO shot_info;          //40
//       unsigned int sound_len[3];    //6
//       char hit_sound[9];            //9
//       char dead_sound[9];           //9
//       char shoot_sound[9];          //9
//       char sound[11140];
} ACTOR_DATA;
//==========================================================================
//internal prototypes
void exit_code(void);
void xprint(int x,int y,char *string,int color,unsigned int page);
void xmouse_show(int x,int y);
void xmouse_hide(int x,int y);
void display_mouse_pos(int x,int y);
void draw_grid(void);
void fill_grid_box(int x,int y,int color);
void draw_palette(void);
void display_color(int x,int y);
void get_new_fg(int x,int y);
void get_new_bg(int x,int y);
void display_color_box(void);
void display_pics(void);
void animate(void);
void copy_pic_to_grid(int num);
void display_help(int level);
void status_line(char *message,int color);
int  do_key_function(void);
void load_file(void);
int  read_rim_file(char *filename,int num);
int  xinput(int x,int y,char *buff,int fg,int bg,int max,int min,unsigned int page);
void save_file(void);
int  are_you_sure(char *mess);
void copy_pic_to_pic(int num);
void set_undo(void);
void undo(void);
void flush_buff(void);
void display_enabled(void);
void ask_to_save(void);
void shift_up(void);
void shift_down(void);
void shift_left(void);
void shift_right(void);
void flip_vertical(void);
void flip_horizontal(void);
void mirror_vertical(void);
void mirror_horizontal(void);
void rotate(void);
void no_button(void);
void load_palette(void);
void show_directory(void);
void start_new(void);
void export(void);
void import(void);
int  point_within(int x,int y,int x1,int y1,int x2,int y2);
void pic_import(void);
void pic_export(void);
void color_swap(void);
void set_default_palette(void);
void rotate_palette(void);
void show_help(void);
int  help_pause(void);
void pcx_import(void);
int  select_bgpic(void);
void beep(void);
void load_actor(void);
void save_actor(void);
void edit_actor(void);
void edit_shot(void);
int  input_data(void);
void store_input(ACTOR_NFO *data);
void retrieve_input(ACTOR_NFO *data);
void display_actor_pics(void);
void export_actor_pics(void);
void import_actor_pics(void);
void write_screen(void);
void read_screen(void);
void overlap(void);
//==========================================================================
// external prototypes
void xpset(int X, int Y, unsigned int PageBase, int Color);
void xget(int x1,int y1,int x2,int y2,unsigned int pagebase,
          char *buff,int invis);
void xput(int x,int y,unsigned int pagebase,char *buff);
void xtext(int x,int y,unsigned int pagebase,char *buff,int color);
void xfillrectangle(int StartX, int StartY, int EndX, int EndY,
                    unsigned int PageBase, int Color);
unsigned int xcreatemaskimage(MaskedImage * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask);
void xcopyd2dmasked(int SourceStartX,
     int SourceStartY, int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage * Source,
     unsigned int DestPageBase, int DestBitmapWidth);
void xcopys2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, char* SourcePtr, unsigned int DestPageBase,
     int SourceBitmapWidth, int DestBitmapWidth);
void xcopyd2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, unsigned int SourcePageBase,
     unsigned int DestPageBase, int SourceBitmapWidth,
     int DestBitmapWidth);
unsigned int xpoint(int X, int Y, unsigned int PageBase);
xsetpal(unsigned char color, unsigned char R,unsigned char G,unsigned char B);
xgetpal(char far * pal, int num_colrs, int start_index);

//from XIMP.C

int  pcx_imp(void);
void import_rim(int x1,int y1);
int  select_rim(int *nx,int *ny);
//==========================================================================
//global variables

union REGS in,out;
struct SREGS seg;
int xmouse_x,xmouse_y,xmouse_lb,xmouse_rb;
int xmouse_cnt;
int mx,my,fg,bg;
int active_pic;
int speed;
char filename[9];
char tempstr[255];

char pic[4][300];
char undo_buff[4][300];
char undo_tmp[4][300];
char tmp_pic[300];
int  undo_flag;
int  changed;
char pic_enable[4];
char pcx_filename[9];
int  game_num,area_num;
char level_str[21];
char in_str[20][9];
char slow_mode;

char byte;
unsigned int word;

unsigned int page[3]={PAGE0,PAGE1,PAGE2};
long

// mouse curosr 8x8

static char mcursor[]={
		  0,0,0,0,0,0,0,0,
		  0,7,7,7,7,7,0,0,
		  0,7,7,7,7,0,0,0,
		  0,7,7,7,7,0,0,0,
		  0,7,7,7,7,7,0,0,
		  0,7,0,0,7,7,7,0,
		  0,0,0,0,0,7,7,0,
		  0,0,0,0,0,0,0,0};

static char mmask[]={
		  1,1,1,1,1,1,1,1,
		  1,1,1,1,1,1,1,0,
		  1,1,1,1,1,1,0,0,
		  1,1,1,1,1,1,0,0,
		  1,1,1,1,1,1,1,0,
		  1,1,1,1,1,1,1,1,
		  1,1,0,0,1,1,1,1,
		  1,0,0,0,0,1,1,0};
static MaskedImage mouse_image;

ACTOR_DATA actor;
int actor_num;

char text[60][72];

struct picf{
       char width;
       char height;
};
struct picf pic_header[800];
int ph_flag;

unsigned int display_page;
unsigned int draw_page;
char bg_header[200];
int bg_flag;
int game_num,area_num;
char level_str[21];
char bg_file[21];
char ad_file[21];
char pic_file[21];

char *ea_prompt[]={"            NAME:",
                   "            TYPE:",
                   "MOVEMENT PATTERN:",
                   " # OF DIRECTIONS:",
                   "     # OF FRAMES:",
                   "     FRAME SPEED:",
                   "  FRAME SEQUENCE:",
                   "           SPEED:",
                   "          SIZE X:",
                   "          SIZE Y:",
                   "        STRENGTH:",
                   "          HEALTH:",
                   "      # OF MOVES:",
                   "SHOOTING PATTERN:",
                   "   SHOTS ALLOWED:",
                   "           SOLID:",
                   "          FLYING:",
                   "     MAGIC HURTS:",
                   "SPECIAL FUNCTION:",
                   "  FUNCTION VALUE:"
                  };
//==========================================================================
void main(int argc, char *argv[]){
int i;
FILE *fp;
char lflag,rflag;
int help_level,hl;
int *ip;

memset(text,0x00,60*72);
memset(pcx_filename,0,9);
memset(pic_file,0,12);

if(argc>2){
  game_num=atoi(argv[1]);
  area_num=atoi(argv[2]);
  if(game_num > 3 || game_num<0 || area_num>3 || area_num<0){
    printf("Invalid GAME or AREA Number\r\n");
    exit(0);
  }
  strcpy(level_str,argv[1]);
  strcat(level_str,argv[2]);

}
else{
  game_num=1;
  area_num=1;
  strcpy(level_str,"11");
}
strcpy(bg_file,"\\PG\\PGBG");
strcat(bg_file,level_str);
strcat(bg_file,".DAT");
//if(area_num!=0) bg_file[11]='1';

strcpy(ad_file,"\\PG\\PGAD");
strcat(ad_file,level_str);
strcat(ad_file,".DAT");
if(area_num!=0) ad_file[9]='1';

ph_flag=0;
//fp=fopen("\\PG\\picdata.dat","rb");
//if(fp){
//  if(fread(pic_header,(1600),1,fp) !=1) {fclose(fp);exit(0);}
//  fclose(fp);
//  ph_flag=1;
//}

fp=fopen("\\PG\\text.dat","rb");
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
xmouse_init();
xmouse_off();
xmouse_set_bounds(0,0,624,231);
xmouse_set_pos(320,120);
xmouse_stat();
mx=MPX;
my=MPY;
xmouse_cnt=1;
MSSHOW;
lflag=0;
rflag=0;
fg=15;
bg=0;
active_pic=0;
speed=1600;
help_level=0;
undo_flag=0;
changed=0;
pic_enable[0]=1;
pic_enable[1]=1;
pic_enable[2]=1;
pic_enable[3]=1;

game_num=1;
area_num=1;
strcpy(level_str,"11");

memset(pic[0],0,1200);
for(i=0;i<4;i++){
   ip=(int *) pic[i];
   *ip=2;
   ip++;
   *ip=16;
   ip++;
   *ip=0;
}

if(xcreatmaskimage(&mouse_image,PAGE3,mcursor,8,8,mmask)==0){
  exit_code();
  exit(0);
}

//setup background
xshowpage(PAGE0);
draw_grid();
draw_palette();
display_color_box();
display_pics();
display_help(0);
display_enabled();
load_palette();
set_default_palette();

xprint(224,70, "COOR:",7,PAGE0);
xprint(216,80,"COLOR:",7,PAGE0);

xprint(200,100,"COPYRIGHT 1992,",12,PAGE0);
xprint(200,108,"CUSTOM SOFTWARE",12,PAGE0);
xprint(200,116,"ENGINEERING",12,PAGE0);

xprint(200,144,"HIT H FOR HELP",15,PAGE0);

//
//xcopyd2d(0, 0, 320, 240,     0, 0,PAGE0, PAGE1,320,320);
//xcopyd2d(0, 0, 320, Y_MAX+1, 0, 0,PAGE1, PAGE2,320,320);
start_new();

while(1){
     in.h.ah = 2;
     int86(0x16,&in,&out);
     if(out.h.al & 1) hl=1;         //shift
     else if(out.h.al & 2) hl=1;    //shift
     else if(out.h.al & 4) hl=2;    //ctrl
     else if(out.h.al & 8) hl=3;    //alt
     else hl=0;
     if(hl!=help_level){
	help_level=hl;
	display_help(help_level);
     }
     if(kbhit()){
	if(do_key_function()) break;
       flush_buff();
     }
     xmouse_stat();
     if(MPX!=mx || MPY!=my){
	lflag=0;
	rflag=0;
	MSHIDE;
	mx=MPX;
	my=MPY;
	MSSHOW;
	display_mouse_pos(mx,my);
	display_color(mx,my);
     }
     if(MLB && (!lflag)){
	if(point_within(mx,my,0,0,191,191)){
         fill_grid_box(mx,my,fg);
         changed=1;
       }
	else if(point_within(mx,my,0,200,320,221)) get_new_fg(mx,my);
	else if(point_within(mx,my,203,0,221,17)){
	  active_pic=0;
	  display_pics();
	}
	else if(point_within(mx,my,235,0,253,17)){
	  active_pic=1;
	  display_pics();
	}
	else if(point_within(mx,my,267,0,285,17)){
	  active_pic=2;
	  display_pics();
	}
	else if(point_within(mx,my,299,0,317,17)){
	  active_pic=3;
	  display_pics();
	}
	else if(point_within(mx,my,247,38,265,55)) animate();
	else if(point_within(mx,my,209,22,214,26)){
	  pic_enable[0]^=1;
	  display_enabled();
         no_button();
	}
	else if(point_within(mx,my,241,22,246,26)){
	  pic_enable[1]^=1;
	  display_enabled();
         no_button();
	}
	else if(point_within(mx,my,273,22,278,26)){
	  pic_enable[2]^=1;
	  display_enabled();
         no_button();
	}
	else if(point_within(mx,my,305,22,310,26)){
	  pic_enable[3]^=1;
	  display_enabled();
         no_button();
	}
	lflag=1;
     }
     else if(MRB && (!rflag)){
	if(point_within(mx,my,0,0,191,191)) fill_grid_box(mx,my,bg);
	else if(point_within(mx,my,0,200,320,221)) get_new_bg(mx,my);
	else if(point_within(mx,my,203,0,221,17)) copy_pic_to_pic(0);
	else if(point_within(mx,my,235,0,253,17)) copy_pic_to_pic(1);
	else if(point_within(mx,my,267,0,285,17)) copy_pic_to_pic(2);
	else if(point_within(mx,my,299,0,317,17)) copy_pic_to_pic(3);
	rflag=1;
     }
}

exit_code();
exit(0);
}
//===========================================================================
void exit_code(void){
union REGS regset;

regset.x.ax = 0x0003; int86(0x10, &regset, &regset);
//chdir("\\bc");
}
//===========================================================================
int do_key_function(void){
int key;

key=getch();
if(key!=0){
  key=toupper(key);
  if(key==9){
    MSHIDE;
    fg=xpoint(mx,my,PAGE0);
    display_color_box();
    MSSHOW;
  }
  if(key=='H'){           //help
    show_help();
  }
  return 0;
}
key=getch();

switch(key){
      case 15:           //shift-tab
	    MSHIDE;
	    bg=xpoint(mx,my,PAGE0);
	    display_color_box();
	    MSSHOW;
	    break;
      case 75:
	    MSHIDE;
	    if(pic_enable[0]+pic_enable[1]+pic_enable[2]+pic_enable[3]<2){
	      status_line("Error...At Least 2 Pics must be Enabled.",12);
	      getch();
	      display_help(0);
	      MSSHOW;
	      return 0;
           }
	    for(key=0;key<4;key++){
		active_pic--;
		if(active_pic<0) active_pic=3;
		if(pic_enable[active_pic]){
		  display_pics();
		  MSSHOW;
                flush_buff();
                return 0;
              }
	    }
           MSSHOW;
	    break;
      case 77:
	    MSHIDE;
	    if(pic_enable[0]+pic_enable[1]+pic_enable[2]+pic_enable[3]<2){
	      status_line("Error...At Least 2 Pics must be Enabled.",12);
	      getch();
	      display_help(0);
	      MSSHOW;
	      return 0;
           }
	    for(key=0;key<4;key++){
		active_pic++;
		if(active_pic>3) active_pic=0;
		if(pic_enable[active_pic]){
		  display_pics();
		  MSSHOW;
                flush_buff();
                return 0;
              }
	    }
           MSSHOW;
	    break;
      case 59:           //F1
	    save_file();
	    break;
      case 60:           //F2
           ask_to_save();
	    load_file();
	    break;
      case 61:           //F3
	    undo();
	    break;
      case 62:           //F4
	    set_undo();
	    MSHIDE;
	    memset(&pic[active_pic][6],bg,256);
	    xfillrectangle(204+(active_pic*32),1,
			     220+(active_pic*32),17,PAGE0,bg);
	    xput(204+(active_pic*32),1,PAGE0,pic[active_pic]);
	    copy_pic_to_grid(active_pic);
	    MSSHOW;
           changed=1;
	    break;
      case 63:           //F5
           ask_to_save();
           if(are_you_sure("Quit")) return 1;
	    break;
      case 64:           //F6
           rotate_palette();
           break;
      case 84:          //shift F1
           set_undo();
           shift_up();
           break;
      case 85:
           set_undo();
           shift_down();
           break;
      case 86:
           set_undo();
           shift_left();
           break;
      case 87:
           set_undo();
           shift_right();
           break;
      case 88:
           load_actor();
           break;
      case 89:
           save_actor();
           break;
      case 90:
           edit_actor();
           break;
      case 91:
           edit_shot();
           break;
      case 94:          //ctrl-F1
           set_undo();
           flip_vertical();
           break;
      case 95:
           set_undo();
           flip_horizontal();
           break;
      case 96:
           set_undo();
           mirror_vertical();
           break;
      case 97:
           set_undo();
           mirror_horizontal();
           break;
      case 98:
           set_undo();
           rotate();
           break;
      case 104:         //alt-F1
           show_directory();
           break;
      case 105:           //alt-f2
           if(are_you_sure("START NEW")) start_new();
	    break;
      case 106:           //alt-f3
           set_undo();
           export();
           break;
      case 107:           //alt-f4
           set_undo();
           import();
           break;
      case 108:           //alt-f5
           set_undo();
           pcx_import();
           break;
      case 109:           //alt-f6
           write_screen();
           break;
//      case 110:           //alt-f7
//           read_screen();
//           break;
      case 23:            //alt-I
           set_undo();
           import_actor_pics();
           break;
      case 18:            //alt-E
           export_actor_pics();
           break;
      case 31:            //alt-S
           set_undo();
           color_swap();
           break;
      case 24:            //alt-O
           set_undo();
           overlap();
           break;

}
return 0;
}
//===========================================================================
void xprint(int x,int y,char *string,int color,unsigned int page){
char ch;
char str[3];

str[2]=0;
x &= 0xfffc;
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
/*=========================================================================*/
int point_within(int x,int y,int x1,int y1,int x2,int y2){

if((x<x1) || (x>x2) || (y<y1) || (y>y2)) return 0;
return 1;
}
/*=========================================================================*/
void xmouse_show(int x,int y){

if(xmouse_cnt==1){
  xcopyd2d(x,y,x+8,y+8,x,y,PAGE0,PAGE2,320,320);
  xcopyd2dmasked(0,0,8,8,x,y,&mouse_image,0,320);
  xmouse_cnt=0;
}
else xmouse_cnt--;
}
/*=========================================================================*/
void xmouse_hide(int x,int y){

if(xmouse_cnt==0) xcopyd2d(x,y,x+8,y+8,x,y,PAGE2,PAGE0,320,320);
xmouse_cnt++;
}
/*=========================================================================*/
void display_mouse_pos(int x,int y){
char s[21];

MSHIDE;
xfillrectangle(264,70,312,78,PAGE0,0);
if(point_within(x,y,0,0,191,191)){
  x/=12;
  itoa(x,s,10);
  xprint(264+((2-strlen(s))*8),70,s,14,PAGE0);
  xprint(280,70,",",7,PAGE0);
  y/=12;
  itoa(y,s,10);
  xprint(288,70,s,14,PAGE0);
}
MSSHOW;
}
/*=========================================================================*/
void display_color(int x,int y){
char s[21];

MSHIDE;
xfillrectangle(264,80,288,96,PAGE0,0);
if(point_within(x,y,0,0,191,191) || point_within(x,y,0,200,320,221)){
  itoa(xpoint(x,y,PAGE0),s,10);
  xprint(264+((3-strlen(s))*8),80,s,14,PAGE0);
}
MSSHOW;
}
/*=========================================================================*/
void draw_grid(void){
int x;

MSHIDE;
for(x=0;x<17;x++){
   xline(x*12,0,x*12,192,8,PAGE0);
   xline(0,x*12,192,x*12,8,PAGE0);
}
MSSHOW;
}
/*=========================================================================*/
void draw_palette(void){
int x;

MSHIDE;
xline(0,199,319,199,14,PAGE0);
xline(0,221,319,221,14,PAGE0);
for(x=0;x<63;x++){
   xfillrectangle((x*5),200,(x*5)+5,206,PAGE0,x);
   xfillrectangle((x*5),205,(x*5)+5,211,PAGE0,x+63);
   xfillrectangle((x*5),210,(x*5)+5,216,PAGE0,x+126);
   xfillrectangle((x*5),215,(x*5)+5,221,PAGE0,x+189);
}
MSSHOW;
}
/*=========================================================================*/
void fill_grid_box(int x,int y,int color){

MSHIDE;
x/=12;
y/=12;
xfillrectangle((x*12)+1,(y*12)+1,(x*12)+12,(y*12)+12,PAGE0,color);
xpset(x+(204+(active_pic*32)),y+1,PAGE0,color);
MSSHOW;
}
/*=========================================================================*/
void xbox(int x1,int y1,int x2,int y2,int color,unsigned page){

xline(x1,y1,x2,y1,color,page);
xline(x1,y2,x2,y2,color,page);
xline(x1,y1,x1,y2,color,page);
xline(x2,y1,x2,y2,color,page);
}
/*=========================================================================*/
void display_color_box(void){

xfillrectangle(245,177,262,194,PAGE0,bg);
xfillrectangle(249,181,258,190,PAGE0,fg);
xbox(244,176,262,194,14,PAGE0);

}
//=========================================================================
int xinput(int x,int y,char *buff,int fg,int bg,
           int max,int min,unsigned int page){

int key;
int pos;
char ch;
char s[2];
MSHIDE;
xfillrectangle(x,y,x+(max*8),y+8,page,bg);
xprint(x,y,buff,fg,page);
pos=strlen(buff);
if(min==-1){
  MSSHOW;
  return 0;
}

while(1){
     if(kbhit()){
	key=getch();
	if(key==0){getch(); continue;}
	else if(key==13){
	   if(pos>=min){
	     buff[pos]=0;
	     MSSHOW;
	     return 1;
	   }
	}
	else if(key==27){
	  buff[pos]=0;
	  MSSHOW;
	  return 0;
	}
	else if(key==8 && pos>0){
	  pos--;
	  xfillrectangle(x+(pos*8),y,x+(pos*8)+8,y+8,page,bg);
	  buff[pos]=0;
	}
	else if(isprint(key) && (pos<max)){
	  key=toupper(key);
	  ch=key;
	  s[0]=ch;
	  s[1]=0;
	  xprint(x+(pos*8),y,s,fg,page);
	  buff[pos++]=ch;
	  buff[pos]=0;
	}
     }
}
}
/*=========================================================================*/
void get_new_fg(int x,int y){

MSHIDE;
fg=xpoint(x,y,PAGE0);
display_color_box();
MSSHOW;
}
/*=========================================================================*/
void get_new_bg(int x,int y){

MSHIDE;
bg=xpoint(x,y,PAGE0);
display_color_box();
MSSHOW;
}
/*=========================================================================*/
void display_pics(void){
int i,x,y,c;

MSHIDE;
for(i=0;i<4;i++)
   xbox(203+(i*32),0,220+(i*32),17,14-(2*(i==active_pic)),PAGE0);

xbox(247,38,264,55,14,PAGE0);

for(y=0;y<16;y++){
   for(x=0;x<16;x++){
      c=xpoint(204+x+(active_pic*32),y+1,PAGE0);
      xfillrectangle((x*12)+1,(y*12)+1,(x*12)+12,(y*12)+12,PAGE0,c);
   }
}
xget(204+(active_pic*32),1,219+(active_pic*32),16,PAGE0,
     pic[active_pic],0);
xfillrectangle(248,39,264,55,PAGE0,0);
xput(248,39,PAGE0,pic[active_pic]);
MSSHOW;
}
/*=========================================================================*/
void display_enabled(void){
int i;

MSHIDE;
for(i=0;i<4;i++){
   xbox(209+(i*32),22,214+(i*32),26,14,PAGE0);
   if(pic_enable[i]) xfillrectangle(210+(i*32),23,214+(i*32),26,PAGE0,12);
   else xfillrectangle(210+(i*32),23,214+(i*32),26,PAGE0,0);
}
MSSHOW;
}
/*=========================================================================*/
void animate(void){
int i,spd;
int key,delay;

MSHIDE;
if(pic_enable[0]+pic_enable[1]+pic_enable[2]+pic_enable[3]<2){
  status_line("Error...At Least 2 Pics must be Enabled.",12);
  getch();
  display_help(0);
  MSSHOW;
  return;
}
status_line("ESC/15/ Stop /14/UP,DN,PGUP,PGDN/15/ Change Speed",14);
for(i=0;i<4;i++) xget(204+(i*32),1,219+(i*32),16,PAGE0,pic[i],255);

i=0;
spd=3000;
while(1){
     if(kbhit()){
	key=getch();
	if(key==27) break;
	if(key==0){
	  key=getch();
	  if(key==UP) speed--;
	  else if(key==DOWN) speed++;
	  else if(key==PGUP) speed-=10;
	  else if(key==PGDN) speed+=10;
	  if(speed<0) speed=0;
	  else if(speed>5000) speed=5000;
	}
     }
     if(spd>=speed){
//        xfillrectangle(248,39,264,55,PAGE0,0);
	xput(248,39,PAGE0,pic[i++]);
	spd=0;
     }
     if(i>3) i=0;
     while(!pic_enable[i]){
	   i++;
	   if(i>3) i=0;
     }
     for(delay=0;delay<50;delay++);
     spd++;
}
MSSHOW;
display_help(0);
}

/*=========================================================================*/
void copy_pic_to_grid(int num){
int x,y,c;

MSHIDE;
for(y=0;y<16;y++){
   for(x=0;x<16;x++){
      c=xpoint(204+x+(num*32),y+1,PAGE0);
      fill_grid_box(x*12,y*12,c);
   }
}
MSSHOW;
}
/*=========================================================================*/
void status_line(char *message,int color){

strupr(message);
MSHIDE;
xfillrectangle(0,231,320,240,PAGE0,0);
xprint(0,231,message,color,PAGE0);
MSSHOW;
}
/*=========================================================================*/
void display_help(int level){

MSHIDE;
xfillrectangle(0,231,320,240,PAGE0,0);
switch(level){
      case 0:
	    xprint(0,231,
	    "F1 /15/SV/14/ F2 /15/LD/14/ F3 /15/UN/14/ F4 /15/CLR/14/ F5 /15/QUIT/14/ F6 /15/PAL",14,PAGE0);
	     break;
      case 1:
	    xprint(0,231,
	    "F1 /15/UP/14/ F2 /15/DN/14/ F3 /15/LF/14/ F4 /15/RT/14/ F5 /15/LDA/14/ F6 /15/SVA",14,PAGE0);
	     break;
      case 2:
	    xprint(0,231,
	    "F1 /15/VFLP/14/ F2 /15/HFLP/14/ F3 /15/VMIR/14/ F4 /15/HMIR/14/ F5 /15/ROT",14,PAGE0);
	     break;
      case 3:
	    xprint(0,231,
	    "F1 /15/DIR/14/ F2 /15/NEW/14/ F3 /15/EXP/14/ F4 /15/IMP/14/ F5 /15/PCX IMP",14,PAGE0);
	     break;
}
MSSHOW;
}
/*=========================================================================*/
void save_file(void){
int i,p;
FILE *fp;
char str[80];


status_line("Save:",14);
strcpy(str,filename);
if(!xinput(48,231,str,15,4,8,1,PAGE0)){
  display_help(0);
  return;
}
strcpy(filename,str);
strcpy(str,"\\PG\\rim\\");
strcat(str,filename);
strcat(str,".rim");

fp=fopen(str,"rb");
if(fp){
  fclose(fp);
  if(!are_you_sure("Overwrite")) return;
}
fp=fopen(str,"wb");
if(!fp){
  status_line("Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
MSHIDE;
for(i=0;i<4;i++){
   xget(204+(i*32),1,219+(i*32),16,PAGE0,pic[i],0);
   for(p=0;p<256;p++) pic[i][p+6]^=p;
   fwrite(pic[i],262,1,fp);
}
MSSHOW;
fclose(fp);
display_help(0);
changed=0;
}
/*=========================================================================*/
void load_file(void){
int i,p;
FILE *fp;
char str[80];

status_line("Load:",14);
strcpy(str,filename);
if(!xinput(48,231,str,15,4,8,1,PAGE0)){
  display_help(0);
  return;
}
strcpy(filename,str);
strcpy(str,"\\PG\\rim\\");
strcat(str,filename);
strcat(str,".rim");
fp=fopen(str,"rb");
if(!fp){
  status_line("File Not Found...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
MSHIDE;
for(i=0;i<4;i++){
   xfillrectangle(204+(i*32),1,220+(i*32),17,PAGE0,0);
   fread(pic[i],262,1,fp);
   for(p=0;p<256;p++) pic[i][p+6]^=p;
   xput(204+(i*32),1,PAGE0,pic[i]);
}
MSSHOW;
fclose(fp);
copy_pic_to_grid(active_pic);
display_help(0);
changed=0;
}
/*=========================================================================*/
int read_rim_file(char *filename,int num){
int i,x,y,sx,sy;
char ch;
FILE *fp;

strcpy(tempstr,"\\PG\\rim\\");
strcat(tempstr,filename);
fp=fopen(tempstr,"rb");
if(!fp) return 0;


x=204+(num*32);
y=1;
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
   if(y>sy){
     y=1;
     x++;
   }
}
fclose(fp);
return 1;
}
/*=========================================================================*/
int are_you_sure(char *mess){
int key;
char s[80];

strcpy(s,mess);
strcat(s,": Are You Sure? ");
strcat(s,"(Y/N)");
status_line(s,12);
flush_buff();
while(1){
     key=toupper(getch());
     if(key=='Y'){key=1;break;}
     else if((key=='N') || (key==27)){key=0;break;}
}
display_help(0);
return key;
}
/*=========================================================================*/
void copy_pic_to_pic(int num){
char s[80];
char s1[21];

MSHIDE;
strcpy(s,"Copy Pic");
itoa(num+1,s1,10);
strcat(s,s1);
strcat(s," to Pic");
itoa(active_pic+1,s1,10);
strcat(s,s1);
if(are_you_sure(s)){
  set_undo();
  copy_pic_to_grid(num);
  changed=1;
}
MSSHOW;
}
/*=========================================================================*/
void set_undo(void){
int i;

MSHIDE;
for(i=0;i<4;i++) xget(204+(i*32),1,219+(i*32),16,PAGE0,undo_buff[i],0);
MSSHOW;
undo_flag=1;
}
/*=========================================================================*/
void undo(void){
int i;

if(!undo_flag) return;

MSHIDE;
for(i=0;i<4;i++) xget(204+(i*32),1,219+(i*32),16,PAGE0,undo_tmp[i],0);
for(i=0;i<4;i++){
   xfillrectangle(204+(i*32),1,220+(i*32),17,PAGE0,0);
   xput(204+(i*32),1,PAGE0,undo_buff[i]);
}
copy_pic_to_grid(active_pic);
MSSHOW;
memcpy(undo_buff,undo_tmp,1200);
}
/*=========================================================================*/
void flush_buff(void){

while(kbhit()) getch();
}
/*=========================================================================*/
void ask_to_save(void){
int key;

changed=0;
if(!changed) return;

status_line("Do You Wish To Save First? (Y/N)",14);
flush_buff();
while(1){
     key=toupper(getch());
     if(key=='Y') break;
     else if((key=='N')) return;
}
save_file();
}
/*=========================================================================*/
void shift_up(void){
int i;

i=active_pic;
MSHIDE;
xget(204+(i*32),2,219+(i*32),16,PAGE0,tmp_pic,0);
xfillrectangle(204+(i*32),1,220+(i*32),17,PAGE0,0);
xput(204+(i*32),1,PAGE0,tmp_pic);
for(i=0;i<16;i++) xpset(i+204+(active_pic*32),16,PAGE0,bg);
copy_pic_to_grid(active_pic);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void shift_down(void){
int i;

i=active_pic;
MSHIDE;
xget(204+(i*32),1,219+(i*32),15,PAGE0,tmp_pic,0);
xfillrectangle(204+(i*32),1,220+(i*32),17,PAGE0,0);
xput(204+(i*32),2,PAGE0,tmp_pic);
for(i=0;i<16;i++) xpset(i+204+(active_pic*32),1,PAGE0,bg);
copy_pic_to_grid(active_pic);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void shift_left(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
for(x=0;x<15;x++){
   for(y=0;y<16;y++){
      ch=xpoint(205+x+(i*32),y+1,PAGE0);
      xpset(204+x+(i*32),y+1,PAGE0,ch);
   }
}
for(x=0;x<16;x++) xpset(219+(i*32),x+1,PAGE0,bg);
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void shift_right(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
for(x=14;x>=0;x--){
   for(y=0;y<16;y++){
      ch=xpoint(204+x+(i*32),y+1,PAGE0);
      xpset(205+x+(i*32),y+1,PAGE0,ch);
   }
}
for(x=0;x<16;x++) xpset(204+(i*32),x+1,PAGE0,bg);
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void mirror_horizontal(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
for(x=0;x<16;x++){
   for(y=0;y<8;y++){
      ch=xpoint(204+x+(i*32),y+1,PAGE0);
      xpset(204+x+(i*32),(15-y)+1,PAGE0,ch);
   }
}
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void mirror_vertical(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
for(x=0;x<8;x++){
   for(y=0;y<16;y++){
      ch=xpoint(204+x+(i*32),y+1,PAGE0);
      xpset(((204+15)-x)+(i*32),y+1,PAGE0,ch);
   }
}
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void flip_horizontal(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
xfillrectangle(248,39,264,55,PAGE0,0);
xget(204+(i*32),1,219+(i*32),16,PAGE0,tmp_pic,0);
xput(248,39,PAGE0,tmp_pic);
for(x=0;x<16;x++){
   for(y=0;y<16;y++){
      ch=xpoint(248+x,y+39,PAGE0);
      xpset(204+x+(i*32),(15-y)+1,PAGE0,ch);
   }
}
xget(204+(i*32),1,219+(i*32),16,PAGE0,tmp_pic,0);
xfillrectangle(248,39,264,55,PAGE0,0);
xput(248,39,PAGE0,tmp_pic);
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void flip_vertical(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
xfillrectangle(248,39,264,55,PAGE0,0);
xget(204+(i*32),1,219+(i*32),16,PAGE0,tmp_pic,0);
xput(248,39,PAGE0,tmp_pic);
for(x=0;x<16;x++){
   for(y=0;y<16;y++){
      ch=xpoint(248+x,y+39,PAGE0);
      xpset(204+(15-x)+(i*32),y+1,PAGE0,ch);
   }
}
xget(204+(i*32),1,219+(i*32),16,PAGE0,tmp_pic,0);
xfillrectangle(248,39,264,55,PAGE0,0);
xput(248,39,PAGE0,tmp_pic);
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void rotate(void){
int i,x,y;
char ch;

i=active_pic;
MSHIDE;
xfillrectangle(248,39,264,55,PAGE0,0);
xget(204+(i*32),1,219+(i*32),16,PAGE0,tmp_pic,0);
xput(248,39,PAGE0,tmp_pic);
for(x=0;x<16;x++){
   for(y=0;y<16;y++){
      ch=xpoint(248+x,y+39,PAGE0);
      xpset(204+(15-y)+(i*32),x+1,PAGE0,ch);
   }
}
xget(204+(i*32),1,219+(i*32),16,PAGE0,tmp_pic,0);
xfillrectangle(248,39,264,55,PAGE0,0);
xput(248,39,PAGE0,tmp_pic);
copy_pic_to_grid(i);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void no_button(void){

while(MLB || MRB) xmouse_stat();
}
/*=========================================================================*/
#define DAC_READ_INDEX	03c7h
#define DAC_WRITE_INDEX 03c8h
#define DAC_DATA	03c9h

void load_palette(void){
int i;
char buff[1000];
FILE *fp;
char r,g,b,n;

fp=fopen("\\PG\\palette.dat","rb");
if(!fp) return;

i=fread(buff,768,1,fp);
if(i!=1){fclose(fp);return;}

in.h.al=0x10;
in.h.ah=0x10;

for(i=0;i<256;i++){
   n=i;
   r=buff[i*3]/4;
   g=buff[(i*3)+1]/4;
   b=buff[(i*3)+2]/4;
   asm mov  al,n
   asm mov  dx,DAC_WRITE_INDEX  // Tell DAC what colour index to
   asm out  dx,al               // write to
   asm mov  dx,DAC_DATA

   asm mov  bl,r
   asm mov  al,bl              // Set the red component
   asm out  dx,al

   asm mov  ch,g
   asm mov  al,ch              // Set the green component
   asm out  dx,al

   asm mov  cl,b
   asm mov  al,cl              // Set the blue component
   asm out  dx,al
}
fclose(fp);
}
/*=========================================================================*/
void xcls(int color,unsigned int page){

MSHIDE;
xfillrectangle(0,0,320,240,page,color);
MSSHOW;
}
/*=========================================================================*/
void show_directory(void){
struct ffblk ffblk;
int done,y,key;
char *p;

MSHIDE;
xcls(0,PAGE1);
xshowpage(PAGE1);
y=0;
done = findfirst("\\PG\\rim\\*.rim",&ffblk,0);
while(!done){
     p=ffblk.ff_name;
     while(*p){
       if(*p=='.'){
         *p=0;
         break;
       }
       p++;
     }
     xprint(0,y,ffblk.ff_name,7,PAGE1);
     done=findnext(&ffblk);
     y+=10;
     if(y>200){
       xprint(0,231,"PRESS ANY KEY...",14,PAGE1);
       key=getch();
       if(key==27){
         xshowpage(PAGE0);
         MSSHOW;
         return;
       }
       xcls(0,PAGE1);
       y=0;
     }
}
xprint(0,231,"PRESS ANY KEY...",14,PAGE1);
key=getch();
xshowpage(PAGE0);
MSSHOW;
}
/*=========================================================================*/
void start_new(void){
int key;

set_undo();
MSHIDE;
for(key=0;key<4;key++){
   memset(&pic[key][6],bg,256);
   xfillrectangle(204+(key*32),1,
                  220+(key*32),17,PAGE0,bg);
   xput(204+(key*32),1,PAGE0,pic[key]);
}
active_pic=0;
copy_pic_to_grid(active_pic);
display_pics();
filename[0]=0;
MSSHOW;
changed=0;
}
/*=========================================================================*/
int select_bgpic(void){
int x,y,i,li;
FILE *fp;
char ipic[262];
int *ip;

fp=fopen(bg_file,"rb+");
if(!fp){
  status_line("File Open Error...Press Any Key.",12);
  getch();
  display_help(0);
  return -1;
}

if(fseek(fp,200l,SEEK_SET)){
  fclose(fp);
  status_line("File Seek Error...Press Any Key.",12);
  getch();
  display_help(0);
  return -1;
}
x=0;
y=0;

for(i=0;i<262;i++){
   if(fread(ipic,262,1,fp) !=1){
     fclose(fp);
     status_line("File Read Error...Press Any Key.",12);
     getch();
     display_help(0);
     return -1;
   }
   ip=(int *) ipic;
   *ip=4;
   ip++;
   *ip=16;
   ip++;
   *ip=0;
   xput(x*16,y*16,PAGE1,ipic);
   x++;
   if(x>=20){
     x=0;
     y++;
   }
}
fclose(fp);

xcopyd2d(0,0,8,8,0,0,PAGE1,PAGE2,320,320);
xcopyd2dmasked(0,0,8,8,0,0,&mouse_image,PAGE1,320);
x=y=0;
xshowpage(PAGE1);
li=-1;
while(1){
     if(kbhit()) if(getch()==27) return -1;
     xmouse_stat();
     if(MPX!=x || MPY !=y){
       xcopyd2d(x,y,x+8,y+8,x,y,PAGE2,PAGE1,320,320);
       x=MPX;
       y=MPY;
       xcopyd2d(x,y,x+8,y+8,x,y,PAGE1,PAGE2,320,320);
       xcopyd2dmasked(0,0,8,8,x,y,&mouse_image,PAGE1,320);
       i=((y/16)*20)+(x/16);
       if((i!=li) && (i<262)){
         xfillrectangle(216,231,320,240,PAGE1,0);
         i=((y/16)*20)+(x/16);
         itoa(i,tempstr,10);
         xprint(216,231,"#",14,PAGE1);
         xprint(224,231,tempstr,14,PAGE1);
         if(i<80) xprint(256,231,"SOLID",14,PAGE1);
         else if(i<140) xprint(256,231,"FLY",14,PAGE1);
         else if(i<200) xprint(256,231,"WALK",14,PAGE1);
         else if(i<230) xprint(256,231,"SPECIAL",14,PAGE1);
         else xprint(256,231,"OBJECT",14,PAGE1);

         li=i;
       }
     }
     if(MLB){
       xcopyd2d(x,y,x+8,y+8,x,y,PAGE2,PAGE1,320,320);
       return i;
     }
     if(MRB) return -1;
}
}
/*=========================================================================*/
void import(void){
int i,x,y;

MSHIDE;
xcls(0,PAGE1);
xprint(0,231,"POINT & CLICK LB TO IMPORT",14,PAGE1);

i=select_bgpic();
no_button();
if(i<262 && i>=0){
  y=(i/20)*16;
  x=(i%20)*16;
  xget(x,y,x+15,y+15,PAGE1,pic[active_pic],0);
  xfillrectangle(204+(active_pic*32),1,220+(active_pic*32),17,PAGE0,0);
  xput(204+(active_pic*32),1,PAGE0,pic[active_pic]);
  display_pics();
}
xshowpage(PAGE0);
xcls(0,PAGE1);
MSSHOW;
}
/*=========================================================================*/
void export(void){
int i;
FILE *fp;

MSHIDE;
xcls(0,PAGE1);
xprint(0,231,"POINT & CLICK LB TO EXPORT",14,PAGE1);

loop1:
i=select_bgpic();
no_button();
xshowpage(PAGE0);
xcls(0,PAGE1);

if(i<262 && i >=0){
  fp=fopen(bg_file,"rb+");
  if(!fp){
    status_line("File Open Error...Press Any Key.",12);
    getch();
    display_help(0);
    return;
  }
  if(fseek(fp,(long) (((long) i*262l)+200l),SEEK_SET)){
    fclose(fp);
    status_line("File Seek Error...Press Any Key.",12);
    getch();
    display_help(0);
    return;
  }
  xget(204+(active_pic*32),1,219+(active_pic*32),16,PAGE0,pic[active_pic],255);
  if(fwrite(pic[active_pic],262,1,fp) !=1){
    fclose(fp);
    status_line("File Write Error...Press Any Key.",12);
    getch();
    display_help(0);
    return;
  }
  fclose(fp);
}
//else return;
//goto loop1;
MSSHOW;
}
/*=========================================================================*/
void pic_export(void){
int i,key,x,y,r;
char buff[256];
char str[21];
FILE *fp;
char width,height;
long offset;

if(!ph_flag) return;
status_line("PIC Number to EXPORT: ",14);
flush_buff();
strcpy(str,"");
if(!xinput(22*8,231,str,15,4,3,1,PAGE0)){
  display_help(0);
  return;
}
i=atoi(str);
if(i<0 || i >799){
  status_line("Out of Range...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
if(pic_header[i].width){
  status_line("Do You Want to Overwrite? (Y/N)",14);
  flush_buff();
  while(1){
       key=toupper(getch());
       if(key=='Y') break;
       else if((key=='N')){
         display_help(0);
         return;
       }
  }
}
height=16;
width=16;
fp=fopen("\\PG\\picdata.dat","rb+");
if(!fp){
  status_line("File Open Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
offset=((long)i*256)+1600;
if(fseek(fp,offset,SEEK_SET)){
  fclose(fp);
  status_line("File Seek Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
memset(buff,255,256);
MSHIDE;
r=0;
for(y=0;y<height;y++){
   for(x=0;x<width;x++){
      buff[r++]=xpoint(204+(active_pic*32)+x,y+1,PAGE0);
   }
}
MSSHOW;
if(fwrite(buff,256,1,fp) !=1){
  fclose(fp);
  status_line("File Write Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
pic_header[i].width=width;
pic_header[i].height=height;
fseek(fp,0l,SEEK_SET);
fwrite(pic_header,1600,1,fp);
fclose(fp);
}
/*=========================================================================*/
void pic_import(void){
int i,x,y,r;
char str[21];
char buff[256];
FILE *fp;
long offset;

if(!ph_flag) return;
status_line("PIC Number to IMPORT: ",14);
flush_buff();
strcpy(str,"");
if(!xinput(22*8,231,str,15,4,3,1,PAGE0)){
  display_help(0);
  return;
}
i=atoi(str);
if(i<0 || i >799){
  status_line("Out of Range...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
fp=fopen("\\PG\\picdata.dat","rb");
if(!fp){
  status_line("File Open Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
offset=((long) i*256)+1600;
if(fseek(fp,offset,SEEK_SET)){
  fclose(fp);
  status_line("File Seek Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
if(fread(buff,256,1,fp) !=1){
  fclose(fp);
  status_line("File Read Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
fclose(fp);
MSHIDE;
r=active_pic;
xfillrectangle(204+(r*32),1,220+(r*32),17,PAGE0,0xff);
r=0;
for(y=0;y<pic_header[i].height;y++){
   for(x=0;x<pic_header[i].width;x++){
      xpset(204+(active_pic*32)+x,y+1,PAGE0,buff[r++]);
   }
}
r=active_pic;
xget(204+(r*32),1,219+(r*32),16,PAGE0,pic[r],255);
xput(204+(r*32),1,PAGE0,pic[r]);
copy_pic_to_grid(active_pic);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void color_swap(void){
int x,y,i,p;

i=active_pic;
MSHIDE;
for(x=0;x<16;x++){
   for(y=0;y<16;y++){
      p=xpoint(204+x+(i*32),1+y,PAGE0);
      if(p==fg) xpset(204+x+(i*32),1+y,PAGE0,bg);
   }
}
copy_pic_to_grid(active_pic);
MSSHOW;
changed=1;
}
/*=========================================================================*/
void set_default_palette(void){
char pal[3];

xsetpal(240,0x00,0x00,0x00);
xsetpal(241,0xa0,0xa0,0xa0);
xsetpal(242,0xaa,0xaa,0xaa);
xsetpal(243,0xff,0xff,0xff);

xsetpal(244,0x00,0x00,0x00);
xsetpal(245,0xa0,0xa0,0xa0);
xsetpal(246,0xaa,0xaa,0xaa);
xsetpal(247,0xff,0xff,0xff);

xgetpal((char far*) pal,1,139);
xsetpal(251,pal[0],pal[1],pal[2]);
xgetpal((char far*) pal,1,146);
xsetpal(252,pal[0],pal[1],pal[2]);
xgetpal((char far*) pal,1,149);
xsetpal(253,pal[0],pal[1],pal[2]);

}
/*=========================================================================*/
void rotate_palette(void){


xsetpal(240,0x00,0x00,0x3b);  //set all blue
xsetpal(241,0x00,0x00,0x3b);
xsetpal(242,0x00,0x00,0x3b);
xsetpal(243,0x00,0x00,0x3b);

xsetpal(244,0x3b,0x00,0x00);  //set all red
xsetpal(245,0x3b,0x00,0x00);
xsetpal(246,0x3b,0x00,0x00);
xsetpal(247,0x3b,0x00,0x00);

while(!kbhit()){
  xsetpal(240,0x27,0x27,0x3f);
  xsetpal(243,0x00,0x00,0x3b);
  xsetpal(244,0x3f,0x27,0x27);
  xsetpal(247,0x3b,0x00,0x00);
  delay(200);
  xsetpal(241,0x27,0x27,0x3f);
  xsetpal(240,0x00,0x00,0x3b);
  xsetpal(245,0x3f,0x27,0x27);
  xsetpal(244,0x3b,0x00,0x00);
  delay(200);
  xsetpal(242,0x27,0x27,0x3f);
  xsetpal(241,0x00,0x00,0x3b);
  xsetpal(246,0x3f,0x27,0x27);
  xsetpal(245,0x3b,0x00,0x00);
  delay(200);
  xsetpal(243,0x27,0x27,0x3f);
  xsetpal(242,0x00,0x00,0x3b);
  xsetpal(247,0x3f,0x27,0x27);
  xsetpal(246,0x3b,0x00,0x00);
  delay(200);
}
set_default_palette();
}
/*=========================================================================*/
void show_help(void){
int y;

MSHIDE;
xcls(0,PAGE1);
xshowpage(PAGE1);
y=0;

xprint(0,y+=10,"              HELP SCREEN 1",14,PAGE1);
y+=8;
xprint(0,y+=10,"POINT MOUSE IN COLOR BARS AND PRESS:",7,PAGE1);
xprint(0,y+=10,"/14/LEFT  BUTTON /07/TO CHANGE FOREGROUND (FG)",7,PAGE1);
xprint(0,y+=10,"/14/RIGHT BUTTON /07/TO CHANGE BACKGROUND (BG)",7,PAGE1);
y+=8;
xprint(0,y+=10,"POINT MOUSE IN BIG GRID AND HOLD:",7,PAGE1);
xprint(0,y+=10,"/14/LEFT  BUTTON /07/(LB) TO DRAW IN FG COLOR",7,PAGE1);
xprint(0,y+=10,"/14/RIGHT BUTTON /07/(RB) TO DRAW IN BG COLOR",7,PAGE1);
y+=8;
xprint(0,y+=10,"/14/<TAB>       /07/PICK UP FG AT MOUSE POINT",7,PAGE1);
xprint(0,y+=10,"/14/<SHIFT-TAB> /07/PICK UP BG AT MOUSE POINT",7,PAGE1);
xprint(0,y+=10,"/14/<ALT-S>     /07/CHANGE ALL FG COLOR TO BG",7,PAGE1);
//              |        |         |         |         |
y+=8;
xprint(0,y+=10,"POINT MOUSE AT THE SMALL SPRITE (1 OF 4)",7,PAGE1);
xprint(0,y+=10,"YOU WANT TO WORK ON AND PRESS LB",7,PAGE1);
xprint(0,y+=10,"(OR PRESS /14/LEFT /07/OR /14/ RIGHT /07/ ARROW)",7,PAGE1);
y+=8;
xprint(0,y+=10,"CLICK ON THE SMALL SPRITE BELOW THE",7,PAGE1);
xprint(0,y+=10,"OTHER 4 TO ANIMATE. THE CHECK BOX BELOW",7,PAGE1);
xprint(0,y+=10,"EACH SPRITE WILL INCLUDE OR EXCLUDE EACH",7,PAGE1);
xprint(0,y+=10,"OF THE 4 SPRITES IN THE ANIMATION",7,PAGE1);
if(!help_pause()) return;

y=0;
xprint(0,y+=10,"              HELP SCREEN 2",14,PAGE1);
//              |        |         |         |         |       ^
y+=8;
xprint(0,y+=10,"/14/F1 /07/SAVE ALL 4 SPRITES IN A .RIM FILE",7,PAGE1);
xprint(0,y+=10,"/14/F2 /07/LOAD SPRITES FROM A .RIM FILE",7,PAGE1);
xprint(0,y+=10,"/14/F3 /07/UNDO LAST COMMAND (NO UNDO ON DRAW)",7,PAGE1);
xprint(0,y+=10,"/14/F4 /07/CLEAR CURRENT SPRITE TO BG COLOR",7,PAGE1);
xprint(0,y+=10,"/14/F5 /07/QUIT TO DOS (ASK TO SAVE FIRST)",7,PAGE1);
xprint(0,y+=10,"/14/F6 /07/ROTATE PALETTE AS IN GAME",7,PAGE1);
y+=8;
xprint(0,y+=10,"/12/<SHIFT> +",7,PAGE1);
xprint(0,y+=18,"/14/F1 /07/SHIFT SPRITE UP 1 ROW",7,PAGE1);
xprint(0,y+=10,"/14/F2 /07/SHIFT SPRITE DOWN 1 ROW",7,PAGE1);
xprint(0,y+=10,"/14/F3 /07/SHIFT SPRITE LEFT 1 COLUMN",7,PAGE1);
xprint(0,y+=10,"/14/F4 /07/SHIFT SPRITE RIGHT 1 COLUMN",7,PAGE1);
xprint(0,y+=10,"/14/F5 /07/LOAD AN ACTOR",7,PAGE1);
xprint(0,y+=10,"/14/F6 /07/SAVE AN ACTOR",7,PAGE1);
xprint(0,y+=10,"/14/F7 /07/EDIT ACTOR DATA",7,PAGE1);
xprint(0,y+=10,"/14/F8 /07/EDIT SHOT DATA",7,PAGE1);
xprint(0,y+=10,"/14/F9 /07/EDIT ACTOR SOUNDS",7,PAGE1);

if(!help_pause()) return;

y=0;
xprint(0,y+=10,"              HELP SCREEN 3",14,PAGE1);
//              |        |         |         |         |       ^
y+=8;
xprint(0,y+=10,"/12/<CTRL> +",7,PAGE1);
xprint(0,y+=18,"/14/F1 /07/FLIP SPRITE ON VERTICAL AXIS",7,PAGE1);
xprint(0,y+=10,"/14/F2 /07/FLIP SPRITE ON HORIZONTAL AXIS",7,PAGE1);
xprint(0,y+=10,"/14/F3 /07/MIRROR SPRITE ON VERTICAL AXIS",7,PAGE1);
xprint(0,y+=10,"/14/F4 /07/MIRROR SPRITE ON HORIZONTAL AXIS",7,PAGE1);
xprint(0,y+=10,"/14/F5 /07/ROTATE SPRITE CLOCKWISE",7,PAGE1);
y+=8;
xprint(0,y+=10,"/12/<ALT> +",7,PAGE1);
xprint(0,y+=18,"/14/F1 /07/GET DIRECTORY OF .RIM FILES",7,PAGE1);
xprint(0,y+=10,"/14/F2 /07/ERASE ALL SPRITES AND START NEW SET",7,PAGE1);
xprint(0,y+=10,"/14/F3 /07/EXPORT CURRENT SPRITE TO BG FILE",7,PAGE1);
xprint(0,y+=10,"/14/F4 /07/IMPORT A SPRITE FROM BG FILE",7,PAGE1);
xprint(0,y+=10,"/14/F5 /07/IMPORT 4 SPRITES FROM PCX FILE",7,PAGE1);
xprint(0,y+=10,"/14/I  /07/EXPORT 4 SPRITES TO ACTOR",7,PAGE1);
xprint(0,y+=10,"/14/E  /07/IMPORT 4 SPRITES FROM ACTOR",7,PAGE1);

xprint(0,231,"PRESS ANY KEY...",12,PAGE1);
getch();
xcls(0,PAGE1);
xshowpage(PAGE0);
MSSHOW;
}
/*=========================================================================*/
int help_pause(void){

xprint(0,231,"ESC TO ABORT, OTHER KEY FOR NEXT SCREEN",12,PAGE1);
if(getch()==27){
  xcls(0,PAGE1);
  xshowpage(PAGE0);
  MSSHOW;
  return 0;
}
xcls(0,PAGE1);
return 1;
}
/*=========================================================================*/
void pcx_import(void){
int i,ret;
FILE *fp;

status_line("PCX FILE:",14);
strcpy(tempstr,pcx_filename);
if(!xinput(80,231,tempstr,15,4,8,1,PAGE0)){
  display_help(0);
  return;
}
strcpy(pcx_filename,tempstr);
strcpy(tempstr,"\\PG\\pcx\\");
strcat(tempstr,pcx_filename);
strcat(tempstr,".pcx");

fp=fopen(tempstr,"rb");
if(!fp){
  fclose(fp);
  return;
}
fclose(fp);

ret=pcx_imp();
if(ret) changed=1;

xsetmode();
xmouse_init();
xmouse_off();
xmouse_set_bounds(0,0,624,231);
xmouse_set_pos(320,120);
xmouse_stat();
mx=MPX;
my=MPY;
xmouse_cnt=1;
MSSHOW;

if(xcreatmaskimage(&mouse_image,PAGE3,mcursor,8,8,mmask)==0){
  exit_code();
  exit(0);
}
xshowpage(PAGE0);
draw_grid();
draw_palette();
display_color_box();
//display_pics();
display_help(0);
display_enabled();
load_palette();
set_default_palette();

xprint(224,70, "COOR:",7,PAGE0);
xprint(216,80,"COLOR:",7,PAGE0);

xprint(200,100,"COPYRIGHT 1992,",12,PAGE0);
xprint(200,108,"CUSTOM SOFTWARE",12,PAGE0);
xprint(200,116,"ENGINEERING",12,PAGE0);

xprint(200,144,"HIT H FOR HELP",15,PAGE0);

MSHIDE;
for(i=0;i<4;i++){
   xfillrectangle(204+(i*32),1,220+(i*32),17,PAGE0,0);
   xput(204+(i*32),1,PAGE0,pic[i]);
}
//copy_pic_to_grid(active_pic);
display_pics();
MSSHOW;
}
/*=========================================================================*/
void beep(void){

sound(1000);
delay(500);
nosound();
}
/*=========================================================================*/
void load_actor(void){
int i;
long offset;
FILE *fp;

status_line("LOAD ACTOR #:",14);
itoa(actor_num,tempstr,10);

while(1){
  if(!xinput(14*8,231,tempstr,15,4,2,1,PAGE0)){
    display_help(0);
    return;
  }
  i=atoi(tempstr);
  if(i<0 ||i >99){
    beep();
    continue;
  }
  actor_num=i;
  break;
}
fp=fopen(ad_file,"rb");
if(!fp) exit(0);

offset=((long) i * (long) sizeof(ACTOR_DATA));
if(fseek(fp,offset,SEEK_SET)){
  fclose(fp);
  status_line("File Seek Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
if(fread(&actor,sizeof(ACTOR_DATA),1,fp) !=1){
     fclose(fp);
     status_line("File Read Error...Press Any Key.",12);
     getch();
     display_help(0);
     return;
}
fclose(fp);
}
/*=========================================================================*/
void save_actor(void){
int i;
long offset;
FILE *fp;

actor.shot_info.width=16;
actor.shot_info.height=16;
actor.actor_info.width=16;
actor.actor_info.height=16;
beep();
status_line("SAVE ACTOR #:",14);
itoa(actor_num,tempstr,10);

while(1){
  if(!xinput(14*8,231,tempstr,15,4,2,1,PAGE0)){
    display_help(0);
    return;
  }
  i=atoi(tempstr);
  if(i<0 ||i >99){
    beep();
    continue;
  }
  actor_num=i;
  break;
}
fp=fopen(ad_file,"rb+");
if(!fp) exit(0);

offset=((long) i * (long) sizeof(ACTOR_DATA));
if(fseek(fp,offset,SEEK_SET)){
  fclose(fp);
  status_line("File Seek Error...Press Any Key.",12);
  getch();
  display_help(0);
  return;
}
if(fwrite(&actor,sizeof(ACTOR_DATA),1,fp) !=1){
     fclose(fp);
     status_line("File Write Error...Press Any Key.",12);
     getch();
     display_help(0);
     return;
}
fclose(fp);
}
/*=========================================================================*/
void edit_actor(void){

MSHIDE;
xcls(0,PAGE1);
xshowpage(PAGE1);
xprint(13*8,0,"EDIT ACTOR DATA",14,PAGE1);
display_actor_pics();
store_input(&actor.actor_info);
if(input_data()) retrieve_input(&actor.actor_info);
display_help(0);
xshowpage(PAGE0);
MSSHOW;
}
/*=========================================================================*/
void edit_shot(void){

MSHIDE;
xcls(0,PAGE1);
xshowpage(PAGE1);
xprint(13*8,0,"EDIT SHOT DATA",14,PAGE1);
display_actor_pics();
store_input(&actor.shot_info);
if(input_data()) retrieve_input(&actor.shot_info);
display_help(0);
xshowpage(PAGE0);
MSSHOW;
}
/*=========================================================================*/
int input_data(void){
int i,y;

y=16;
xfillrectangle(0,16,320,223,PAGE1,0);

for(i=0;i<20;i++){
   xprint(0,y,ea_prompt[i],15,PAGE1);
   xinput(18*8,y,in_str[i],15,0,8,-1,PAGE1);
   y+=10;
}
y=16;
for(i=0;i<20;i++){
//   xprint(0,y,ea_prompt[i],15,PAGE1);
   if(!xinput(18*8,y,in_str[i],15,4,8,1,PAGE1)){
     display_help(0);
     xshowpage(PAGE0);
     return 0;
   }
   xinput(18*8,y,in_str[i],15,0,8,-1,PAGE1);
   y+=10;
}
return 1;
}
/*=========================================================================*/
void store_input(ACTOR_NFO *data){

strcpy(in_str[0],data->name);
itoa(data->type,in_str[1],10);
itoa(data->move,in_str[2],10);
itoa(data->directions,in_str[3],10);
itoa(data->frames,in_str[4],10);
itoa(data->frame_speed,in_str[5],10);
in_str[6][0]=data->frame_sequence[0]+48;
in_str[6][1]=data->frame_sequence[1]+48;
in_str[6][2]=data->frame_sequence[2]+48;
in_str[6][3]=data->frame_sequence[3]+48;
itoa(data->speed,in_str[7],10);
itoa(data->size_x,in_str[8],10);
itoa(data->size_y,in_str[9],10);
itoa(data->strength,in_str[10],10);
itoa(data->health,in_str[11],10);
itoa(data->num_moves,in_str[12],10);
itoa(data->shot_pattern,in_str[13],10);
itoa(data->shots_allowed,in_str[14],10);
itoa(data->solid,in_str[15],10);
itoa(data->flying,in_str[16],10);
itoa(data->magic_hurts,in_str[17],10);
itoa(data->func_num,in_str[18],10);
itoa(data->func_pass,in_str[19],10);
}
/*=========================================================================*/
void retrieve_input(ACTOR_NFO *data){

strcpy(data->name,in_str[0]);
data->type=atoi(in_str[1]);
data->move=atoi(in_str[2]);
data->directions=atoi(in_str[3]);
data->frames=atoi(in_str[4]);
data->frame_speed=atoi(in_str[5]);
data->frame_sequence[0]=in_str[6][0]-48;
data->frame_sequence[1]=in_str[6][1]-48;
data->frame_sequence[2]=in_str[6][2]-48;
data->frame_sequence[3]=in_str[6][3]-48;
data->speed=atoi(in_str[7]);
data->size_x=atoi(in_str[8]);
data->size_y=atoi(in_str[9]);
data->strength=atoi(in_str[10]);
data->health=atoi(in_str[11]);
data->num_moves=atoi(in_str[12]);
data->shot_pattern=atoi(in_str[13]);
data->shots_allowed=atoi(in_str[14]);
data->solid=atoi(in_str[15]);
data->flying=atoi(in_str[16]);
data->magic_hurts=atoi(in_str[17]);
data->func_num=atoi(in_str[18]);
data->func_pass=atoi(in_str[19]);
}
/*=========================================================================*/
void display_actor_pics(void){
int i,x,y,r;

for(i=0;i<16;i++){
   r=0;
   for(y=0;y<16;y++){
      for(x=0;x<16;x++){
         xpset((i*16)+x,y+223,PAGE1,actor.pic[i][r++]);
      }
   }
}
for(i=0;i<4;i++){
   r=0;
   for(y=0;y<16;y++){
      for(x=0;x<16;x++){
         xpset(256+(i*16)+x,y+223,PAGE1,actor.shot[i][r++]);
      }
   }
}

}
/*=========================================================================*/
void import_actor_pics(void){
int key,x,i;

MSHIDE;
xcls(0,PAGE1);
xshowpage(PAGE1);
xprint(11*8,0,"IMPORT ACTOR PICS",14,PAGE1);
display_actor_pics();

xfillrectangle(0,16,320,223,PAGE1,0);

xprint(10*8,120,"PRESS /14/1/15/-/14/5/15/ TO IMPORT",15,PAGE1);

xprint(0,211,"#   /14/1/15/   #   /14/2/15/   #   /14/3/15/   #   /14/4/15/   #   /14/5/15/  #",15,PAGE1);

x=0;
while(1){
     key=toupper(getch());
     if(!key) {getch(); continue;}
     if(key>48 && key < 54){
        x=(key-48);
        break;
     }
     if(key==27) break;
}
if(x>0){
  x--;
  x*=64;
  for(i=0;i<4;i++)
     xget(x+(i*16),223,x+(i*16)+16,238,PAGE1,pic[i],0);
  display_help(0);
  xshowpage(PAGE0);
  for(i=0;i<4;i++){
     xfillrectangle(204+(i*32),1,220+(i*32),17,PAGE0,0);
     xput(204+(i*32),1,PAGE0,pic[i]);
  }
display_pics();
}
else{
  display_help(0);
  xshowpage(PAGE0);
}
MSSHOW;
}
/*=========================================================================*/
void export_actor_pics(void){
int key,x,y,r,i,x1,f;

MSHIDE;

for(i=0;i<4;i++) xget(204+(i*32),1,219+(i*32),16,PAGE0,pic[i],0);

xcls(0,PAGE1);
xshowpage(PAGE1);
xprint(11*8,0,"EXPORT ACTOR PICS",14,PAGE1);
display_actor_pics();

xfillrectangle(0,16,320,223,PAGE1,0);

xprint(10*8,120,"PRESS /14/1/15/-/14/5/15/ TO EXPORT",15,PAGE1);

for(i=0;i<4;i++) xput(124+(i*16),52,PAGE1,pic[i]);

xprint(0,211,"#   /14/1/15/   #   /14/2/15/   #   /14/3/15/   #   /14/4/15/   #   /14/5/15/  #",15,PAGE1);

f=0;
while(1){
     key=toupper(getch());
     if(!key) {getch(); continue;}
     if(key>48 && key < 54){
        f=(key-48);
        break;
     }
     if(key==27) break;
}
if(f>0){
  f--;
  f*=4;
  x1=124;
  for(i=0;i<4;i++){
     r=0;
     for(y=0;y<16;y++){
        for(x=0;x<16;x++){
           if(x<16) actor.pic[f][r++]=xpoint(x+x1,52+y,PAGE1);
           else actor.shot[f-16][r++]=xpoint(x+x1,52+y,PAGE1);
        }
     }
     x1+=16;
     f++;
  }
}
display_actor_pics();
beep();
xfillrectangle(0,110,320,130,PAGE1,0);
xprint(10*8,120,"DONE...PRESS ANY KEY.  ",15,PAGE1);
getch();
display_help(0);
xshowpage(PAGE0);
MSSHOW;
}
/*=========================================================================*/
void write_screen(void){
int i;
FILE *fp;
char s[21];
char str[21];

status_line(".PIC Name: ",14);
strcpy(s,pic_file);
if(!xinput(11*8,231,s,15,4,8,1,PAGE0)){
  display_help(0);
  return;
}
strcpy(pic_file,s);
strcpy(str,"\\PG\\");
strcat(str,s);
strcat(str,".pic");
fp=fopen(str,"wb");
if(!fp) exit(0);

for(i=0;i<4;i++){
   xget(204+(i*32),1,219+(i*32),16,PAGE0,
       pic[i],0);
   fwrite(pic[i],262,1,fp);
}
fclose(fp);
}
/*=========================================================================*/
void read_screen(void){
int x,y;
char color;
FILE *fp;


xcls(0,PAGE0);
fp=fopen("\\bc\\hammer.bin","rb");
if(!fp) exit(0);


for(y=0;y<240;y++){
   for(x=0;x<320;x++){
      fread(&color,1,1,fp);
      xpset(x,y,PAGE0,color);
   }
}
fclose(fp);
}
/*=========================================================================*/
void overlap(void){
int x,y,c;

for(y=0;y<16;y++){
   for(x=0;x<16;x++){
      c=xpoint(204+x+(active_pic*32),y+1,PAGE0);
      if(c!=0 && c!=15) xpset(x+204,y+1,PAGE0,c);
   }
}
xget(204,1,219,16,PAGE0,pic[0],0);
}












