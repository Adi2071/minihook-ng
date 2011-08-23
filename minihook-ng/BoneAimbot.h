#pragma once
#include "aimbot.h"
class BoneAimbot :
	public OriginAimbot
{
public:
	bool TargetSpot(float* eyePos, PlayerInfo& target, float* targetSpot);
};

extern BoneAimbot gAimbot;
