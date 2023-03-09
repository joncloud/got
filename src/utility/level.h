#ifndef LEVEL_H_
#define LEVEL_H_

#define LEVEL_ROWS           12
#define LEVEL_COLUMNS        20
#define LEVEL_MAX_ACTOR      16
#define LEVEL_MAX_PAL        3
#define LEVEL_MAX_STATIC_OBJ 30
#define LEVEL_MAX_NEW_LEVEL  10

typedef struct {                           //size=512
  char icon[LEVEL_ROWS][LEVEL_COLUMNS];    //0   grid of icons
  char bg_color;                           //240 background color
  char type;                               //241 music
  char actor_type[LEVEL_MAX_ACTOR];        //242 type of enemies (12 max)
  char actor_loc[LEVEL_MAX_ACTOR];         //254 location of enemies
  char actor_value[LEVEL_MAX_ACTOR];       //pass value
  char pal_colors[LEVEL_MAX_PAL];          //change 251,253,254 to these three
  char actor_invis[LEVEL_MAX_ACTOR];
  char extra[13];
  char static_obj[LEVEL_MAX_STATIC_OBJ];   //LEVEL_MAX_STATIC_OBJ2 static objects (treasure, keys,etc)
  int  static_x[LEVEL_MAX_STATIC_OBJ];     //332 X coor of static objects
  int  static_y[LEVEL_MAX_STATIC_OBJ];     //392 Y coor of static objects
  char new_level[LEVEL_MAX_NEW_LEVEL];     //452 level jump for icon 200-204
  char new_level_loc[LEVEL_MAX_NEW_LEVEL]; //462 grid location to jump in to
  char area;                               //472 game area (1=forest,etc)
  char actor_dir[LEVEL_MAX_ACTOR];         //initial dir
  char future[3];                          //473
} LEVEL;

#endif
