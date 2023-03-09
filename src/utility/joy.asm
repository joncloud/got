;Source code released to the public domain on March 27th, 2020.

.286
MASM51
QUIRKS
LOCALS
.MODEL MEDIUM,C

.data

joy_x   DW 0
joy_y   DW 0
joy_b1  DB 0
joy_b2  DB 0

.code

PROC         read_joystick
      PUBLIC read_joystick
      USES   di

      pushf
      cli   ;no interrupts
      xor   di,di
      xor   bx,bx
      mov   dx,201h
      out   dx,al      ;Any random number tell hardware to start
      mov   cx,-1
@@10: in    al,dx
      test  al,3
      jz    @@90
      test  al,1
      jz    @@20
      inc   di
@@20: test  al,2
      jz    @@30
      inc   bx
@@30: loop  @@10

@@90: mov   joy_y,bx
      mov   joy_x,di

      in    al,dx      ;read buttons
      mov   joy_b1,al
      and   joy_b1,10000b
      xor   joy_b1,10000b

      and   al,100000b
      xor   al,100000b
      mov   joy_b2,al

      popf  ;restore flags, (restores int bit)
      ret
read_joystick ENDP

END
