#include "g_mask.h"

void xsetmode(void) {
  // TODO (this is in g_asm.asm)
}

void xshowpage(unsigned page) {
  // TODO (this is in g_asm.asm)
  (void)page;
}

void xline(int x0,int y0,int x1,int y1,int page,int color) {
  // TODO
  (void)x0;
  (void)y0;
  (void)x1;
  (void)y1;
  (void)page;
  (void)color;
}

void xfillrectangle(int StartX, int StartY, int EndX, int EndY,
                    unsigned int PageBase, int Color) {
  // TODO (this is in g_asm.asm)
  (void)StartX;
  (void)StartY;
  (void)EndX;
  (void)EndY;
  (void)PageBase;
  (void)Color;
}

void xpset(int X, int Y, unsigned int PageBase, int Color) {
  // TODO (this is in g_asm.asm)
  (void)X;
  (void)Y;
  (void)PageBase;
  (void)Color;
}

int xpoint(int X, int Y, unsigned int PageBase) {
  // TODO (this is in g_asm.asm)
  (void)X;
  (void)Y;
  (void)PageBase;
  return 0;
}

void xget(int x1,int y1,int x2,int y2,unsigned int pagebase,
          char far *buff,int invis) {
  // TODO (this is in g_asm.asm)
  (void)x1;
  (void)y1;
  (void)x2;
  (void)y2;
  (void)pagebase;
  (void)buff;
  (void)invis;
}

void xput(int x,int y,unsigned int pagebase,char *buff) {
  // TODO (this is in g_asm.asm)
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
}

void xput2(int x,int y,unsigned int pagebase,char *buff) {
  // TODO
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
}

void xtext(int x,int y,unsigned int pagebase,char far *buff,int color) {
  // TODO (this is in g_asm.asm)
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
  (void)color;
}

void xtext1(int x,int y,unsigned int pagebase,char far *buff,int color) {
  // TODO (this is in g_asm.asm)
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
  (void)color;
}

void xtextx(int x,int y,unsigned int pagebase,char far *buff,int color) {
  // TODO (this is in g_asm.asm)
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
  (void)color;
}

void xfput(int x,int y,unsigned int pagebase,char far *buff) {
  // TODO (this is in g_asm.asm)
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
}

void xfarput(int x,int y,unsigned int pagebase,char far *buff) {
  // TODO (this is in g_asm.asm)
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
}

void xcopyd2dmasked(int SourceStartX,
     int SourceStartY, int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage * Source,
     unsigned int DestPageBase, int DestBitmapWidth) {
  // TODO
  (void)SourceStartX;
  (void)SourceStartY;
  (void)SourceEndX;
  (void)SourceEndY;
  (void)DestStartX;
  (void)DestStartY;
  (void)Source;
  (void)DestPageBase;
  (void)DestBitmapWidth;
}

void xcopyd2dmasked2(
     int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage *Source,
     unsigned int DestPageBase) {
  // TODO
  (void)SourceEndX;
  (void)SourceEndY;
  (void)DestStartX;
  (void)DestStartY;
  (void)Source;
  (void)DestPageBase;
}

void xcopys2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, char* SourcePtr, unsigned int DestPageBase,
     int SourceBitmapWidth, int DestBitmapWidth) {
  // TODO (this is in g_asm.asm)
  (void)SourceStartX;
  (void)SourceStartY;
  (void)SourceEndX;
  (void)SourceEndY;
  (void)DestStartX;
  (void)DestStartY;
  (void)SourcePtr;
  (void)DestPageBase;
  (void)DestBitmapWidth;
}

void xcopyd2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, unsigned int SourcePageBase,
     unsigned int DestPageBase, int SourceBitmapWidth,
     int DestBitmapWidth) {
  // TODO (this is in g_asm.asm)
  (void)SourceStartX;
  (void)SourceStartY;
  (void)SourceEndX;
  (void)SourceEndY;
  (void)DestStartX;
  (void)DestStartY;
  (void)SourcePageBase;
  (void)DestPageBase;
  (void)SourceBitmapWidth;
  (void)DestBitmapWidth;
}

unsigned int xcreatmaskimage(MaskedImage * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask) {
  // TODO
  (void)ImageToSet;
  (void)DispMemStart;
  (void)Image;
  (void)ImageWidth;
  (void)ImageHeight;
  (void)Mask;
}
unsigned int xcreatmaskimage2(MaskedImage * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask) {
  // TODO
  (void)ImageToSet;
  (void)DispMemStart;
  (void)Image;
  (void)ImageWidth;
  (void)ImageHeight;
  (void)Mask;
}

void xddfast(int source_x,int source_y, int width, int height,
             int dest_x, int dest_y,
             unsigned int source_page,unsigned int dest_page) {
  // TODO
  (void)source_x;
  (void)source_y;
  (void)width;
  (void)height;
  (void)dest_x;
  (void)dest_y;
  (void)source_page;
  (void)dest_page;
}

xsetpal(unsigned char color, unsigned char R,unsigned char G,unsigned char B) {
  // TODO (this is in g_asm.asm)
  (void)color;
  (void)R;
  (void)G;
  (void)B;
}

xgetpal(char far * pal, int num_colrs, int start_index) {
  // TODO (this is in g_asm.asm)
  (void)pal;
  (void)num_colrs;
  (void)start_index;
}
