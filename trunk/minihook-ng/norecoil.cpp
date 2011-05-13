#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

extern cvar_t* recoilVar1;
extern cvar_t* recoilVar2;

float recvar1 = 0, recvar2;

void GetRecoilVars() {
	int iID = GetCurWeaponID();

	switch(iID) {
		case WEAPONLIST_USP:
			recvar1 = -1000.0f;
			recvar2 = -70.0f;
			break;
		case WEAPONLIST_GLOCK18:
			recvar1 = 0.0f;
			recvar2 = 0.0f;
			break;
		case WEAPONLIST_DEAGLE:
			recvar1 = 0.0f;
			recvar2 = 0.0f;
			break;
		case WEAPONLIST_P228:
			recvar1 = -3.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_ELITE:
			recvar1 = 0.0f;
			recvar2 = -68;
			break;
		case WEAPONLIST_FIVESEVEN:
			recvar1 = 0.0f;
			recvar2 = -20.0f;
			break;
		case WEAPONLIST_M4A1:
			recvar1 = -3.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_AK47:
			recvar1 = -5.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_AUG:
			recvar1 = -2.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_SG552:
			recvar1 = -1.0f;
			recvar2 = -58.0f;
			break;
		case WEAPONLIST_M249:
			recvar1 = -6.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_UMP45:
			recvar1 = 0.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_MP5:
			recvar1 = -2.0f;
			recvar2 = -60.0f;
			break;
		case WEAPONLIST_TMP:
			recvar1 = 0.5f;
			recvar2 = -65.0f;
			break;
		case WEAPONLIST_MAC10:
			recvar1 = 0.0f;
			recvar2 = -65.0f;
			break;
		case WEAPONLIST_P90:
			recvar1 = 0.0f;
			recvar2 = -60.0f;
			break;
		default:
			recvar1 = 0.0f;
			recvar2 = 0.0f;
			break;
	}
}

void ApplyNorecoil(float frametime, float *punchangle, float *outAngles)
{
	Vector punch;
    float length;
    VectorCopy(punchangle, punch);

    length = punch.Length();
	punch = punch.Normalize();

	GetRecoilVars();

    length -= (recvar1*me.spread.recoil + length*recvar2) * 0.011f;//frametime;
    length = max(length, 0.0);
    punch = punch * length;
    outAngles[0] = punch[0];
    outAngles[1] = punch[1];
}
