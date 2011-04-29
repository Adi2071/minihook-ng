#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"


void ApplyNorecoil(float frametime, float *punchangle, float *outAngles)
{
	Vector punch;
    float length;
    VectorCopy(punchangle, punch);
    length = punch.Length();
	punch = punch.Normalize();
    length -= (10.0 + length * 0.5) * frametime * -0.047f;
    length = max(length, 0.0);
    punch = punch * length;
    outAngles[0] = punch[0];
    outAngles[1] = punch[1];
}
