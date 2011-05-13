#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

void hpattack2(void) {
	int curWeapon = GetCurWeaponId();
	if(cvar.zoomall && IsCurWeaponGun() && curWeapon != WEAPONLIST_AWP && curWeapon != WEAPONLIST_SCOUT && curWeapon != WEAPONLIST_SG550 && curWeapon != WEAPONLIST_G3SG1) {
		if(*pFOV == 90.0f) {
			*pFOV = 40.0f;
		}
		else if(*pFOV == 40.0f) {
			*pFOV = 15.0f;
		}
		else if(*pFOV == 15.0f) {
			*pFOV = 90.0f;
		}
		return;
	}
	else {
		ppattack2();
	}
}

void hpreload(void) {

	if(cvar.zoomall && *pFOV != 90.0f) {
		*pFOV = 90.0f;
	}
	ppreload();
}

pfnCommand ppattack2;
pfnCommand ppreload;
