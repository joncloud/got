#ifndef JOY_H_
#define JOY_H_

typedef struct joystick_input {
  unsigned int x;
  unsigned int y;
  char b1;
  char b2;
} joystick_input;

void read_joystick(joystick_input* joy);

#endif
