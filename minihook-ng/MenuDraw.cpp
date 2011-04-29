#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>

#include "SDKInclude.h"
#include "TransInclude.h"
#include "MenuDraw.h"
#include "Drawing.h"

MenuColor TitleBorder = {0, 255, 0, 191};
MenuColor TitleFill = {0, 255, 0, 127};
MenuColor TitleText = {255, 0, 255, 255};

MenuColor ElemBorder = {0, 255, 0, 191};
MenuColor ElemFill = {0, 0, 255, 191};
MenuColor ElemFillSelected = {0, 0, 255, 127};
MenuColor ElemText = {255, 255, 0, 255};

void CMenuDraw::Draw(CMenuElem& rMenu, int x, int y) {
	int curY = y;

	DrawElement(rMenu, x, curY, TitleBorder, TitleFill, TitleText, true);
	curY += MENUELEM_HEIGHT;

	for(int i = 0; i < rMenu.vElems.size(); i++, curY += MENUELEM_HEIGHT) {
		DrawElement(rMenu.vElems.at(i), x, curY, ElemBorder, ElemFill, ElemText, false);
	}
}

void CMenuDraw::DrawElement(CMenuElem& rElem, int x, int y, MenuColor& BorderColor, MenuColor& FillColor, MenuColor& TextColor, bool CenterText) {
	int length, width;
	int textX = 0;
	char* ElemPrefix = " ";
	char* ElemPostfix = "";

	DrawRect(x, y-1, MENUELEM_WIDTH-1, MENUELEM_HEIGHT, FillColor.r, FillColor.g, FillColor.b, FillColor.a, true);
	DrawRect(x, y, MENUELEM_WIDTH, MENUELEM_HEIGHT, BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a, false);	

	if(rElem.ElemType == ELEM_SUBMENU) {
		ElemPostfix = " ->";
	}
	else if(rElem.ElemType == ELEM_CALLBACK) {
		ElemPostfix = "*";
	}

	CMenuDraw::DrawStringDimensions(&length, &width, "%s%s%s", ElemPrefix, rElem.sDisplayText.c_str(), ElemPostfix);
	if(CenterText) {
		textX = x - length/2;
	} else {
		textX = x - MENUELEM_WIDTH/2;
	}

	CMenuDraw::DrawString(textX, y - width, TextColor.r, TextColor.g, TextColor.b, TextColor.a, "%s%s%s", ElemPrefix, rElem.sDisplayText.c_str(), ElemPostfix);
}

void CMenuDraw::DrawRect(int x, int y, int w, int h, int r, int g, int b, int a, bool fill) {
	DrawingBegin();

	DrawingSetColor(r, g, b, a);
	DrawingDrawRectangle(x, y, w, h, fill);

	DrawingEnd();
}

void __cdecl CMenuDraw::DrawString(int x, int y, int r, int g, int b, int a, char* format, ...) {
	va_list va_alist;
	char buf[256];
	
	va_start (va_alist, format);
	_vsnprintf (buf, sizeof(buf), format, va_alist);
	va_end (va_alist);

	DrawConString(x, y, r, g, b, "%s", buf);
}

void __cdecl CMenuDraw::DrawStringDimensions(int* length, int* height, char* format, ...) {
	va_list va_alist;
	char buf[256];
	
	va_start (va_alist, format);
	_vsnprintf (buf, sizeof(buf), format, va_alist);
	va_end (va_alist);

	gEngfuncs.pfnDrawConsoleStringLen( buf, length, height );
}

