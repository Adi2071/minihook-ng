#ifndef __DRAWING__
#define __DRAWING__


void __fastcall DrawingDrawCircle(int x, int y, int r, bool solid);
void __fastcall DrawingDrawLine(int xs, int ys, int xe, int ye);
void __fastcall DrawingDrawRectangle(int x, int y, int w, int h, bool solid);
void __fastcall DrawingSetLineWidth(float w);
void __fastcall DrawingSetColor(int r, int g, int b, int a);
void DrawingBegin(void);
void inline DrawingEnd(void);

void DrawConString (int x, int y, int r, int g, int b, const char *fmt, ... );

#endif