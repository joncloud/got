#ifndef XMOUSE_H_
#define XMOUSE_H_

typedef struct xmouse {
  unsigned int x;
  unsigned int y;
  unsigned int button;
} xmouse;

#define XMOUSE_LEFT(m)  m.button & 0x01
#define XMOUSE_RIGHT(m) m.button & 0x02

int  xmouse_init(void);
void xmouse_on(void);
void xmouse_off(void);
void xmouse_stat(xmouse* m);
void xmouse_set_bounds(int x1, int y1, int x2, int y2);
void xmouse_set_pos(int x, int y);

#endif
