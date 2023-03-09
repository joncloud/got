#ifndef LEVEL_H_
#define LEVEL_H_

typedef struct {           //size=512
  char icon[12][20];       //0   grid of icons
  char bg_color;           //240 background color
  char type;               //241 music
  char actor_type[16];     //242 type of enemies (12 max)
  char actor_loc[16];      //254 location of enemies
  char actor_value[16];    //pass value
  char pal_colors[3];      //change 251,253,254 to these three
  char actor_invis[16];
  char extra[13];
  char static_obj[30];     //302 static objects (treasure, keys,etc)
  int  static_x[30];       //332 X coor of static objects
  int  static_y[30];       //392 Y coor of static objects
  char new_level[10];      //452 level jump for icon 200-204
  char new_level_loc[10];  //462 grid location to jump in to
  char area;               //472 game area (1=forest,etc)
  char actor_dir[16];      //initial dir
  char future[3];          //473
} LEVEL;

#endif
