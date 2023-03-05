#ifndef MU_MAN_H_
#define MU_MAN_H_

void MU_MusicOff(void);
void MU_MusicOn(void);
int MU_MusicPlaying(void);
void MU_StartMusic(char far* music, int repeat);
void MU_Service(void);

#endif
