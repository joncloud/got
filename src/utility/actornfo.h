#ifndef ACTORNFO_H_
#define ACTORNFO_H_

typedef struct {           //size=40
  char move;               //movement pattern (0=none)
  char width;              //physical width
  char height;             //physical height
  char directions;         //1,2 or 4 (1=uni-directional)
  char frames;             //# frames per direction
  char frame_speed;        //# cycles between frame changes
  char frame_sequence[4];  //sequence
  char speed;              //move every Nth cycle
  char size_x;             //non-physical padding on X coor
  char size_y;             //non-phsyical padding on Y coor
  char strength;           //hit strength
  char health;             //
  char num_moves;          //# of moves every <speed> cycles
  char shot_type;          //actor # of shot
  char shot_pattern;       //func number to decide to shoot
  char shots_allowed;      //# shots allowed on screen
  char solid;              //1=solid (not ghost,etc)
  char flying;             //
  char rating;             //rnd(100) < rating = jewel
  char type;               //actor (0=thor,1=hammer,2=enemy,3=shot)
  char name[9];            //actors name
  char func_num;           //special function when thor touches
  char func_pass;          //value to pass to func
  char future1[6];
} ACTOR_NFO;

#endif
