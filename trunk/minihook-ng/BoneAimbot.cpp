#include "BoneAimbot.h"

BoneAimbot gAimbot;

#define NUM_AIMSPOTS 6

int aimspot1[] = {BONE_NECK, BONE_LOWERNECK, BONE_HEAD, 
						BONE_UPPERTORSO, BONE_MIDTORSO, BONE_LOWERTORSO, 
						BONE_INVALID};//, 10, 25, 11, 26, 21, 36, 43, 49, -1};
int aimspot2[] = {BONE_UPPERTORSO, BONE_MIDTORSO, BONE_LOWERTORSO, 
						BONE_NECK, BONE_LOWERNECK, BONE_HEAD, 
						BONE_INVALID};
int aimspot3[] = {BONE_MIDTORSO, BONE_LOWERTORSO, BONE_LEFTPELVIS, 
						BONE_RIGHTPELVIS, BONE_LEFTKNEE, BONE_RIGHTKNEE, 
						BONE_INVALID};
int aimspot4[] = {BONE_LEFTPELVIS, BONE_RIGHTPELVIS, BONE_LEFTKNEE, 
						BONE_RIGHTKNEE, BONE_LEFTANKLE, BONE_RIGHTANKLE,
						BONE_INVALID};
						 

bool BoneAimbot::TargetSpot(float* eyePos, PlayerInfo& target, float* targetSpot)
{
	int* bonesToTry;

	switch((int)cvar.aimspot) {
		default:
		case 0:
			bonesToTry = aimspot1;
			break;

		case 1:
			bonesToTry = aimspot2;
			break;

		case 2:
			bonesToTry = aimspot3;
			break;

		case 3:
			bonesToTry = aimspot4;
			break;
	}

	int bx = 0;

	if(target.gotbones && ((target.numTargetSpots+1) > NUM_AIMSPOTS))
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

