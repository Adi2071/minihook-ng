#pragma once
#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"

#include "client.h"

class CAimbot {
public:
	CAimbot(void);
	~CAimbot(void);

	void scanPlayers(void);
	vec3_t aimAngles(void);

private:
	PlayerInfo* findTarget();

	PlayerInfo* m_target;
	vec3_t m_targetSpot;
};

