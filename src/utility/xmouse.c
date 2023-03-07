#include "xmouse.h"
#include <dos.h>

struct REGPACK xmouse_reg;

void xmouse_int33(void);

void xmouse_int33(void) {
  intr(0x33, &xmouse_reg);
}

int xmouse_init(void) {
  // https://stanislavs.org/helppc/int_33-0.html
  // INT 33,0 - Mouse Reset/Get Mouse Installed Flag
  // AX = 00
  // on return:
  // AX = 0000  mouse driver not installed
  //      FFFF  mouse driver installed
  // BX = number of buttons

  int mouse_available;

  xmouse_reg.r_ax = 0x00;
  xmouse_reg.r_bx = 0x00;
  xmouse_int33();

  mouse_available = xmouse_reg.r_ax;

  return mouse_available;
}

void xmouse_on(void) {
  // https://stanislavs.org/helppc/int_33-1.html
  // INT 33,1 - Show Mouse Cursor
  // AX = 01
  // returns nothing

  xmouse_reg.r_ax = 0x01;
  xmouse_int33();
}

void xmouse_off(void) {
  // https://stanislavs.org/helppc/int_33-2.html
  // INT 33,2 - Hide Mouse Cursor
  // AX = 02
  // returns nothing

  xmouse_reg.r_ax = 0x02;
  xmouse_int33();
}

void xmouse_stat(xmouse* m) {
  // https://stanislavs.org/helppc/int_33-3.html
  // INT 33,3 - Get Mouse Position and Button Status
  // AX = 03
  // on return:
  // CX = horizontal (X) position  (0..639)
  // DX = vertical (Y) position  (0..199)
  // BX = button status:
  // |F-8|7|6|5|4|3|2|1|0|  Button Status
  //   |  | | | | | | | `---- left button (1 = pressed)
  //   |  | | | | | | `----- right button (1 = pressed)
  //   `------------------- unused

  xmouse_reg.r_ax = 0x03;
  xmouse_reg.r_bx = 0x00;
  xmouse_reg.r_cx = 0x00;
  xmouse_reg.r_dx = 0x00;
  xmouse_int33();

  m->x = xmouse_reg.r_cx;
  m->y = xmouse_reg.r_dx;
  m->button = xmouse_reg.r_bx;
}

void xmouse_set_bounds(int x1, int y1, int x2, int y2) {
  // https://stanislavs.org/helppc/int_33-7.html
  // INT 33,7 - Set Mouse Horizontal Min/Max Position
  // AX = 7
  // CX = minimum horizontal position
  // DX = maximum horizontal position
  // returns nothing

  xmouse_reg.r_ax = 0x07;
  xmouse_reg.r_cx = x1;
  xmouse_reg.r_dx = x2;
  xmouse_int33();

  // https://stanislavs.org/helppc/int_33-8.html
  // INT 33,8 - Set Mouse Vertical Min/Max Position
  // AX = 8
  // CX = minimum vertical position
  // DX = maximum vertical position
  // returns nothing

  xmouse_reg.r_ax = 0x08;
  xmouse_reg.r_cx = y1;
  xmouse_reg.r_dx = y2;
  xmouse_int33();
}

void xmouse_set_pos(int x, int y) {
  // https://stanislavs.org/helppc/int_33-4.html
  // INT 33,4 - Set Mouse Cursor Position
  // AX = 4
  // CX = horizontal position
  // DX = vertical position
  // returns nothing

  xmouse_reg.r_ax = 0x04;
  xmouse_reg.r_cx = x;
  xmouse_reg.r_dx = y;
  xmouse_int33();
}
