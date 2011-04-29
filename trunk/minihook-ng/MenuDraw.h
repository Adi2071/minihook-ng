#pragma once
#include "MenuElem.h"

#define MENUELEM_WIDTH 165
#define MENUELEM_HEIGHT 18

typedef struct _MenuColor {
	int r;
	int g;
	int b;
	int a;
}MenuColor;

class CMenuDraw
{
public:
	static void Draw(CMenuElem& rMenu, int x, int y);

private:
	static void DrawElement(CMenuElem& rElem, int x, int y, MenuColor& BorderColor, MenuColor& FillColor, MenuColor& TextColor, bool CenterText);
	static void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a, bool fill);
	static void __cdecl DrawStringDimensions(int* length, int* height, char* format, ...);
	static void __cdecl  DrawString(int x, int y, int r, int g, int b, int a, char* format, ...);
};

