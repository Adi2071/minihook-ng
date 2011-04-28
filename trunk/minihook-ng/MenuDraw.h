#pragma once
#include "MenuElem.h"

class CMenuDraw
{
public:
	static void Draw(CMenuElem& rMenu, int x, int y);

private:
	static void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a, bool fill);
	static void DrawText(int x, int y, int r, int g, int b, int a, char* format, ...);
};

