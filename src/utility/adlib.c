#include "adlib.h"

void SB_ALOut(unsigned char reg, unsigned char val) {
  // Lock
  asm pushf
  asm cli

  // Write address register
  asm mov   dx, 0x388
  asm mov   al, [reg]
  asm out   dx, al

  // Wait for at least 3.3 usecs by executing 6 IN instructions
  // (as recommended in the AdLib documentation)
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx

  // Write data register
  asm mov   dx, 0x389
  asm mov   al, [val]
  asm out   dx, al

  asm popf

  // Wait for at least 23 usecs by executing 35 IN instructions
  // (as recommended in the AdLib documentation)
  asm mov   dx, 0x388
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx

  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx

  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx

  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
  asm in    al, dx
}

void SB_AL_ResetChannels(void) {
  int i;

  // Silence any rhythm mode instruments (none of the music files shipping with
  // the game make use of rhythm mode)
  SB_ALOut(0xBD, 0);

  // Set the "key on" bit to 0 for AdLib channels 2 to 9. This stops any
  // currently playing notes on those channels, but doesn't necessarily stop
  // audio output, depending on the release envelope setting for the instrument.
  // If audio output keeps going, it will be at a fairly low frequency, since
  // setting the register to 0 doesn't just alter the "key on" bit, it also
  // changes the octave (aka "block") to the lowest one and unsets the two most
  // significant bits of the channel's current frequency value.
  //
  // Channel 1 is reserved for sound effects, and thus left unchanged.
  //
  // [BUG] The loop should only go from 0 to 7, i.e. the condition should be
  // `i < 8`. There are only 9 AdLib channels in total, with 0xB8 addressing
  // the 9th channel. The loop thus ends up writing two non-existant registers,
  // but this doesn't seem to cause any issues.
  for (i = 0; i < 10; i++) {
    SB_ALOut(0xB1 + (unsigned char)i, 0);
  }
}
