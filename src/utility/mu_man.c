#include "mu_man.h"

#include "adlib.h"
#include <alloc.h>

typedef struct {
  // Number of ticks to wait *after* the data has been sent
  unsigned char delay;
  // OPL register to write to
  unsigned char opl_register;
  // Value to write
  unsigned char opl_value;
} fm_music_note;

typedef struct {
  // The original memory buffer including the header information
  char far*          origin;
  // The offset to start playing when looping
  fm_music_note far* loop_offset;
  // The total length of the music
  long               length;
  // The pointer to the initial note memory buffer
  fm_music_note far* notes;
} fm_music;

void      MU_StopInternal(void);
fm_music* MU_ConvertOpl(char far* buffer, long length);
void      MU_FreeFMMusic(fm_music* m);

long               MU_TicksElapsed = 0;
unsigned char      MU_IsPlaying = 0;
fm_music*          MU_FMMusic = 0;
fm_music_note far* MU_FMNote = 0;
long               MU_DataLeft = 0;
long               MU_NextEventTime = 0;

void MU_MusicOff(void) {
  MU_StopInternal();
}

void MU_MusicOn(void) {
  if (MU_FMMusic) {
    MU_IsPlaying = 1;
  }
}

int MU_MusicPlaying(void) {
  return MU_IsPlaying;
}

void MU_StartMusic(char far* buffer, long length) {
  fm_music* m;

  m = MU_ConvertOpl(buffer, length);
  if (!m) {
    return;
  }

  if (MU_FMMusic) {
    MU_FreeFMMusic(MU_FMMusic);
  }

  MU_FMMusic = m;
  MU_FMNote = m->notes;
  MU_IsPlaying = 1;
  MU_DataLeft = m->length;
  MU_NextEventTime = 0;
  MU_TicksElapsed = 0;
}

void MU_Service(void) {
  if (!MU_IsPlaying) {
    return;
  }

  // If enough time has passed for the next event to be due, keep reading
  // events and feeding them to the AdLib hardware until we encounter an event
  // with a non-zero delay value.
  while (MU_DataLeft > 3 && MU_NextEventTime <= MU_TicksElapsed && MU_IsPlaying) {
    SB_ALOut(MU_FMNote->opl_register, MU_FMNote->opl_value);
    MU_NextEventTime = MU_TicksElapsed + MU_FMNote->delay;
    MU_FMNote += 1;
    MU_DataLeft -= sizeof(fm_music_note);
  }

  MU_TicksElapsed++;

  // Once the entire song has been played, loop back to the beginning
  if (MU_DataLeft < 3) {
    MU_FMNote = MU_FMMusic->loop_offset;

    // TODO length should take into account when loop_offset > 0
    MU_DataLeft = MU_FMMusic->length;
    MU_TicksElapsed = MU_NextEventTime = 0;
  }
}

fm_music* MU_ConvertOpl(char far* buffer, long length) {
  fm_music* m;
  int offset;

  m = (fm_music*)malloc(sizeof(fm_music));
  if (!m) {
    return 0;
  }

  m->origin = buffer;

  // All of the song offsets are 0x0001, so set the loop offset
  // to be 0 based instead of 1 based.
  offset = (*buffer
    | (*(buffer + 1) << 8))
    - 1;
  m->loop_offset = (fm_music_note far*)(buffer + 2 + offset);
  m->notes = (fm_music_note far*)(buffer + 2);
  m->length = (length - 2);

  return m;
}

void MU_FreeFMMusic(fm_music* m) {
  if (!m) {
    return;
  }
  if (m->origin) {
    farfree(m->origin);
  }
  free(m);
}

void MU_StopInternal(void) {
  MU_IsPlaying = 0;
  SB_AL_ResetChannels();
}
