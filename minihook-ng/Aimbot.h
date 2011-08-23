#ifndef _ACID_AIMBOT_
#define _ACID_AIMBOT_

#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"
using namespace std;

class aimvec
{
public:
	float h;
	float f;
	float r;
};

class OriginAimbot
{
public:
	void FindTarget(void);
	int target;
	vec3_t targetAngles;

protected:
	virtual bool TargetSpot(float* eyePos, PlayerInfo& target, float* targetSpot);

	int CanPenetrate( float *start, float *end );
	void VectorAngles(const float *forward, float *angles);
	float Degree(float radian);
	void MakeDelta(float *src, float *dst, float *vec);
	void MakeAngle(float *vec, float *angle);
	bool isValidEnt(cl_entity_s *ent);
	inline float VectorLength(float* v);
	inline float VectorPseudo(float* v);
	inline void VectorScale(const float* in, float scale, float* out);
	static void PredictTarget(int index,float *pred);
};

#endif