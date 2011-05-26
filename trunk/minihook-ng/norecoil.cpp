#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

extern cvar_t* recoilVar1;
extern cvar_t* recoilVar2;

float GetRecoilVar() {
	int iID = GetCurWeaponID();
	float recoil = 0.0f;

	switch(iID) {
		case WEAPONLIST_USP:
			recoil = 1.0f;
			break;
		case WEAPONLIST_GLOCK18:
			recoil = 1.0f;
			break;
		case WEAPONLIST_DEAGLE:
			recoil = 0.2f;
			break;
		case WEAPONLIST_P228:
			recoil = 1.0f;
			break;
		case WEAPONLIST_ELITE:
			recoil = 1.2f;
			break;
		case WEAPONLIST_FIVESEVEN:
			recoil = 1.0f;
			break;
		case WEAPONLIST_M4A1:
			recoil = 1.73f;
			break;
		case WEAPONLIST_AK47:
			recoil = 1.73f;
			break;
		case WEAPONLIST_AUG:
			recoil = 1.6f;
			break;
		case WEAPONLIST_SG552:
			recoil = 1.74f;
			break;
		case WEAPONLIST_M249:
			recoil = 1.85f;
			break;
		case WEAPONLIST_UMP45:
			recoil = 1.1f;
			break;
		case WEAPONLIST_MP5:
			recoil = 1.2f;
			break;
		case WEAPONLIST_TMP:
			recoil = 0.8f;
			break;
		case WEAPONLIST_MAC10:
			recoil = 1.58f;
			break;
		case WEAPONLIST_P90:
			recoil = 1.6f;
			break;
		default:
			recoil = 1.0f;
			break;
	}

	return recoil;
}

void ApplyNorecoil(float *punchangle, float *outAngles)
{
	/*Vector punch;
    float length;
    VectorCopy(punchangle, punch);

    length = punch.Length();
	punch = punch.Normalize();

	GetRecoilVars();

    length -= (recvar1*me.spread.recoil + length*recvar2);// * 0.01f;
    length = max(length, 0.0);
    punch = punch * length;
    outAngles[0] = punch[0];
    outAngles[1] = punch[1];
	*/

	float recoilVar = GetRecoilVar();
	outAngles[0] = punchangle[0] * recoilVar;
	outAngles[1] = punchangle[1] * recoilVar;
}
