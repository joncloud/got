#include "g_mask.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void xpset(int X, int Y, unsigned int PageBase, int Color);

void xline(int x0,int y0,int x1,int y1,int page,int color) {
int x,y;

if(x0==x1 && y0==y1) xpset(x0, y0, page, color);

else if(abs(x1-x0) >= abs(y1-y0)){
     if(x1<x0){
       x=x1;
       y=y1;
       x1=x0;
       y1=y0;
       x0=x;
       y0=y;
     }
     for(x=x0;x<=x1;x++){
        y=(int) (y0+((x-x0)*(long)(y1-y0))/(x1-x0));
        xpset(x, y, page, color);
     }
}
else{
  if(y1<y0){
    x=x1;
    y=y1;
    x1=x0;
    y1=y0;
    x0=x;
    y0=y;
  }
  for(y=y0;y<=y1;y++){
     x=(int) (x0+((y-y0)*(long)(x1-x0))/(y1-y0));
     xpset(x, y, page, color);
  }
}
}

void xput2(int x,int y,unsigned int pagebase,char *buff) {
  // TODO
  (void)x;
  (void)y;
  (void)pagebase;
  (void)buff;
}

void xcopyd2dmasked(int SourceStartX,
     int SourceStartY, int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MaskedImage * Source,
     unsigned int DestPageBase, int DestBitmapWidth) {
  // TODO https://github.com/joncloud/got/issues/1
  int i, j, k;
  int sourceWidth, sourceHeight;
  int destWidth, destHeight;
  int sourceX, sourceY, destX, destY;
  char* sourceMask;
  char* destMask;
  unsigned int sourcePtr, destPtr;
  AlignedMaskedImage* alignment;

  // Determine the width and height of the source and destination rectangles
  sourceWidth = SourceEndX - SourceStartX + 1;
  sourceHeight = SourceEndY - SourceStartY + 1;
  destWidth = sourceWidth;
  destHeight = sourceHeight;

  // Iterate over each alignment of the source mask-image pair
  for(i = 0; i < 4; i++) {
    alignment = Source->Alignments[i];

    // Determine the source and destination coordinates for this alignment
    switch(i) {
      case 0: // Top-left alignment
        sourceX = SourceStartX;
        sourceY = SourceStartY;
        destX = DestStartX;
        destY = DestStartY;
        break;
      case 1: // Top-right alignment
        sourceX = SourceStartX + sourceWidth - 1;
        sourceY = SourceStartY;
        destX = DestStartX + destWidth - 1;
        destY = DestStartY;
        break;
      case 2: // Bottom-left alignment
        sourceX = SourceStartX;
        sourceY = SourceStartY + sourceHeight - 1;
        destX = DestStartX;
        destY = DestStartY + destHeight - 1;
        break;
      case 3: // Bottom-right alignment
        sourceX = SourceStartX + sourceWidth - 1;
        sourceY = SourceStartY + sourceHeight - 1;
        destX = DestStartX + destWidth - 1;
        destY = DestStartY + destHeight - 1;
        break;
    }

    // Compute the starting addresses of the source and destination bitmaps
    sourcePtr = alignment->ImagePtr + sourceY * alignment->ImageWidth + sourceX;
    destPtr = DestPageBase + destY * DestBitmapWidth + destX;

    // Copy the pixels from the source bitmap to the destination bitmap, respecting the mask bitmap
    sourceMask = alignment->MaskPtr + sourceY * ((alignment->ImageWidth + 7) / 8);
    destMask = (char *) (DestPageBase + DestBitmapWidth * (destY / 8) + destX);
    for(j = 0; j < sourceHeight; j++) {
      for(k = 0; k < sourceWidth; k++) {
        if(sourceMask[k / 8] & (1 << (7 - (k % 8)))) {
          *(char *)(destMask + (k / 8)) |= (1 << (7 - (k % 8)));
          *(char *)destPtr = *(char *)sourcePtr;
        }
        sourcePtr++;
        destPtr++;
      }
      sourceMask += (alignment->ImageWidth + 7) / 8;
      destMask += DestBitmapWidth / 8;
      destPtr += DestBitmapWidth - sourceWidth;
    }
  }
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

unsigned int xcreatmaskimage(MaskedImage * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask) {
  unsigned int totalImageSize;
  unsigned int currentPtr;
  int i, j;

  totalImageSize = (ImageWidth * ImageHeight) + ((ImageWidth + 7) / 8) * ImageHeight;
  currentPtr = DispMemStart;

  for (i = 0; i < 4; i++) {
    ImageToSet->Alignments[i] = (AlignedMaskedImage *) malloc(sizeof(AlignedMaskedImage));
    ImageToSet->Alignments[i]->ImageWidth = ImageWidth;
    ImageToSet->Alignments[i]->ImagePtr = currentPtr;
    ImageToSet->Alignments[i]->MaskPtr = (char *) malloc(totalImageSize);

    memset(ImageToSet->Alignments[i]->MaskPtr, 0, totalImageSize);

    for (j = 0; j < ImageHeight; j++) {
      memcpy((char *) currentPtr, Image + j * ImageWidth, ImageWidth);
      currentPtr += ImageWidth;

      memcpy(ImageToSet->Alignments[i]->MaskPtr + j * ((ImageWidth + 7) / 8), Mask + j * ((ImageWidth + 7) / 8), (ImageWidth + 7) / 8);
    }

    currentPtr += ((ImageWidth + 7) / 8) * ImageHeight;
  }

  return DispMemStart;
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
  return 0;
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
