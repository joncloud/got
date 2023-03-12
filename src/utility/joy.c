#include "joy.h"
#include <dos.h>

void read_joystick(joystick_input* joy) {
  unsigned char al;
  unsigned int di=0, bx=0, cx=-1;
  unsigned int dx=0x201;

  // No interrupts
  asm pushf
  asm cli

  // Any random number tell hardware to start
  al = inportb(dx);
  outportb(dx, al);

  do {
    al = inportb(dx);
    if ((al & 3) == 0) {
      continue;
    }
    if (al & 1) {
      di++;
    }
    if (al & 2) {
      bx++;
    }
  } while (--cx);

  joy->y = bx;
  joy->x = di;

  // Read buttons
  al = inportb(dx);
  joy->b1 = al & 0x10;
  joy->b1 ^= 0x10;
  joy->b2 = al & 0x20;

  // restore flags (restores int bit)
  asm popf
}
