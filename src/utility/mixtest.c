#include <stdio.h>

#include <r_proto.h>
#include <window.h>
#include <mouse.h>
#include <keyboard.h>
#include <defaults.h>
#include <controls.h>
//===========================================================================
void set_default_colors(void);
//===========================================================================
void main(void){
Window w1;
Control b1;

set_default_colors();

w1=w_open(25,7,30,10);
w_print(w1," Eat Me!!");
b1=c_add_button(w1,"  ~Ok  ",11,8,0x0001,BUTTON_SHADOW_RIGHT);


wait_key();
w_close(w1);
}

//===========================================================================
void set_default_colors(void){

d_change(SYSBGCOLOR,03);
d_change(WBRDTYPE,BRD_DDDD);
d_change(WCOLOR,23);
d_change(WBRDCOLOR,31);
d_change(BUTTONCOLOR,112);
d_change(BHIGHLTCOLOR,127);


}

