#ifndef FX_MAN_H_
#define FX_MAN_H_

typedef struct {
  int priority;
} PCSound;

void FX_ServicePC(void);
void FX_StopPC(void);
int  FX_PCPlaying(void);
void FX_PlayPC(PCSound far* sound, long length);

#endif
