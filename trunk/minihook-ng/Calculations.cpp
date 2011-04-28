#include <windows.h>
#include "SDKInclude.h"
#include "Calculations.h"
#include "client.h"

float *vieworg = me.pmEyePos;		// Copy in V_CalcRefdef
float *viewangles = me.viewAngles;	// Copy in V_CalcRefdef
float FOV = 90.0f;		// Copy in UserMsg: SetFoc; Default: 90

int m_iCenterX, m_iCenterY;

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

int __fastcall CalcScreen(const float *origin, float *vecScreen)
{
	int result = gEngfuncs.pTriAPI->WorldToScreen( const_cast<float*>(origin),vecScreen);
	
	if(vecScreen[0] < 1 && vecScreen[1] < 1 && vecScreen[0] > -1 && vecScreen[1] > -1 && !result)
	{
		vecScreen[0] =  vecScreen[0] * m_iCenterX + m_iCenterX;
		vecScreen[1] = -vecScreen[1] * m_iCenterY + m_iCenterY;
		return true;
	}
	return false;
}