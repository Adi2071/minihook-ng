#include "MenuDraw.h"
#include "Drawing.h"

void CMenuDraw::Draw(CMenuElem& rMenu, int x, int y) {
	CMenuDraw::DrawRect(x, y, 100, 100, 0, 255, 0, 127, true);
}

void CMenuDraw::DrawRect(int x, int y, int w, int h, int r, int g, int b, int a, bool fill) {
	DrawingBegin();

	DrawingSetColor(r, g, b, a);
	DrawingDrawRectangle(x, y, w, h, fill);

	DrawingEnd();
}
void CMenuDraw::DrawText(int x, int y, int r, int g, int b, int a, char* format, ...) {

}

