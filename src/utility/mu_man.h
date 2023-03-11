#ifndef MU_MAN_H_
#define MU_MAN_H_

#include "modern.h"

/**
 * Turns off any music that is playing.
 */
void MU_MusicOff(void);

/**
 * Turns on music, and if it was originally
 * playing it resumes where it left off.
 */
void MU_MusicOn(void);

/**
 * Determines whether or not music is playing.
 * @returns 1 if music is playing, otherwise 0.
 */
int MU_MusicPlaying(void);

/**
 * Starts playing music.
 * @param buffer A memory buffer to music data.
 * @param length The total length of the memory buffer.
 */
void MU_StartMusic(char far* buffer, long length);

/**
 * Service function to play music notes on the 0x8
 * interrupt running at 120hz.
 */
void MU_Service(void);

#endif
