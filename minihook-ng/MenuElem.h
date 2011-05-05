#pragma once

#include <string>
#include <vector>

#define GLOBALMENU_TITLE "minihook-ng"

enum ELEM_TYPE {
	ELEM_BASEMENU = 0,
	ELEM_SUBMENU,
	ELEM_VALUE,			// pExtra is set to pointer to float value
	ELEM_CALLBACK
};

typedef void (*tMenuCallback)(void);

class CMenuDraw;
class CMenuControl;
class CMenuElem
{
	friend class CMenuDraw;
	friend class CMenuControl;
public:
	CMenuElem(std::string sText, enum ELEM_TYPE eType, void* pExtra);

	void AddElement(CMenuElem rElem);

	float SetMinimumValue(float fMin);
	float SetMaximumValue(float fMax);

	void Initialize();
		
private:
	// general variables common to all types
	enum ELEM_TYPE ElemType;
	std::string sDisplayText;				// What gets displayed in the menu, or title for menus

	//for menus
	int iMenuIndex;							// Index of selected menu element
	std::vector<class CMenuElem> vElems;	// Vector list of all elements
	class CMenuElem* pPrevMenu;				// Pointer to previous menu if this is a submenu
	// for base menus
public:
	bool bShow;
private:
	class CMenuElem* pCurMenu;				// Current menu

	// for values
	float fMinimumValue;					// Minimum possible value
	float fMaximumValue;					// Maximum possible value
	float *pfCurrentValue;					// Pointer to display value

	// for callbacks
	tMenuCallback pCallbackFunction;

};

extern CMenuElem gMenu;