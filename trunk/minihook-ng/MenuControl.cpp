#include <Windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "MenuControl.h"
#include "MenuElem.h"
#include "util.h"

int CMenuControl::HUD_Key_Event(int down, int keynum, const char *pszCurrentBinding) {
	CMenuElem* pCurMenu = gMenu.pCurMenu;
	if(!pCurMenu)
		return 1;

	CMenuElem& rCurMenuElem = pCurMenu->vElems.at(pCurMenu->iMenuIndex);

	if(keynum == K_INS && down) {
		gMenu.bShow = !gMenu.bShow;
		return 0;
	}

	if(gMenu.bShow && down) {
		switch(keynum) {
			case K_UPARROW:
			case K_MWHEELUP:
			{
				if(pCurMenu->iMenuIndex > 0) {
					pCurMenu->iMenuIndex--;
				}
				return 0;
			}

			case K_DOWNARROW:
			case K_MWHEELDOWN:
			{
				if(pCurMenu->iMenuIndex < pCurMenu->vElems.size()-1) {
					pCurMenu->iMenuIndex++;
				}
				return 0;
			}

			case K_MOUSE3:
			{
				if(rCurMenuElem.ElemType == ELEM_VALUE)
				{
					*rCurMenuElem.pfCurrentValue = 0.0f;
				}
				return 0;
			}

			case K_LEFTARROW:
			case K_MOUSE2:
			{
				gMenu.pCurMenu = pCurMenu->pPrevMenu;
				return 0;
			}

			case K_RIGHTARROW:
			case K_MOUSE1:
			{
				if(rCurMenuElem.ElemType == ELEM_VALUE) {
					if(++(*rCurMenuElem.pfCurrentValue) > rCurMenuElem.fMaximumValue) {
						*rCurMenuElem.pfCurrentValue = rCurMenuElem.fMinimumValue;
					}
				}
				else if(rCurMenuElem.ElemType == ELEM_SUBMENU) {
					gMenu.pCurMenu = &rCurMenuElem;
				}
				return 0;
			}
		}
	}

	return 1;
}


