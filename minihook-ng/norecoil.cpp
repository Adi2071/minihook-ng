#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

extern cvar_t* recoilVar1;
extern cvar_t* recoilVar2;

void ApplyNorecoil(float frametime, float *punchangle, float *outAngles)
{
	Vector punch;
    float length;
    VectorCopy(punchangle, punch);

    length = punch.Length();
	punch = punch.Normalize();

    length -= (recoilVar1->value + length * recoilVar2->value) * frametime;
    length = max(length, 0.0);
    punch = punch * length;
    outAngles[0] = punch[0];
    outAngles[1] = punch[1];
}
