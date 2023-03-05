void xsetmode(void);
void xshowpage(unsigned page);
void xfput(int x,int y,unsigned int pagebase,char far *buff);
void xcopyd2dmasked(int SourceStartX,
     int SourceStartY, int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage * Source,
     unsigned int DestPageBase, int DestBitmapWidth);
void xcopyd2dmasked2(
     int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage * Source,
     unsigned int DestPageBase);
void xcopys2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, char* SourcePtr, unsigned int DestPageBase,
     int SourceBitmapWidth, int DestBitmapWidth);
void xcopyd2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, unsigned int SourcePageBase,
     unsigned int DestPageBase, int SourceBitmapWidth,
     int DestBitmapWidth);
void xline(int x0,int y0,int x1,int y1,int color,int page);
unsigned int xcreatmaskimage(MaskedImage * ImageToSet,
   unsigned int DispMemStart, char * Image, int ImageWidth,
   int ImageHeight, char * Mask);
void xpset(int X, int Y, unsigned int PageBase, int Color);
void xget(int x1,int y1,int x2,int y2,unsigned int pagebase,
          char *buff,int invis);
void xput(int x,int y,unsigned int pagebase,char *buff);
void xtext(int x,int y,unsigned int pagebase,char *buff,int color);
void xfillrectangle(int StartX, int StartY, int EndX, int EndY,
                    unsigned int PageBase, int Color);

unsigned int xcreatemaskimage(MaskedImage * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask);

unsigned int xcreatmaskimage2(MaskedImage * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask);

void xcopyd2dmasked(int SourceStartX,
     int SourceStartY, int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage * Source,
     unsigned int DestPageBase, int DestBitmapWidth);
unsigned int xpoint(int X, int Y, unsigned int PageBase);
