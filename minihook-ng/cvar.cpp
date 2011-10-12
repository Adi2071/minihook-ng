#include "cvar.h"

#include <cstdio>
#include <cstring>
#include "MenuElem.h"

struct hookcvar_s cvar;
struct hookcvar_s panicvars;
struct debugvar_s dvar;

bool inPanic = false;
bool panicMenuShow = false;
void togglePanic() {
	if(!inPanic) {
		memcpy(&panicvars, &cvar, sizeof(struct hookcvar_s));
		memset(&cvar, 0, sizeof(struct hookcvar_s));
		panicMenuShow = gMenu.bShow;
		gMenu.bShow = false;
		inPanic = true;
	}
	else {
		memcpy(&cvar, &panicvars, sizeof(struct hookcvar_s));
		gMenu.bShow = panicMenuShow;
		inPanic = false;
	}
}
