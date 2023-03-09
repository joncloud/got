#ifndef ACTORDAT_H_
#define ACTORDAT_H_

#include "actornfo.h"

typedef struct {        //5200
  char pic[16][256];    //4096
  char shot[4][256];    //1024
  ACTOR_NFO actor_info; //40
  ACTOR_NFO shot_info;  //40
} ACTOR_DATA;

#endif
