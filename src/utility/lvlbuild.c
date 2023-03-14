#define TESTING 1
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <dir.h>
#include <ctype.h>
#include <conio.h>
#include <alloc.h>
#include <process.h>

#include "maskim.h"
#include "modex.h"
#include "xmouse.h"
#include "res_man.h"
#include "level.h"
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

#define MSHIDE xmouse_hide(mx,my)
#define MSSHOW xmouse_show(mx,my)

//==========================================================================
//external prototypes
xsetpal(unsigned char color, unsigned char R,unsigned char G,unsigned char B);
xgetpal(char far * pal, int num_colrs, int start_index);
//internal prototypes
void xprint(int x, int y, const char* string, int color, unsigned int page);
void exit_error(const char* error_msg);
void exit_code(void);
void xmouse_show(int x, int y);
void xmouse_hide(int x, int y);
void display_help(int level);
void status_line(const char* message, int color);
int  do_key_function(void);
void view_screen(int num);
void load_file(void);
int  xinput(int x,int y,char *buff,int fg,int bg,int max,int min,unsigned int page);
void save_screen(void);
void save_file(void);
int  are_you_sure(const char* mess);
void set_undo(void);
void undo(void);
void flush_buff(void);
void ask_to_save(void);
void no_button(void);
void load_palette(void);
void set_screen_pal(void);
int  point_within(int x, int y, int x1, int y1, int x2, int y2);
void show_screen(void);
void show_bg(void);
int  load_bg_pics(void);
void change_bg_color(void);
void fill_screen(int);
void add_actor(void);
void display_actors(void);
void delete_actor(void);
void flip_actor(void);
void show_objects(void);
int load_objects(void);
void show_current_object(void);
void inc_object(void);
void dec_object(void);
int find_empty_object(void);
void place_object(void);
void delete_object(void);
void beep(void);
void edit_level_data(void);
void edit_pal_data(void);
int  load_sd_data(void);
int  save_sd_data(void);
void pickup_tile(void);
int  load_actors(void);
int  select_actor(void);
void pickup_tile(void);
int convert(void);
void actor_value(void);
void edit_actor_value(int num);
int  pick_tile(void);
void pick_warp(void);
int  pick_actor(void);
void actor_script(void);
void reset_mode(void);
//==========================================================================
//global variables

union REGS in, out;
struct SREGS seg;
xmouse mouse;
int xmouse_cnt;
int mx, my, fg, bg;
int  area_num;
int  changed;
char tempstr[255];

char slow_mode, main_loop;

// mouse curosr 8x8

static char mcursor[]={
  0,0,0,0,0,0,0,0,
  0,7,7,7,7,7,0,0,
  0,7,7,7,7,0,0,0,
  0,7,7,7,7,0,0,0,
  0,7,7,7,7,7,0,0,
  0,7,0,0,7,7,7,0,
  0,0,0,0,0,7,7,0,
  0,0,0,0,0,0,0,0,
};

static char mmask[]={
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0,
  1,1,1,1,1,1,0,0,
  1,1,1,1,1,1,0,0,
  1,1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,0,0,1,1,1,1,
  1,0,0,0,0,1,1,0,
};
static MaskedImage mouse_image;

char far text[94][72];

char far* bg_pics;
char objects[32][262];

#include "actornfo.h"
#include "actordat.h"

LEVEL scrn;
ACTOR_DATA actor_buff;
char afb[100];

char actor[100][256];
char actor_flag[100];
char actor_nf[100];
int  frames_left;
char res_file[80];

int current_bg;
int hilite_bg;
int alt_flag;
int current_object;
char far *sd_data;
char current_screen;
char far *fb;

//==========================================================================
void main(int argc, char *argv[]) {
  int i, ret, x, y;
  int help_level, hl;
  char s[21];
  int lx, ly;

  strcpy(res_file, "\\GOT\\GOTRES.DAT");
  area_num = 1;

  if (argc > 1) { //parse the command line
    for (i = 1; i < argc; i++) {
      if (argv[i][0] == '/' || argv[i][0] == '\\') {
        strcpy(&argv[i][0], &argv[i][1]);
        strupr(argv[i]);
        if (!strncmp(argv[i], "AREA:", 5)) {
          area_num = atoi(&argv[i][5]);
          if (area_num == 0) {
            area_num++;
          }
        }
        if (!strncmp(argv[i], "FILE:", 5)) {
          strcpy(res_file,&argv[i][5]);
        }
      }
    }
  }

  fb = farmalloc(30000u);
  if (!fb) {
    exit_error("Out of Memory");
  }

  mkdir("c:\\sdf");
  res_init(fb);
  if (res_open(res_file) < 0) {
    sprintf(tempstr, "Cannot Open: %s\r\n\r\n", res_file);
    exit_error(tempstr);
  }

  if (res_read("TEXT", (char far*)text) < 0) {
    exit_error("Can't Read TEXT");
  }

  load_sd_data();

  bg_pics = 0;
  load_bg_pics();

  load_objects();

  current_object = 0;
  xsetmode();
  xmouse_init();
  xmouse_off();
  xmouse_set_bounds(0, 0, 320, 240);
  xmouse_set_pos(160, 120);
  xmouse_stat(&mouse);
  mx = mouse.x;
  my = mouse.y;
  xmouse_cnt = 1;
  MSSHOW;
  fg = 31;
  bg = 0;
  help_level = 0;
  changed = 0;
  current_bg = 0;
  hilite_bg = 10;
  main_loop = 1;

  if (xcreatmaskimage(&mouse_image, PAGE3, mcursor, 8, 8, mmask) == 0) {
    exit_error("xcreatmaskimage fail\n");
  }

  // setup background
  xshowpage(PAGE0);
  display_help(0);
  load_palette();

  if (!load_actors()) {
    exit_error("Cannot Load Actors\r\n");
  }

  lx = 0;
  ly = 0;

  show_screen();
  show_objects();
  show_bg();
  show_current_object();

  current_screen = 0;
  view_screen(current_screen);

  while (1) {
    in.h.ah = 2;
    int86(0x16, &in, &out);
    if ((out.h.al & 1) || (out.h.al & 2)) {
      hl = 1; //shift
    }
    else if (out.h.al & 4) {
      hl = 2; //ctrl
    }
    else if (out.h.al & 8) {
      hl = 3; //alt
    }
    else {
      hl = 0;
    }
    if (hl == 3) {
      alt_flag = 1;
    }
    else {
      alt_flag = 0;
    }
    if (hl != help_level) {
      help_level = hl;
      display_help(help_level);
    }
    if (kbhit()) {
      if (do_key_function()) {
        break;
      }
      flush_buff();
    }
    xmouse_stat(&mouse);
    if (mouse.x != mx || mouse.y != my) {
      MSHIDE;
      mx = mouse.x;
      my = mouse.y;
      MSSHOW;
    }
    x = mx/16;
    y = my/16;
    if (y != ly || x != lx) {
      itoa(scrn.icon[y][x], s, 10);
      xfillrectangle(10 * 8, 218, 32 * 8, 226, PAGE0, 0);
      xprint(10 * 8, 218, "CURRENT:", 15, PAGE0);
      xprint(18 * 8, 218, s, 14, PAGE0);
      lx = x;
      ly = y;
      if (((y * 20) + x) < 240) {
        itoa((y * 20) + x, s, 10);
        xprint(24 * 8, 218, "POS:", 15, PAGE0);
        xprint(28 * 8, 218, s, 14, PAGE0);
      }
    }
    if (XMOUSE_LEFT(mouse)) {
      if (alt_flag) {
        place_object();
      }
      else if (point_within(mx, my, 0, 200, 320, 216)) {
        ret = (mx / 16) + current_bg;
        if (ret > 229) {
          ret -= 230;
        }
        hilite_bg = mx / 16;
        show_bg();
        no_button();
      }
      else if (point_within(mx, my, 0, 0, 320, 192)) {
        x = mx / 16;
        y = my / 16;
        if (y < 12 && x < 20) {
          ret = current_bg + hilite_bg;
          if (ret > 229) {
            ret -= 230;
          }
          if (scrn.icon[y][x] != ret) {
            MSHIDE;
            xfput(x * 16, y * 16, PAGE0, (char far*)(bg_pics + (scrn.bg_color * 262)));
            xfput(x * 16, y * 16, PAGE0, (char far*)(bg_pics + (ret * 262)));
            MSSHOW;
            scrn.icon[y][x] = ret;
            changed = 1;
          }
        }
      }
    }
    if (XMOUSE_RIGHT(mouse)) {
      if (alt_flag) {
        delete_object();
      }
      else if (point_within(mx, my, 0, 0, 320, 192)) {
        x = mx / 16;
        y = my / 16;
        if (y < 12 && x < 20) {
          MSHIDE;
          xfillrectangle(x * 16, y * 16, (x * 16) + 16, (y * 16) + 16, PAGE0, 0);
          xfput(x * 16, y * 16, PAGE0, (char far*)(bg_pics + (scrn.bg_color * 262)));
          MSSHOW;
          scrn.icon[y][x] = scrn.bg_color;
          changed=1;
        }
      }
    }
  }
  exit_code();
  exit(0);
}
//===========================================================================
void exit_error(const char* error_msg) {
  exit_code();
  printf("ERROR: %s\r\n\r\n", error_msg);
  exit(0);
}
//===========================================================================
void exit_code(void) {
  union REGS regset;

  res_close();
  if (sd_data) {
    farfree(sd_data);
  }
  if (bg_pics) {
    farfree(bg_pics);
  }
  regset.x.ax = 0x0003;
  int86(0x10, &regset, &regset);
}
//===========================================================================
int do_key_function(void) {
  int key, hl;

  key = getch();
  if (key == 9) {
    pickup_tile();
    return 0;
  }
  if (key != 0) {
    return 0;
  }
  key = getch();

  hl = 0;
  in.h.ah = 2;
  int86(0x16, &in, &out);
  if (out.h.al & 1) {      //shift
    hl = 1;
  }
  else if (out.h.al & 2) { //shift
    hl = 1;
  }

  switch (key) {
  case 77:       //right
    if (hl) {
      if (current_screen < 119) {
        save_screen();
        current_screen++;
        view_screen(current_screen);
      }
    }
    else {
      if (current_bg < 229) {
        current_bg++;
      }
      else {
        current_bg = 0;
      }
      show_bg();
    }
    return 0;
  case 75:      //left
    if (hl) {
      if (current_screen > 0) {
        save_screen();
        current_screen--;
        view_screen(current_screen);
      }
    }
    else {
      if (current_bg > 0) {
        current_bg--;
      }
      else {
        current_bg = 229;
      }
      show_bg();
    }
    return 0;
  case 72:       //up
    if (hl) {
      if (current_screen > 9) {
        save_screen();
        current_screen -= 10;
        view_screen(current_screen);
      }
    }
    return 0;
  case 80:      //down
    if (hl) {
      if (current_screen < 110) {
        save_screen();
        current_screen += 10;
        view_screen(current_screen);
      }
    }
    return 0;
  case 71:      //home
    current_bg = 0;
    show_bg();
    return 0;
  case 116:       //ctrl-right
    current_bg += 10;
    if (current_bg > 229) {
      current_bg -= 230;
    }
    show_bg();
    return 0;
  case 115:      //ctrl-left
    current_bg -= 10;
    if (current_bg < 0) {
      current_bg += 230;
    }
    show_bg();
    return 0;
  case 59:           //F1
    save_file();
    break;
  case 60:           //F2
    load_file();
    break;
  case 61:           //F3
    change_bg_color();
    break;
  case 62:           //F4
    key = current_bg+hilite_bg;
    if (key > 229) {
      key -= 230;
    }
    scrn.bg_color = key;
    changed = 1;
    fill_screen(key);
    break;
  case 63:           //F5
    ask_to_save();
    if (are_you_sure("Quit")) {
      return 1;
    }
    break;
  case 64:           //F6
    pickup_tile();
    break;
  case 84:          //shft-F1
    scrn.type++;
    if (scrn.type > 4) {
      scrn.type = 0;
    }
    changed = 1;
  case 85:          //shft-F2
    MSHIDE;
    show_screen();
    show_objects();
    MSSHOW;
    break;
  case 86:          //shft-F3
    edit_level_data();
    break;
  case 87:          //shft-F4
    pick_warp();
    break;
  case 88:          //shft-F5
    edit_pal_data();
    break;
  case 94:          //ctrl-F1
    add_actor();
    break;
  case 95:          //ctrl-F2
    delete_actor();
    break;
  case 96:          //ctrl-F3
    flip_actor();
    break;
  case 97:          //ctrl-F4
    actor_value();
    break;
  case 98:          //ctrl-F5
    actor_script();
    break;
  case 104:          //alt-F1
    inc_object();
    break;
  case 105:          //alt-F2
    dec_object();
    break;
  }
  return 0;
}
//===========================================================================
void xprint(int x, int y, const char* string, int color, unsigned int page) {
  char ch;
  char str[3];

  str[2] = 0;
  x &= 0xfffc;
  while (*string) {
    ch = *string++;
    if (ch == '/' && *(string+2) == '/') {
      str[0] = *string++;
      str[1] = *string++;
      string++;
      color = atoi(str);
      continue;
    }
    if (ch > 32 && ch < 126) {
      xtext(x, y, page, text[ch - 32], color);
    }
    x += 8;
  }
}
/*=========================================================================*/
int point_within(int x, int y, int x1, int y1, int x2, int y2) {
  if ((x < x1) || (x > x2) || (y < y1) || (y > y2)) {
    return 0;
  }
  return 1;
}
/*=========================================================================*/
void xmouse_show(int x, int y){
  (void)x;
  (void)y;
  if (xmouse_cnt == 1) {
    // TODO https://github.com/joncloud/got/issues/1
    // xcopyd2d(x, y, x + 8, y + 8, x, y, PAGE0, PAGE2, 320, 320);
    // TODO this makes the program unpredictable
    // xcopyd2dmasked(0, 0, 8, 8, x, y, &mouse_image, 0, 320);
    xmouse_cnt = 0;
  }
  else {
    xmouse_cnt--;
  }
}
/*=========================================================================*/
void xmouse_hide(int x, int y) {
  (void)x;
  (void)y;
  if (xmouse_cnt == 0) {
    // TODO https://github.com/joncloud/got/issues/1
    // xcopyd2d(x,y,x+8,y+8,x,y,PAGE2,PAGE0,320,320);
  }
  xmouse_cnt++;
}
/*=========================================================================*/
void xbox(int x1, int y1, int x2, int y2, int color, unsigned page) {
  xline(x1, y1, x2, y1, color, page);
  xline(x1, y2, x2, y2, color, page);
  xline(x1, y1, x1, y2, color, page);
  xline(x2, y1, x2, y2, color, page);
}
//=========================================================================
int xinput(int x, int y, char* buff, int fg, int bg,
           int max, int min, unsigned int page) {
  int key;
  int pos;
  char ch;
  char s[2];

  MSHIDE;
  xfillrectangle(x, y, x + (max * 8), y + 8, page, bg);
  xprint(x, y, buff, fg, page);
  pos = strlen(buff);

  while (1) {
    if (kbhit()) {
      key = getch();
      if (key == 0) {
        getch();
        continue;
      }
      else if (key == 13) {
        if (pos >= min) {
          buff[pos] = 0;
          MSSHOW;
          return 1;
        }
      }
      else if (key == 27) {
        buff[pos] = 0;
        MSSHOW;
        return 0;
      }
      else if (key == 8 && pos > 0) {
        pos--;
        xfillrectangle(x + (pos * 8), y, x + (pos * 8) + 8, y + 8, page, bg);
        buff[pos] = 0;
      }
      else if (isprint(key) && (pos < max)) {
        key = toupper(key);
        ch = key;
        s[0] = ch;
        s[1] = 0;
        xprint(x + (pos * 8), y, s, fg, page);
        buff[pos++] = ch;
        buff[pos] = 0;
      }
    }
  }
}
/*=========================================================================*/
void status_line(const char* message, int color) {
  MSHIDE;
  xfillrectangle(0, 231, 320, 240, PAGE0, 0);
  xprint(0, 231, message, color, PAGE0);
  MSSHOW;
}
/*=========================================================================*/
void display_help(int level){
  MSHIDE;
  xfillrectangle(0, 231, 320, 240, PAGE0, 0);
  #define HELP_TEXT(x) xprint(\
    0, 231,\
    x,\
    14, PAGE0\
    )
  switch (level) {
  case 0:
    HELP_TEXT("F1 /15/SV/14/ F2 /15/LD/14/ F3 /15/BGTILE/14/ F4 /15/FILL/14/ F5 /15/QUIT");
    break;
  case 1:
    HELP_TEXT("F1 /15/MUSIC/14/ F2 /15/REDRAW/14/ F3 /15/EDT WRP/14/ F4 /15/PCK WRP");
    break;
  case 2:
    HELP_TEXT("F1 /15/ADD ACTOR/14/ F2 /15/DEL ACTOR/14/ F3 /15/FLIP/14/ F4 /15/VALUE");
    break;
  case 3:
    HELP_TEXT("F1 /15/INC/14/ F2 /15/DEC/14/ LB /15/PLACE/14/ RB /15/DELETE/14/");
    break;
  }
  #undef HELP_TEXT
  MSSHOW;
}
/*=========================================================================*/
int are_you_sure(const char* mess) {
  int key;
  char s[80];

  strcpy(s, mess);
  strcat(s, ": Are You Sure? ");
  strcat(s, "(Y/N)");
  status_line(s, 12);
  flush_buff();
  while (1) {
    key = toupper(getch());
    if (key == 'Y') {
      key = 1;
      break;
    }
    else if ((key == 'N') || (key == 27)) {
      key = 0;
      break;
    }
  }
  display_help(0);
  return key;
}
/*=========================================================================*/
void flush_buff(void) {
  while (kbhit()) {
    getch();
  }
}
/*=========================================================================*/
void ask_to_save(void) {
  int key;

  if (!changed) {
    return;
  }

  status_line("Do You Wish To Save First? (Y/N)", 14);
  flush_buff();
  while (1) {
    key = toupper(getch());
    if (key == 'Y') {
      break;
    }
    else if ((key == 'N')) {
      return;
    }
  }
  save_sd_data();

  changed = 0;
}
/*=========================================================================*/
void no_button(void) {
  while (mouse.button) {
    xmouse_stat(&mouse);
  }
}
/*=========================================================================*/
#define DAC_READ_INDEX  03c7h
#define DAC_WRITE_INDEX 03c8h
#define DAC_DATA        03c9h
void load_palette(void) {
  int i;
  char buff[768];
  char r, g, b, n;

  if (res_read("PALETTE", (char far*)buff) < 0) {
    sprintf(buff, "Cannot Read PALETTE\r\n", tempstr);
    exit_error(buff);
  }

  in.h.al = 0x10;
  in.h.ah = 0x10;

  for (i = 0; i < 256; i++) {
    n = i;
    r = buff[i * 3] / 4;
    g = buff[(i * 3) + 1] / 4;
    b = buff[(i * 3) + 2] / 4;
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
  set_screen_pal();
}
/*=========================================================================*/
void set_screen_pal(void) {
  char pal[3];

  xgetpal((char far*)pal, 1, scrn.pal_colors[0]);
  xsetpal(251, pal[0], pal[1], pal[2]);
  xgetpal((char far*)pal, 1, scrn.pal_colors[1]);
  xsetpal(252, pal[0], pal[1], pal[2]);
  xgetpal((char far*)pal, 1, scrn.pal_colors[2]);
  xsetpal(253, pal[0], pal[1], pal[2]);
}
/*=========================================================================*/
void xcls(int color, unsigned int page) {
  MSHIDE;
  xfillrectangle(0, 0, 320, 240, page, color);
  MSSHOW;
}
/*=========================================================================*/
void save_screen(void) {
  movedata(
    FP_SEG(&scrn),
    FP_OFF(&scrn),
    FP_SEG(sd_data+(current_screen*512)),
    FP_OFF(sd_data+(current_screen*512)),
    512
  );
}
/*=========================================================================*/
void save_file(void) {
  char str[21];
  FILE* fp;

  status_line("SAVE Filename: ", 14);
  flush_buff();

  strcpy(str, "");
  if (!xinput(15 * 8, 231, str, 15, 4, 8, 1, PAGE0)) {
    display_help(0);
    return;
  }
  strcat(str, ".sdf");
  strcpy(tempstr, "sdf\\");
  strcat(tempstr, str);
  fp = fopen(tempstr, "wb");
  if (!fp) {
    status_line("File Open Error...Press Any Key.", 12);
    getch();
    display_help(0);
    return;
  }
  if (fwrite(&scrn, 512, 1, fp) != 1) {
    fclose(fp);
    status_line("File Write Error...Press Any Key.", 12);
    getch();
    display_help(0);
    return;
  }
  fclose(fp);
  display_help(0);
}
//===========================================================================
int load_bg_pics(void) {
  char s[80];

  itoa(area_num, s, 10);
  strcpy(tempstr, "BPICS");
  strcat(tempstr, s);

  bg_pics = res_falloc_read(tempstr);
  if (!bg_pics) {
    sprintf(s, "Cannot Read %s\r\n", tempstr);
    exit_error(s);
  }
  return 1;
}
/*=========================================================================*/
void view_screen(int num) {
  movedata(
    FP_SEG(sd_data + (num * 512)),
    FP_OFF(sd_data + (num * 512)),
    FP_SEG(&scrn),
    FP_OFF(&scrn),
    512
  );

  show_screen();
  show_objects();
  display_help(0);
}

/*=========================================================================*/
void load_file(void){
  char str[21];
  FILE* fp;

  status_line("LOAD Filename: ", 14);
  flush_buff();
  strcpy(str, "");
  if (!xinput(15 * 8, 231, str, 15, 4, 8, 1, PAGE0)) {
    display_help(0);
    return;
  }
  strcat(str, ".sdf");
  strcpy(tempstr, "sdf\\");
  strcat(tempstr, str);
  fp=fopen(tempstr, "rb");
  if (!fp) {
    status_line("File Open Error...Press Any Key.", 12);
    getch();
    display_help(0);
    return;
  }
  if (fread(&scrn, 512, 1, fp) != 1) {
    fclose(fp);
    status_line("File Read Error...Press Any Key.", 12);
    getch();
    display_help(0);
    return;
  }
  fclose(fp);
  changed = 1;
  movedata(
    FP_SEG(&scrn),
    FP_OFF(&scrn),
    FP_SEG(sd_data + (current_screen * 512)),
    FP_OFF(sd_data + (current_screen * 512)),
    512
  );

  show_screen();
  show_objects();
  display_help(0);
}
//===========================================================================
void show_screen(void) {
  int x, y;
  char s[21];

  MSHIDE;
  xfillrectangle(0, 0, 320, 192, PAGE0, 0);
  if (!scrn.pal_colors[0]) {
    scrn.pal_colors[0] = 51;
    scrn.pal_colors[1] = 33;
    scrn.pal_colors[2] = 36;
  }
  set_screen_pal();
  for (y = 0; y < 12; y++) {
    for (x = 0; x < 20; x++) {
      xfput(x * 16, y * 16, PAGE0, (char far*)(bg_pics + (scrn.bg_color * 262)));
      xfput(x * 16, y * 16, PAGE0, (char far*)(bg_pics + (scrn.icon[y][x] * 262)));
    }
  }
  xfillrectangle(32 * 8, 218, 38 * 8, 226, PAGE0, 0);
  sprintf(s, "M%d", scrn.type);
  xprint(32 * 8, 218, s, 14, PAGE0);

  xfillrectangle(35 * 8, 218, 38 * 8, 226, PAGE0, 0);
  itoa(current_screen, s, 10);
  xprint(35 * 8, 218, s, 15, PAGE0);
  MSSHOW;
  display_actors();
}
//===========================================================================
void show_bg(void) {
  int x, p;
  char str[21];

  MSHIDE;
  xfillrectangle(0, 192, 320, 230, PAGE0, 0);
  for (x = 0; x < 20; x++){
    p = x + current_bg;
    if (p > 229) {
      p -= 230;
    }
    xfput(x * 16, 200, PAGE0, (char far*)(bg_pics + (p * 262)));
  }
  xbox(hilite_bg * 16, 200, (hilite_bg * 16) + 15, 216, 15, PAGE0);
  p = current_bg + hilite_bg;
  if (p > 229) {
    p -= 230;
  }
  itoa(p, str, 10);
  xprint(0, 218, "TILE:", 15, PAGE0);
  xprint(5 * 8, 218, str, 14, PAGE0);
  show_current_object();
  MSSHOW;
}
//===========================================================================
void change_bg_color(void) {
  int i;
  char str[21];

  status_line("Enter New BG Tile: ", 14);
  flush_buff();
  itoa(scrn.bg_color, str, 10);
  if (!xinput(20 * 8, 231, str, 15, 4, 3, 1, PAGE0)) {
    display_help(0);
    return;
  }
  i = atoi(str);
  if (i < 0 || i > 229) {
    status_line("Out of Range...Press Any Key.", 12);
    getch();
    display_help(0);
    return;
  }
  scrn.bg_color = i;
  changed = 1;
  show_screen();
  show_objects();
  display_help(0);
}
//===========================================================================
void fill_screen(int fill) {
  int x, y;

  if (!are_you_sure("FILL")) {
    display_help(0);
    return;
  }
  MSHIDE;
  for (x = 0; x < 20; x++) {
    for (y = 0; y < 12; y++) {
      xfillrectangle(x * 16, y * 16, (x * 16) + 16, (y * 16) + 16, PAGE0, 0);
      xfput(x * 16, y * 16, PAGE0, (char far *)(bg_pics + (fill * 262)));
      scrn.icon[y][x] = fill;
    }
  }
  changed = 1;
  show_screen();
  show_objects();
  display_actors();
  MSSHOW;
}
//===========================================================================
void add_actor(void) {
  int i, type, num;

  for (i = 0; i < LEVEL_MAX_ACTOR; i++) {
    if (!scrn.actor_type[i]) {
      num = i;
      break;
    }
  }
  if (i == LEVEL_MAX_ACTOR) {
    beep();
    return;
  }

  i = select_actor();

  type = i;
  if (i < 0) {
    return;
  }

  status_line("POINT TO LOCATION AND CLICK LEFT BUTTON", 14);
  while (1) {
    for (i = 0; i < LEVEL_MAX_ACTOR; i++) {
      if (!scrn.actor_type[i]) {
        num = i;
        break;
      }
    }
    if (i == LEVEL_MAX_ACTOR) {
      beep();
      return;
    }
    xmouse_stat(&mouse);
    if (mx != mouse.x || my != mouse.y) {
      MSHIDE;
      mx = mouse.x;
      my = mouse.y;
      MSSHOW;
    }
    if (XMOUSE_RIGHT(mouse)) {
      break;
    }
    if (XMOUSE_LEFT(mouse)) {
      scrn.actor_type[num] = type;
      scrn.actor_loc[num] = (mouse.x / 16) + ((mouse.y / 16) * 20);
      display_actors();
      no_button();
    }
  }
  done:
  show_screen();
  show_objects();
  display_help(0);
  no_button();
  changed=1;
}
//===========================================================================
void display_actors(void) {
  int i, x, y, d;
  int x1, y1, x2, y2;

  memset(afb, 0, 100);
  frames_left = 62;
  MSHIDE;
  for (i = 0; i < LEVEL_MAX_ACTOR; i++) {
    scrn.actor_type[i]&=0x3f;
    if (scrn.actor_type[i] == 0) {
      continue;
    }
    if (afb[scrn.actor_type[i]] == 0) {
      frames_left -= actor_nf[scrn.actor_type[i]];
    }
    afb[scrn.actor_type[i]] = 1;
    y = (scrn.actor_loc[i] / 20) * 16;
    x = (scrn.actor_loc[i] % 20) * 16;
    // TODO https://github.com/joncloud/got/issues/2
    // xput(x, y, PAGE0, actor[scrn.actor_type[i]]);
    d = scrn.actor_dir[i];
    switch (d) {
    case 0:
      x = x + 8;
      y = y;
      x1 = x - 8;
      y1 = y + 15;
      x2 = x + 7;
      y2 = y + 15;
      break;
    case 1:
      x = x + 8;
      y = y + 15;
      x1 = x - 8;
      y1 = y - 15;
      x2 = x + 7;
      y2 = y - 15;
      break;
    case 2:
      x = x;
      y = y + 8;
      x1 = x + 15;
      y1 = y - 8;
      x2 = x + 15;
      y2 = y + 7;
      break;
    case 3:
      x = x + 15;
      y = y + 8;
      x1 = x - 15;
      y1 = y - 8;
      x2 = x - 15;
      y2 = y + 7;
      break;
    }
    xline(x, y, x1, y1, 15, PAGE0);
    xline(x, y, x2, y2, 15, PAGE0);
  }
  MSSHOW;
}
//===========================================================================
void delete_actor(void) {
  int i;

  while (1) {
    status_line("CLICK ON ACTOR TO DELETE", 14);
    i = pick_actor();
    if (i >= 0) {
      scrn.actor_type[i] = 0;
      scrn.actor_loc[i] = 0;
      scrn.actor_value[i] = 0;
      scrn.actor_dir[i] = 0;
      changed = 1;
      show_screen();
      show_objects();
      display_help(0);
      no_button();
    }
    else {
      break;
    }
  }
}
//===========================================================================
void flip_actor(void) {
  int i, x, y, d;

  status_line("CLICK ON ACTOR TO FLIP", 14);
  while (1) {
    xmouse_stat(&mouse);
    if (mx != mouse.x || my != mouse.y) {
      MSHIDE;
      mx = mouse.x;
      my = mouse.y;
      MSSHOW;
    }
    if (XMOUSE_RIGHT(mouse)) {
      break;
    }
    if (XMOUSE_LEFT(mouse)) {
      x = (mouse.x & 0xfff0);
      y = (mouse.y & 0xfff0);
      for (i = 0; i < LEVEL_MAX_ACTOR; i++) {
        if ((x / 16) + ((y / 16) * 20) == scrn.actor_loc[i]) {
//          if(x==scrn.actor_x[i] && y==scrn.actor_y[i]){
          d = scrn.actor_dir[i];
          d++;
          if (d > 3) {
            d = 0;
          }
          scrn.actor_dir[i] = d;
          changed = 1;
          break;
        }
      }
      break;
    }
  }
  show_screen();
  show_objects();
  display_help(0);
  no_button();
}
//===========================================================================
void show_objects(void) {
  int i;

  MSHIDE;
  for (i = 0; i < 30; i++) {
    if (!scrn.static_obj[i]) {
      continue;
    }
    xput(
      scrn.static_x[i] * 16,
      scrn.static_y[i] * 16,
      PAGE0,
      objects[scrn.static_obj[i] - 1]
    );
  }
  MSSHOW;
}
//============================================================================
int load_objects(void) {
  char s[80];

  if (res_read("OBJECTS", (char far*)objects) < 0) {
    sprintf(s, "Cannot Read OBJECTS\r\n", tempstr);
    exit_error(s);
  }

  return 1;
}
//===========================================================================
void show_current_object(void) {
  MSHIDE;
  xfillrectangle(304, 216, 320, 232, PAGE0, 0);
  xfput(304, 216, PAGE0, (char far*)objects[current_object]);
  MSSHOW;
}
//===========================================================================
void inc_object(void) {
  current_object++;
  if (current_object > 31) {
    current_object = 0;
  }
  show_current_object();
}
//===========================================================================
void dec_object(void) {
  current_object--;
  if (current_object < 0) {
    current_object = 31;
  }
  show_current_object();
}
//===========================================================================
int find_empty_object(void) {
  int i;
  for (i = 0; i < 32; i++) {
    if (scrn.static_obj[i] == 0) {
      return i;
    }
  }
  return -1;
}
//===========================================================================
void place_object(void) {
  int o, x, y, i;

  o = find_empty_object();
  if (o == -1) {
    beep();
    return;
  }
  x = mouse.x /16;
  y = mouse.y /16;

  for (i = 0; i < 30; i += 1) {
    if (scrn.static_obj[i] == 0) {
      continue;
    }

    if (scrn.static_x[i] == x && scrn.static_y[i] == y) {
      beep();
      no_button();
      return;
    }
  }

  scrn.static_obj[o] = current_object + 1;
  scrn.static_x[o] = x;
  scrn.static_y[o] = y;

  show_objects();
  changed = 1;
  no_button();
}
//===========================================================================
void delete_object(void) {
  int x, y, i;

  x = mouse.x / 16;
  y = mouse.y / 16;

  for (i = 0; i < 30; i += 1) {
    if (scrn.static_obj[i] == 0) {
      continue;
    }

    if (scrn.static_x[i] == x && scrn.static_y[i] == y) {
      scrn.static_obj[i] = 0;
      scrn.static_x[i] = 0;
      scrn.static_y[i] = 0;
    }
  }

  changed = 1;
  show_screen();
  show_objects();
  no_button();
}
//===========================================================================
void beep(void) {
  sound(1000);
  delay(200);
  nosound();
}
//===========================================================================
void edit_level_data(void){
/*
int i,y;
char s[21];
char nl[10];
char ni[10];

MSHIDE;

xcls(0,PAGE1);
xshowpage(PAGE1);
xprint(13*8,0,"WARP TILE EDIT",14,PAGE1);
y=16;

for(i=0;i<10;i++){
   nl[i]=scrn.new_level[i];
   ni[i]=scrn.new_level_loc[i];
   strcpy(tempstr,"ICON ");
   itoa(220+i,s,10);
   strcat(tempstr,s);
   strcat(tempstr," WARP TO SCREEN:");
   xprint(0,y,tempstr,15,PAGE1);
   itoa(nl[i],s,10);
get_again1:
   if(!xinput(25*8,y,s,15,4,3,1,PAGE1)){
     display_help(0);
     xshowpage(PAGE0);
     MSSHOW;
     return;
   }
   nl[i]=atoi(s);
//   if(nl[i]>255){ beep(); goto get_again1;}
   y+=10;

   strcpy(tempstr,"         WARP TO TILE  :");
   xprint(0,y,tempstr,15,PAGE1);
   itoa(ni[i],s,10);
get_again2:
   if(!xinput(25*8,y,s,15,4,3,1,PAGE1)){
     display_help(0);
     xshowpage(PAGE0);
     MSSHOW;
     return;
   }
   ni[i]=atoi(s);
   if(ni[i]>239){ beep(); goto get_again2;}
   y+=10;
}
for(i=0;i<10;i++){
   scrn.new_level[i]=nl[i];
   scrn.new_level_loc[i]=ni[i];
}
display_help(0);
xshowpage(PAGE0);
changed=1;
MSSHOW;
*/
}
//===========================================================================
void edit_pal_data(void){
  int i, y;
  char s[21];
  char pal;

  MSHIDE;

  xcls(0, PAGE1);
  xshowpage(PAGE1);
  xprint(10 * 8, 0, "SCREEN PALETTE EDIT", 14, PAGE1);
  y = 16;

  for (i = 0; i < 3; i++) {
    pal = scrn.pal_colors[i];
    strcpy(tempstr, "COLOR ");
    itoa(i + 1, s, 10);
    strcat(tempstr, s);
    strcat(tempstr, ":");
    xprint(0, y, tempstr, 15, PAGE1);
    itoa(pal, s, 10);
  get_again1:
    if (!xinput(11 * 8, y, s, 15, 4, 3, 1, PAGE1)) {
      display_help(0);
      xshowpage(PAGE0);
      MSSHOW;
      return;
    }
    pal = atoi(s);
    scrn.pal_colors[i] = pal;
    y += 10;
  }
  display_help(0);
  xshowpage(PAGE0);
  set_screen_pal();
  changed = 1;
  MSSHOW;
}
//===========================================================================
int load_sd_data(void) {
  char s[80];

  itoa(area_num, s, 10);
  strcpy(tempstr, "SDAT");
  strcat(tempstr, s);

  sd_data = res_falloc_read(tempstr);
  if (!sd_data) {
    sprintf(s, "Cannot Read %s\r\n", tempstr);
    exit_error(s);
  }
  //_fmemset(sd_data,0,61440u);

  return 1;
}
//===========================================================================
int save_sd_data(void) {
  char s[80];

  itoa(area_num, s, 10);
  strcpy(tempstr, "SDAT");
  strcat(tempstr, s);

  movedata(
    FP_SEG(&scrn),
    FP_OFF(&scrn),
    FP_SEG(sd_data+(current_screen*512)),
    FP_OFF(sd_data+(current_screen*512)),
    512
  );

  res_delete_file(tempstr);
  // TODO set the encode_flag = 1 after https://github.com/joncloud/got/issues/3 is fixed
  if (res_write(tempstr, sd_data, 61440l, 0) < 0) {
    sprintf(s, "Cannot Save %s\r\n", tempstr);
    status_line(s, 12);
    getch();
    display_help(0);
    return 0;
  }
  changed = 0;
  return 1;
}
//===========================================================================
void pickup_tile(void) {
  int x, y, ret;

  xmouse_stat(&mouse);
  if (point_within(mouse.x, mouse.y, 0, 0, 320,192)) {
    x = mouse.x / 16;
    y = mouse.y / 16;
    ret = scrn.icon[y][x];
    current_bg = ret - 10;
    if (current_bg < 0) {
      current_bg += 230;
    }
    hilite_bg = 10;
    show_bg();
    no_button();
  }
}
//===========================================================================
int load_actors(void) {
  int i, x, y, r;
  char s[21];

  memset(actor_flag, 0, 100);
  memset(actor_nf, 0, 100);

  for (i = 1; i < 100; i++) {
    strcpy(tempstr, "ACTOR");
    itoa(i, s, 10);
    strcat(tempstr, s);
    if (res_read(tempstr, (char far*)&actor_buff) < 0) {
      continue;
    }
    MSHIDE;
    if (actor_buff.actor_info.type) {
      actor_nf[i] = actor_buff.actor_info.frames * actor_buff.actor_info.directions;
      actor_nf[i] += actor_buff.shot_info.frames * actor_buff.shot_info.directions;
      actor_flag[i] = 1;

      // Draw the image to the screen, and then copy
      // the screen layout to memory
      xfillrectangle(0,0,16,16,PAGE0,0);
      r = 0;
      for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
          xpset(x, y, PAGE0, actor_buff.pic[1][r++]);
        }
      }

      // TODO https://github.com/joncloud/got/issues/2
      // if (i != 4) {
      //   xget(0, 0, 16, 16, PAGE0, actor[i], 0);
      // }

    }
    MSSHOW;
  }

  return 1;
}
/*=========================================================================*/
int select_actor(void) {
  int x, y, i, li, fn;
  char s[21];

  MSHIDE;

  x = y = 0;
  xcls(0, PAGE1);
  for (i = 0; i < 100; i++) {
    if (actor_flag[i]) {
      xput(x * 16, y * 16, PAGE1, actor[i]);
    }
    x++;
    if (x >= 20) {
      x = 0;
      y++;
    }
  }
  xcopyd2d(0, 0, 8, 8, 0, 0, PAGE1, PAGE2, 320, 320);
  xcopyd2dmasked(0, 0, 8, 8, 0, 0, &mouse_image, PAGE1, 320);
  x = y = 0;
  xshowpage(PAGE1);
  xprint(0, 218, "FRAMES NEEDED:", 15, PAGE1);
  xprint(0, 228, "  FRAMES LEFT:", 15, PAGE1);
  itoa(frames_left, s, 10);
  xprint(15 * 8, 228, s, 14, PAGE1);

  li = -1;
  i = -1;
  while (1) {
    if (kbhit()) {
      if (getch() == 27) {
        i = -1;
        break;
      }
    }
    xmouse_stat(&mouse);
    if (mouse.x != x || mouse.y != y) {
      xcopyd2d(x, y, x + 8, y + 8, x, y, PAGE2, PAGE1, 320, 320);
      x = mouse.x;
      y = mouse.y;
      xcopyd2d(x, y, x + 8, y + 8, x, y, PAGE1, PAGE2, 320, 320);
      xcopyd2dmasked(0, 0, 8, 8, x, y, &mouse_image, PAGE1, 320);
      i = ((y / 16) * 20) + (x / 16);
      if ((i != li) && (i < 100)) {
        i = ((y / 16) * 20) + (x / 16);
        li = i;
        xfillrectangle(120, 218, 320, 228, PAGE1, 0);
        fn = actor_nf[i];
        if (afb[i] == 1) {
          fn = 0;
        }
        itoa(fn, s, 10);
        xprint(15 * 8, 218, s, 14, PAGE1);
        if (fn == 0 && actor_nf[i]) {
          xprint(18 * 8, 218, "(ALREADY USED)", 14, PAGE1);
        }
      }
    }
    if (XMOUSE_LEFT(mouse)) {
      if (i < 0) {
        break;
      }
      if (actor_flag[i] && fn <= frames_left) {
        break;
      }
      beep();
    }
    if (XMOUSE_RIGHT(mouse)) {
      i = -1;
      break;
    }
  }
  xcls(0, PAGE1);
  xshowpage(PAGE0);
  MSSHOW;
  no_button();
  return i;
}
//===========================================================================
void actor_value(void) {
  int i, x, y;

  status_line("CLICK ON ACTOR TO CHANGE", 14);
  while (1) {
    xmouse_stat(&mouse);
    if (mx != mouse.x || my != mouse.y) {
      MSHIDE;
      mx = mouse.x;
      my = mouse.y;
      MSSHOW;
    }
    if (XMOUSE_RIGHT(mouse)) {
      break;
    }
    if (XMOUSE_LEFT(mouse)) {
      x = (mouse.x & 0xfff0);
      y = (mouse.y & 0xfff0);
      for (i = 0; i < LEVEL_MAX_ACTOR; i++) {
        if ((x / 16) + ((y / 16) * 20) == scrn.actor_loc[i]) {
          edit_actor_value(i);
          changed = 1;
          break;
        }
      }
      break;
    }
  }
  show_screen();
  show_objects();
  display_help(0);
  no_button();
}
//===========================================================================
void edit_actor_value(int num) {
  char str[21];

  status_line("ACTOR VALUE: ", 14);
  flush_buff();

  itoa(scrn.actor_value[num], str, 10);
  if (!xinput(13 * 8, 231, str, 15, 4, 5, 1, PAGE0)) {
    display_help(0);
    return;
  }
  scrn.actor_value[num] = atoi(str);
}
//===========================================================================
int pick_tile(void) {
  int lx, ly, x, y, key, hl;
  char s[21];

  no_button();
  lx = -1;
  ly = -1;

  while (1) {
    if (kbhit()) {
      key = getch();
      hl =0;
      in.h.ah = 2;
      int86(0x16, &in, &out);
      //shift
      if ((out.h.al & 1) || (out.h.al & 2)) {
        hl=1;
      }
      switch (key) {
      case 27: return -1;
      case 77:       //right
          if (hl) {
            if (current_screen < 119) {
              save_screen();
              current_screen++;
              view_screen(current_screen);
            }
          }
          break;
      case 75:      //left
          if (hl) {
            if (current_screen > 0) {
              save_screen();
              current_screen--;
              view_screen(current_screen);
            }
          }
          break;
      case 72:       //up
          if (hl) {
            if (current_screen > 9) {
              save_screen();
              current_screen -= 10;
              view_screen(current_screen);
            }
          }
          break;
      case 80:      //down
          if (hl) {
            if (current_screen < 110) {
              save_screen();
              current_screen += 10;
              view_screen(current_screen);
            }
          }
          break;
      }
    }
    xmouse_stat(&mouse);
    if (mouse.x != mx || mouse.y != my) {
      MSHIDE;
      mx = mouse.x;
      my = mouse.y;
      MSSHOW;
    }
    x = mx / 16;
    y = my / 16;
    if (y != ly || x != lx) {
      itoa(scrn.icon[y][x], s, 10);
      xfillrectangle(10 * 8, 218, 32 * 8, 226, PAGE0, 0);
      xprint(10 * 8, 218, "CURRENT:", 15, PAGE0);
      xprint(18 * 8, 218, s, 14, PAGE0);
      lx = x;
      ly = y;
      if (((y * 20) + x) < 240) {
        itoa((y * 20) + x, s, 10);
        xprint(24 * 8, 218, "POS:", 15, PAGE0);
        xprint(28 * 8, 218, s, 14, PAGE0);
      }
    }
    if (XMOUSE_LEFT(mouse)) {
      if (point_within(mx, my, 0, 0, 320, 192)) {
        x = mx / 16;
        y = my / 16;
        if (y < 12 && x < 20) {
          return (y * 20) + x;
        }
      }
    }
    if (XMOUSE_RIGHT(mouse)) {
      return -1;
    }
  }
}
//===========================================================================
void pick_warp(void){
/*
int cs,rs,rt,ct,ri;

cs=current_screen;
save_screen();

warp:
status_line("PICK WARP TILE: ",14);
ct=pick_tile();
if(ct<0) goto abort;

current_screen=cs;
view_screen(current_screen);
ct=scrn.icon[ct/20][ct%20];
if(ct<218 || ct> 229) {beep();goto warp;}

warp1:
status_line("PICK DESTINATION: ",14);
rt=pick_tile();
if(rt<0) goto abort;

rs=current_screen;
ri=scrn.icon[rt/20][rt%20];
if(ri<140 || ri>191) {beep();goto warp1;}

current_screen=cs;
view_screen(current_screen);
if(ct<220){
  scrn.new_level[ct-214]=rs;
  scrn.new_level_loc[ct-214]=rt;
}
else{
  scrn.new_level[ct-220]=rs;
  scrn.new_level_loc[ct-220]=rt;
}
save_screen();
changed=1;

abort:
current_screen=cs;
view_screen(current_screen);
show_screen();
show_objects();
display_help(0);
no_button();
*/
}
//=========================================================================
int get_line(char far* src, char far*dst) {
  int cnt;

  cnt = 0;
  while (*src != 13) {
    if (*src != 10) {
      *dst = *src;
      dst++;
    }
    cnt++;
    src++;
  }
  *dst = 0;
  cnt++;
  src++;
  return cnt;
}
//===========================================================================
int pick_actor(void) {
  int i, x, y, ret;

  while (1) {
    xmouse_stat(&mouse);
    if (mx != mouse.x || my != mouse.y) {
      MSHIDE;
      mx = mouse.x;
      my = mouse.y;
      MSSHOW;
    }
    if (XMOUSE_RIGHT(mouse)) {
      ret = -1;
      break;
    }
    if (XMOUSE_LEFT(mouse)) {
      x = (mouse.x & 0xfff0);
      y = (mouse.y & 0xfff0);
      for (i = 0; i < LEVEL_MAX_ACTOR; i++) {
        if ((x / 16) + ((y / 16) * 20) == scrn.actor_loc[i]) {
          ret = i;
          goto done;
        }
      }
    }
  }
  done:
  show_screen();
  show_objects();
  display_help(0);
  no_button();
  return ret;
}
//===========================================================================
void actor_script(void) {
  int sel, key;
  char far* tbuff;
  char far* bp;
  char far* ap;
  char far* tp;
  char far* op;
  char s[21];
  int cnt;
  char tmps[256];
  FILE* fp;
  FILE* fp2;
  char wf;
  long index;
  char ch;
  union REGS regset;

  fp = (FILE*)0;
  fp2 = (FILE*)0;
  if (area_num == 1) {
    return;
  }

  status_line("Pick Actor to Edit", 12);
  sel = pick_actor();
  if (sel == -1) {
    return;
  }
  sel += 3;

  tbuff = farmalloc(30000l);
  if (!tbuff) {
    status_line("Out of Memeory...Press Any Key.", 12);
    getch();
    display_help(0);
    return;
  }
  itoa(area_num, s, 10);
  strcpy(tempstr, "SPEECH");
  strcat(tempstr, s);
  if (res_read(tempstr, (char far*)tbuff) < 0) {
    status_line("File Open Error...Press Any Key.", 12);
    getch();
    display_help(0);
    goto done;
  }
  index = (long)current_screen;
  index = index * 1000;
  index += (long)sel;

  ltoa(index, s, 10);
  strcpy(tempstr, "|");
  strcat(tempstr, s);

  fp = fopen("BL$$$$$$.TMP", "wt");
  if (!fp) {
    status_line("Cannot Open Temporary file 1...Press Any Key.", 12);
    getch();
    display_help(0);
    goto done;
  }

  ap = (char far*)0;
  bp = (char far*)0;
  tp = tbuff;
  wf = 0;
  while (1) {
    if (!wf) {
      bp = tp;
    }
    cnt = get_line(tp, (char far*)tmps);
    tp += cnt;
    if (!strcmp(tmps, "|EOF")) {
      if (!wf) {
        fputs(tempstr, fp);
        fputs("\n'put script here\n", fp);
        fputs("|STOP\n", fp);
        ap = bp + 1;
      }
      break;
    }
    if (!wf && !strcmp(tmps, tempstr)) {
      wf = 1;
    }
    if (wf == 1) {
      fputs(tmps, fp);
      fputs("\n", fp);
    }
    if (wf == 1 && !strcmp(tmps, "|STOP")) {
      wf = 2;
      ap = tp + 1;
    }
  }
  fclose(fp);
  fp = (FILE*)0;

  regset.x.ax = 0x0003;
  int86(0x10, &regset, &regset);
  // system("BLEDIT BL$$$$$$.TMP");
  reset_mode();

  status_line("Save Changes to Script? (Y/N)", 12);
  flush_buff();
  while (1) {
    key = toupper(getch());
    if (key == 'Y') {
      break;
    }
    else if (key == 'N') {
      goto done;
    }
  }
  fp = fopen("BL$$$$$$.TXT", "wb");
  if (!fp) {
    status_line("Cannot Open Temporary file 2...Press Any Key.", 12);
    getch();
    display_help(0);
    goto done;
  }
  fp2 = fopen("BL$$$$$$.TMP", "rt");
  if (!fp2) {
    status_line("Cannot Open Temporary file 1 (again)...Press Any Key.", 12);
    getch();
    display_help(0);
    goto done;
  }
  op = tbuff;
  while (op <= bp) {
    ch = *op;
    fwrite(&ch, 1, 1, fp);
    op++;
  }
  while (1) {
    if (!fgets(tmps, 255, fp2)) {
      break;
    }
    ch = strlen(tmps) - 1;
    tmps[ch++] = 13;
    tmps[ch++] = 10;
    tmps[ch++] = 0;
    fwrite(tmps, 1, strlen(tmps), fp);
  }
  op = ap;
  while (op != tp) {
    ch = *op;
    fwrite(&ch, 1, 1, fp);
    op++;
  }
  fclose(fp);
  fp = (FILE*)0;
  fclose(fp2);
  fp2 = (FILE*)0;

  itoa(area_num, s, 10);
  strcpy(tempstr, "SPEECH");
  strcat(tempstr, s);
  if (res_delete_file(tempstr) < 0) {
    status_line("Cannot Delete Resource...Press Any Key.", 12);
    getch();
    display_help(0);
    goto done;
  }
  if (res_add_file("BL$$$$$$.TXT", tempstr, 1) < 0) {
    status_line("Cannot Add Resource: BL$$$$$$.TXT", 12);
    getch();
    display_help(0);
    goto done;
  }
  res_close();
  if (res_open(res_file) < 0) {
    sprintf(tempstr, "Cannot Open: %s\r\n\r\n", res_file);
    exit_error(tempstr);
  }
  unlink("BL$$$$$$.TMP");
  unlink("BL$$$$$$.TXT");

  done:
  if (fp) {
    fclose(fp);
  }
  if (fp2) {
    fclose(fp2);
  }
  if (tbuff) {
    farfree(tbuff);
  }
}
//===========================================================================
void reset_mode(void) {
  xsetmode();
  xmouse_init();
  xmouse_off();
  xmouse_set_bounds(0, 0, 624, 231);
  xmouse_set_pos(320, 120);
  xmouse_stat(&mouse);
  if (xcreatmaskimage(&mouse_image, PAGE3, mcursor, 8, 8, mmask) == 0) {
    exit_code();
    exit(0);
  }

  //setup background
  xshowpage(PAGE0);
  display_help(0);
  load_palette();
  show_screen();
  show_objects();
  show_bg();
  show_current_object();
}
