//=================================================================================//
//		GSAim Class by hYsteRia aka h1web										   //
//			-Credits to Patrick, Amir, the Game-Deception people					   //
//			-Greets to boecke, sinister, whole Game-Deception Team, ...			   //
//		If you make a public Hook with this, I expect you to credit me !		   //
//																				   //
//		NOTE: Modified by mre521, the author of this hack. Wanted a quick		   //
//			  aimbot base. Left the credits here for good measure.				   //
//=================================================================================//

//#include "players.h"
#include "aimbot.h"
#include "perfectwall.h"

//===================================================================================
#define M_PI		3.14159265358979323846

//===================================================================================
float OriginAimbot::Degree(float radian) 
{ 
    return radian * (180/M_PI); 
} 
//===================================================================================
void OriginAimbot::MakeDelta(float *src, float *dst, float *vec) 
{ 
    vec[0] = src[0] - dst[0]; 
    vec[1] = src[1] - dst[1]; 
    vec[2] = src[2] - dst[2]; 
} 
//===================================================================================
void OriginAimbot::MakeAngle(float *vec, float *angle) 
{ 
    float hyp = sqrt(vec[0]*vec[0] + vec[1]*vec[1]); 
    angle[0] = Degree(atan(vec[2]/hyp)); 
    angle[2] = 0.0f; 
    if(vec[0] >= 0) 
    { 
        if(vec[1] >= 0)        {    angle[1] = Degree(atan(fabs(vec[1]/vec[0]))) + 180;    } 
        else                {    angle[1] = Degree(atan(fabs(vec[0]/vec[1]))) + 90;    } 
    } 
    else 
    { 
        if(vec[1] >= 0)        {    angle[1] = Degree(atan(fabs(vec[0]/vec[1]))) + 270;    } 
        else                {    angle[1] = Degree(atan(fabs(vec[1]/vec[0])));        } 
    } 
} 
//===================================================================================
bool OriginAimbot::isValidEnt(cl_entity_s *ent) // Credits to Tetsuo
{
 if(ent && (ent != pEngfuncs->GetLocalPlayer()) && !(ent->curstate.effects & EF_NODRAW) && ent->player && !ent->curstate.spectator && ent->curstate.solid && !(ent->curstate.messagenum < pEngfuncs->GetLocalPlayer()->curstate.messagenum)) 
 {
 return true;

 }
 else 
 {
 return false;
 }
}
//===================================================================================
void OriginAimbot::PredictTarget(int index,float *pred)
{
	float predahead = cvar.predahead; // Some default Values ;D
	int predback = 0;
			cl_entity_s* ent = pEngfuncs->GetEntityByIndex(index);
			
			float latency;
			net_status_s net;
			//int  historyIndex = (ent->current_position+HISTORY_MAX-predback)%HISTORY_MAX;
			
			vec3_t vFromOrigin , vToOrigin , vDeltaOrigin,vPredictedOrigin;
			//vFromOrigin = //ent->ph[historyIndex].origin;
			//vToOrigin   = //ent->ph[ent->current_position].origin;
			vDeltaOrigin = vPlayers[index].velocity() + vPlayers[index].acceleration() - (vPlayers[me.entindex].velocity() + vPlayers[me.entindex].acceleration());//vToOrigin - vFromOrigin;

			gEngfuncs.pNetAPI->Status(&net);
			latency = net.latency;
			if( latency > 1.0f )
			{
				predahead *= (latency / 1000.0f) + me.frametime;
			}

			vDeltaOrigin[0] *= predahead;
			vDeltaOrigin[1] *= predahead;
			vDeltaOrigin[2] *= predahead;

			vPredictedOrigin = vDeltaOrigin;

			VectorCopy(vPredictedOrigin,pred);
}
//===================================================================================
inline float OriginAimbot::VectorLength(float* v)
{
	return /*(float)*/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}
inline float OriginAimbot::VectorPseudo(float* v)
{
	return /*(float)*/(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}
inline void OriginAimbot::VectorScale(const float* in, float scale, float* out)
{
	out[0] = in[0] * scale;
	out[1] = in[1] * scale;
	out[2] = in[2] * scale;
}
//===================================================================================
int OriginAimbot::CanPenetrate( float *start, float *end ) // Perfectwall wrapper - Credit Snipity
{
	if(!me.weapon)
	{
		return 0;
	}

	int bulletType = playerItems.CurBulletType();
	int damage = playerItems.CurDamage();
	float distance = playerItems.CurDistance();
	int penetration = playerItems.CurPenetration();
	float wallPierce = playerItems.CurWallPierce();

	if(wallPierce == 0.0f)
	{
		pmtrace_t tr;
		gEngfuncs.pEventAPI->EV_SetTraceHull(2);
		gEngfuncs.pEventAPI->EV_PlayerTrace(start, end, PM_GLASS_IGNORE, -1, &tr);

		if(gEngfuncs.pEventAPI->EV_IndexFromTrace(&tr) == 0) // world/wall
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	
	return ::CanPenetrate(start, end, distance, penetration, bulletType, damage, wallPierce);
}

bool OriginAimbot::TargetSpot(float* eyePos, PlayerInfo& target, float* targetSpot)
{
	VectorCopy(target.origin(), targetSpot); 
	return CanPenetrate(eyePos, targetSpot);
}
//===================================================================================
void OriginAimbot::VectorAngles(const float *forward, float *angles)
{
	float tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 90.0;
		else
			pitch = 270.0;
	}
	else
		yaw = (atan2(forward[1], forward[0]) * 180.0 / M_PI);

	if (yaw < 0) yaw += 360.0;
		tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
		
	pitch = (atan2(forward[2], tmp) * 180.0 / M_PI);

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
//===================================================================================
void OriginAimbot::FindTarget(void) // Lets do it, common !
{
	float aimVector[3];

	target = BAD_TARGET;
	VectorClear(targetAngles);
	int ax = 0;

	vTargets.SortTargets();
	int nTargets = vTargets.size();

	if(!nTargets) { return; }

	for(int tx=0; tx<nTargets; tx++)
	{
		cl_entity_s * ent;
		float oaim[3];
		float vecScreen[3];
		float angle[3];
		float targetSpot[3];
		float velocity[3];
		
		ax = vTargets[tx];
		if(ax == BAD_TARGET) { break; }

		ent = pEngfuncs->GetEntityByIndex(ax);

		if(!TargetSpot(me.pmEyePos, vPlayers[ax], targetSpot))
		{
			continue;
		}

		float playerAngles[3], out[3], forward[3], up[3], right[3], view[3];
		PredictTarget(ax, oaim);
		VectorAdd(oaim, targetSpot, oaim);
	
		playerAngles[0]=0;
		playerAngles[1]=ent->angles[1];
		playerAngles[2]=0;
		gEngfuncs.pfnAngleVectors (playerAngles, forward, right, up);
		VectorCopy(oaim, out);
		out[0] = out[0] + forward[0] + up[0] + right[0];
		out[1] = out[1] + forward[1] + up[1] + right[1];
		out[2] = out[2] + forward[2] + up[2] + right[2];

		MakeDelta(me.pmEyePos, out, aimVector);
				
		target = ax;
		break;
	}

	if(target != BAD_TARGET)
	{
		MakeAngle(aimVector, targetAngles);
	}
}
//===================================================================================