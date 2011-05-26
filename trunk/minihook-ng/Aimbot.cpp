#include "Aimbot.h"

int aimSpotPrefs[] = {8, 7, 6, 5, 4, 3, 2, 1, 41, 40, 10, 25, 11, 26, 18, 34, 43, 49, 45, 51};

CAimbot::CAimbot(void) {
}


CAimbot::~CAimbot(void) {
}

void CAimbot::scanPlayers(void) {
	m_target = findTarget();
}

vec3_t CAimbot::aimAngles(void) {
	return vec3_t(0,0,0);
}

PlayerInfo* CAimbot::findTarget() {
	m_target = NULL;
	VectorClear(m_targetSpot);

	return NULL;
}
