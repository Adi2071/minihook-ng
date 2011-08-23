#include "BoneAimbot.h"

BoneAimbot gAimbot;

bool BoneAimbot::TargetSpot(float* eyePos, PlayerInfo& target, float* targetSpot)
{
	int bonesToTry[] = {BONE_NECK, BONE_LOWERNECK, BONE_HEAD, 
						BONE_UPPERTORSO, BONE_MIDTORSO, BONE_LOWERTORSO, 
						BONE_INVALID};//, 10, 25, 11, 26, 21, 36, 43, 49, -1};
	int bx = 0;

	if(target.gotbones && ((target.numTargetSpots+1) > (sizeof(bonesToTry)/sizeof(bonesToTry[0]))))
	{
		while( (bonesToTry[bx] != BONE_INVALID) )
		{
			Vector& vTargetSpot = target.TargetSpots[bonesToTry[bx]];
			if(CanPenetrate(eyePos, vTargetSpot))
			{
				VectorCopy(vTargetSpot, targetSpot);
				return true;
			}

			bx++;
		}
	}
	else
	{
		Vector& org = target.origin();
		if(CanPenetrate(eyePos, org))
		{
			VectorCopy(org, targetSpot);
			return true;
		}
	}

	return false;
}

