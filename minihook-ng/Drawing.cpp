#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
//#include <gl/glaux.h>
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLu32.lib")
//#pragma comment(lib, "GLaux.lib")

//=============================
// DrawingBegin
// Initializes our drawing matrix
//=============================
void DrawingBegin(void)
{
	glPushMatrix(); 
	glLoadIdentity();  
	glDisable(GL_TEXTURE_2D); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

//=============================
// DrawingBegin
// disables our drawing matrix
//=============================
void DrawingEnd(void)
{
	glDisable(GL_BLEND); 
	glEnable(GL_TEXTURE_2D); 
	glPopMatrix();
}

//=============================
// DrawingSetColor
// Set r,g,b,(a) color for drawing 
//=============================
void __fastcall DrawingSetColor(int r, int g, int b)
{
	glColor3ub(r, g, b);
}

void __fastcall DrawingSetColor(int r, int g, int b, int a)
{
	glColor4ub(r, g, b, a);
}

//=============================
// DrawingSetLineWidth
// Set the width of lines to draw
//=============================
void __fastcall DrawingSetLineWidth(float w)
{
	glLineWidth(1.0f);
}

//=============================
// DrawingDrawRectangle
// Draws a solid or nonsolid rectangle
//=============================
void __fastcall DrawingDrawRectangle(int x, int y, int w, int h, bool solid)
{
	if(!solid)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_QUADS);

	glVertex2i(x-w/2, y-h/2);
	glVertex2i(x+w/2+1, y-h/2);
	glVertex2i(x+w/2, y+h/2);
	glVertex2i(x-w/2, y+h/2);

	glEnd();
}

//=============================
// DrawingDrawLine
// Draws a line from A to B
//=============================
void __fastcall DrawingDrawLine(int xs, int ys, int xe, int ye)
{
	glBegin(GL_LINES);
	glVertex2i(xs, ys);
	glVertex2i(xe, ye);
	glEnd();
}

//=============================
// DrawingDrawCircle
// Draws a circle with given radius
//=============================
/*void __fastcall DrawingDrawCircle(int x, int y, int r, bool solid)
{
	float vectorX, vectorY1 = (float)y + r;
	float vectorY, vectorX1 = (float)x;
	glBegin(GL_LINE_STRIP);	
	for(float angle = 0.0f; angle <= (2.0f*3.14159); angle += 0.01f)
	{		
		vectorX = (float)x + (float)r * sin(angle);
		vectorY = (float)y + (float)r * cos(angle);		
		glVertex2f(vectorX1, vectorY1);
		vectorY1 = vectorY;
		vectorX1 = vectorX;			
	}
	glEnd();
}*/

void __fastcall DrawingDrawCircle(int x, int y, int radius) {
	#define PI 3.1415926
	glLineWidth(1.0f); 
	glBegin(GL_POLYGON); 
	glVertex2i(x+radius, y); //freebies
	glVertex2i(x-radius, y);
	glVertex2i(x, y+radius);
	glVertex2i(x, y-radius);
	float xmod, ymod, step = PI / (4*radius); //don't compute much more than is necessary for a solid circle
	for(float theta = 0; theta <= PI/2; theta += step)
	{
		xmod = (cos(theta) * radius);
		ymod = (sin(theta) * radius);
		glVertex2f(x + xmod, y + ymod); //create solids by vertices
		glVertex2f(x + xmod, y - ymod); //and using glpolygon for filling
		glVertex2f(x - xmod, y + ymod); 
		glVertex2f(x - xmod, y - ymod);
	} 
	glEnd(); 
}

//================================================================
// DrawingDrawText
// Draws a text to the screen
// Very bad performance quality. You should better write your own.
//================================================================
void DrawingDrawText(char* Text, int x, int y, int r, int g, int b, int a, char* FontName, int w, int h, bool Centered)
{
	HDC hDC = wglGetCurrentDC();
	GLuint Lists = glGenLists(256);
	wglUseFontBitmaps(hDC, 0, 256, Lists);

	HFONT hFont = CreateFont(w, 0, 0, 0, h, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, FontName);
	HFONT hOldFont = (HFONT) SelectObject(hDC, hFont);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	SIZE s;
	char Sizes[256];
	for(int i=0; i < 256; i++)
	{
		char temp[2] = {i, '\0'};
		GetTextExtentPoint32(hDC, temp, 1, &s);
		Sizes[i] = (char)s.cx;
	}

	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);

	GLfloat curcolor[4], position[4];
	glPushAttrib(GL_LIST_BIT);
	glGetFloatv(GL_CURRENT_COLOR, curcolor);
	glGetFloatv(GL_CURRENT_RASTER_POSITION, position);
	glDisable(GL_TEXTURE_2D);

	glColor4ub(r, g, b, a);
	glRasterPos2i(x, y);

	glListBase(Lists);
	glCallLists(strlen(Text), GL_UNSIGNED_BYTE, Text);

	glPopAttrib();
	glColor4fv(curcolor);
	glRasterPos2f(position[0],position[1]);
	glEnable(GL_TEXTURE_2D);

	glDeleteLists(Lists, 256);
}

#include <stdarg.h>
#include <stdio.h>
#include "SDKInclude.h"
#include "client.h"
void DrawConString (int x, int y, int r, int g, int b, const char *fmt, ... )
{
	va_list va_alist;
	char buf[256];
	
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	
	int length, height;
	
	y += 4;
	gEngfuncs.pfnDrawConsoleStringLen( buf, &length, &height );
	gEngfuncs.pfnDrawSetTextColor(r/255.0f, g/255.0f, b/255.0f);
	gEngfuncs.pfnDrawConsoleString(x,y,buf);
}