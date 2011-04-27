#include <windows.h>
#include "SDKInclude.h"
#include "Calculations.h"

float vieworg[3];		// Copy in V_CalcRefdef
float viewangles[3];	// Copy in V_CalcRefdef
float FOV = 90.0f;		// Copy in UserMsg: SetFoc; Default: 90

float VectorLength(float* Vector)
{
	return (float)sqrt(DotProduct(Vector, Vector));
}

float AngleOfVectors(float* Vector1, float*Vector2)
{
	float Length = VectorLength(Vector1) * VectorLength(Vector2);
	if(Length == 0.0f)
		return Length;

	return acos(DotProduct(Vector1, Vector2)/Length*(180.0f/M_PI));
}

void inline AngleToVector(float *Angle, float* Vector)
{
	float pitch = Angle[PITCH] * M_PI/180.0f;
	float yaw = Angle[YAW] * M_PI/180.0f;

	Vector[0] = -cos(pitch) * -cos(yaw);
	Vector[1] =  sin(yaw) * cos(pitch);
	Vector[2] = -sin(pitch);
}

void inline VectorToAngle(float *Vector, float* Angle)
{
	float temp = sqrt (Vector[0]*Vector[0] + Vector[1]*Vector[1]);
	Angle[YAW] = atan2(Vector[1], Vector[0]) * 180.0f / M_PI;
	Angle[PITCH] = atan2(Vector[2], temp) * 180.0f / M_PI;

	if(Vector[0] == Vector[1] && Vector[0] == 0.0f)
		Angle[YAW] = 0.0f;

	if(Angle[YAW] < 0)
		Angle[YAW] += 360.0f;

	Angle[ROLL] = 0.0f;
}

void inline RotateAxisZ(float *Vector, float alpha, float* NewVector)
{
	float Matrix[3][3] = 
	{
		{ cos(alpha), -sin(alpha), 0 },
		{ sin(alpha),  cos(alpha), 0 },
		{ 0         ,  0         , 1 }
	};
	for(int i=0; i<3; i++)
		NewVector[i] = Vector[0]*Matrix[i][0] + Vector[1]*Matrix[i][1] + Vector[2]*Matrix[i][2];
}

void inline RotateAxisY(float *Vector, float beta, float* NewVector)
{
	float Matrix[3][3] = 
	{
		{  cos(beta),  0,  sin(beta) },
		{  0        ,  1,  0         },
		{ -sin(beta),  0,  cos(beta) }
	};
	for(int i=0; i<3; i++)
		NewVector[i] = Vector[0]*Matrix[i][0] + Vector[1]*Matrix[i][1] + Vector[2]*Matrix[i][2];
}

void inline RotateAxisX(float *Vector, float gamma, float* NewVector)
{
	float Matrix[3][3] = 
	{
		{  1,  0         ,  0            },
		{  0,  cos(gamma),  -sin(gamma)  },
		{  0,  sin(gamma),   cos(gamma)  }
	};
	for(int i=0; i<3; i++)
		NewVector[i] = Vector[0]*Matrix[i][0] + Vector[1]*Matrix[i][1] + Vector[2]*Matrix[i][2];
}

void inline RotateAxes(float *Vector, float* Angles, float* NewVector)
{
	float Temp[3];
	RotateAxisZ(Vector, -(Angles[YAW] * M_PI/180), NewVector);
	RotateAxisY(NewVector, -(Angles[PITCH] * M_PI/180), Temp);
	RotateAxisX(Temp, -(Angles[ROLL] * M_PI/180), NewVector);
}

int __fastcall WorldToScreen(float* World, float* Screen)
{
	SCREENINFO Screeninfo;
	float Temp[3], Camera[3], viewvector[3];

	if(!World || !Screen)
		return FALSE;
	
	Screeninfo.iSize = sizeof(SCREENINFO);
	gEngfuncs.pfnGetScreenInfo(&Screeninfo);

	VectorSubtract(World, vieworg, Temp);

	AngleToVector(viewangles, viewvector);
	if(AngleOfVectors(viewvector, Temp) > FOV/1.8f)
		return FALSE;

	RotateAxes(Temp, viewangles, Camera);
	if(Camera[0] <= 0.0f)
		return FALSE;

	float num = ((320.0f/Camera[0]) * (120.0f/FOV - 1.0f/3.0f));

	Screen[0] = 320.0f - num * Camera[1];
	Screen[1] = 240.0f - num * Camera[2];

	#define BOUND_VALUE(var, min, max) if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}
	BOUND_VALUE(Screen[0], 0, Screeninfo.iWidth);
	BOUND_VALUE(Screen[1], 0, Screeninfo.iHeight);

	return TRUE;
}