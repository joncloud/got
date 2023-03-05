//from X_LIBA.ASM

void XGet(int x1,int y1,int x2,int y2,unsigned int PageBase,
          char far *Buff,int Invis);
void XPut(int x,int y, unsigned int PageBase,char far *Buff);
void XShowPage(unsigned int PageBase);
void XText(int x, int y,unsigned int PageBase,char *Buff,int Color);
void XCopyDD(int SourceStartX, int SourceStartY,int SourceEndX, int SourceEndY,
             int DestStartX,int DestStartY,
             unsigned int SourcePageBase,unsigned int DestPageBase,
             int SourceWidth,int DestWidth); //normally 320
void XCopySD(int SourceStartX, int SourceStartY,int SourceEndX, int SourceEndY,
             int DestStartX,int DestStartY,
             char far *SourcePtr,unsigned int DestPageBase,
             int SourceWidth,int DestWidth);
void XFillBox(int StartX,int StartY,int EndX,int EndY,
              unsigned int PageBase,int Color)
void XSetModeX(void);
void XSet(int x,int y, unsigned int PageBase,int Color);
int  XPoint(int x,int y,unsigned int PageBase);
void XSetPalOne(char Index,char Red,char Green,char Blue);
void XSetPalAll(char far *Palette);
void XGetPalAll(char far *Buff,int NumColors,int StartColor);
void XPalFadeIn(char far *Palette);
void XPalFadeOut(char far *Palette);




void JoyRead(void);
