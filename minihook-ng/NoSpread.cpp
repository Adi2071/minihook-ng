//
#include <windows.h>
#include "nospread.h"
#include "SDKInclude.h"
#include "TransInclude.h"
#include "client.h"

#define WEAPONLIST_GALIL 14
#define WEAPONLIST_FAMAS 15

cNoSpread gNoSpread;
float testspread = 1.0f;

// helper functions:
inline float VectorLength(const float *v)
{
	return (float)sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

// An unmanaged array of seeds for nospread
unsigned int seed_table[ 256 ] =
{
	28985, 27138, 26457, 9451, 17764, 10909, 28790, 8716, 6361, 4853, 17798, 21977, 19643, 20662, 10834, 20103,
	27067, 28634, 18623, 25849, 8576, 26234, 23887, 18228, 32587, 4836, 3306, 1811, 3035, 24559, 18399, 315,
	26766, 907, 24102, 12370, 9674, 2972, 10472, 16492, 22683, 11529, 27968, 30406, 13213, 2319, 23620, 16823,
	10013, 23772, 21567, 1251, 19579, 20313, 18241, 30130, 8402, 20807, 27354, 7169, 21211, 17293, 5410, 19223,
	10255, 22480, 27388, 9946, 15628, 24389, 17308, 2370, 9530, 31683, 25927, 23567, 11694, 26397, 32602, 15031,
	18255, 17582, 1422, 28835, 23607, 12597, 20602, 10138, 5212, 1252, 10074, 23166, 19823, 31667, 5902, 24630,
	18948, 14330, 14950, 8939, 23540, 21311, 22428, 22391, 3583, 29004, 30498, 18714, 4278, 2437, 22430, 3439,
	28313, 23161, 25396, 13471, 19324, 15287, 2563, 18901, 13103, 16867, 9714, 14322, 15197, 26889, 19372, 26241,
	31925, 14640, 11497, 8941, 10056, 6451, 28656, 10737, 13874, 17356, 8281, 25937, 1661, 4850, 7448, 12744,
	21826, 5477, 10167, 16705, 26897, 8839, 30947, 27978, 27283, 24685, 32298, 3525, 12398, 28726, 9475, 10208,
	617, 13467, 22287, 2376, 6097, 26312, 2974, 9114, 21787, 28010, 4725, 15387, 3274, 10762, 31695, 17320,
	18324, 12441, 16801, 27376, 22464, 7500, 5666, 18144, 15314, 31914, 31627, 6495, 5226, 31203, 2331, 4668,
	12650, 18275, 351, 7268, 31319, 30119, 7600, 2905, 13826, 11343, 13053, 15583, 30055, 31093, 5067, 761,
	9685, 11070, 21369, 27155, 3663, 26542, 20169, 12161, 15411, 30401, 7580, 31784, 8985, 29367, 20989, 14203,
	29694, 21167, 10337, 1706, 28578, 887, 3373, 19477, 14382, 675, 7033, 15111, 26138, 12252, 30996, 21409,
	25678, 18555, 13256, 23316, 22407, 16727, 991, 9236, 5373, 29402, 6117, 15241, 27715, 19291, 19888, 19847
};

void VectorAngles(const float *forward, float *angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		pitch = 0;
	}
	else
	{
		yaw = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);

		pitch = atan2(forward[2], tmp) * 180 / M_PI;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

cNoSpread::cNoSpread(void)
{
}

cNoSpread::~cNoSpread(void)
{
}

unsigned int cNoSpread::U_Random( void ) 
{ 
	iSeed *= 69069; 
	iSeed += seed_table[ iSeed & 0xff ];
 
	return ( ++iSeed & 0x0fffffff ); 
} 

void cNoSpread::U_Srand(unsigned int seed)
{
	iSeed = seed_table[ seed & 0xff ];
}

float cNoSpread::UTIL_SharedRandomFloat(unsigned int seed, float low, float high)
{
	//
	unsigned int range;

	U_Srand( (int)seed + *(int *)&low + *(int *)&high );

	U_Random();
	U_Random();

	range = high - low;
	if ( !range )
	{
		return low;
	}
	else
	{
		int tensixrand;
		float offset;

		tensixrand = U_Random() & 65535;

		offset = (float)tensixrand / 65536.0f;

		return (low + offset * range );
	}
}

/*void cNoSpread::AngleVectors(const float *angles, float *forward, float *right, float *up)
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;
	
	angle = angles[1] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[0] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[2] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (-1*sr*sp*sy+-1*cr*cy);
		right[2] = -1*sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy+-sr*-sy);
		up[1] = (cr*sp*sy+-sr*cy);
		up[2] = cr*cp;
	}
}*/

void cNoSpread::DefaultSpreadVar(int weaponid)
{
	int id = weaponid;

	if (id == WEAPONLIST_DEAGLE)
		me.spread.spreadvar = 0.9f;
	else if (id == WEAPONLIST_MP5)
		me.spread.spreadvar = 0.0f;
	else if (id == WEAPONLIST_AK47)
		me.spread.spreadvar = 0.2f;
	else if (id == WEAPONLIST_SG552)
		me.spread.spreadvar = 0.2f;
	else if (id == WEAPONLIST_AUG)
		me.spread.spreadvar = 0.3f;
	else if (id == WEAPONLIST_M4A1)
		me.spread.spreadvar = 0.2f;
	else if (id == WEAPONLIST_M249)
		me.spread.spreadvar = 0.2f;
	else if (id == WEAPONLIST_MAC10)
		me.spread.spreadvar = 0.15f;
	else if (id == WEAPONLIST_UMP45)
		me.spread.spreadvar = 0;
	else if (id == WEAPONLIST_TMP)
		me.spread.spreadvar = 0.2f;
	else if(id == WEAPONLIST_P90)
		me.spread.spreadvar = 0.15f;
	else if (id == WEAPONLIST_P228)
		me.spread.spreadvar = 0.9f;
	else if (id == WEAPONLIST_FIVESEVEN)
		me.spread.spreadvar = 0.92f;
	else if (id == WEAPONLIST_ELITE)
		me.spread.spreadvar = 0.88f;
	else if (id == WEAPONLIST_GLOCK18)
		me.spread.spreadvar = 0.9f;
	else if (id == WEAPONLIST_USP)
		me.spread.spreadvar = 0.92f;
	else if (id == WEAPONLIST_G3SG1)
		me.spread.spreadvar = 0.2f;
	else if	 (id == WEAPONLIST_SG550)
		me.spread.spreadvar = 0.2f;
	else
		me.spread.spreadvar = 0.0f;
}

void cNoSpread::HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed)
{
	static int prevammo = 0, curammo;
	int i, index, Id;
	if(!from || !to || !cmd)return;
	if(!me.alive)return;

/*	if (runfuncs)
	{
		me.spread.random_seed = random_seed;

		me.spread.gtime = time;

		me.pmFlags = to->client.flags;
		//glockburst
		float FullNoSpread[3];
		
		int weaponID = to->client.m_iId;

		if (cmd->buttons & IN_ATTACK && CanCurWeaponAttack()) // catch case when pistol and IN_ATTACK is always on and not firing
		{
		//	PrimaryAttack();
		}
		else if (!(cmd->buttons & (IN_ATTACK | IN_ATTACK2)))
		{
			if (me.spread.firing)
			{
				me.spread.firing = false;

				if (me.spread.recoil > 15)
					me.spread.recoil = 15;

				me.spread.recoiltime = time + 0.4;
			}

			if (IsCurWeaponSec())
			{
				me.spread.recoil = 0;
			}
			else if (me.spread.recoil > 0)
			{
				if (me.spread.recoiltime <= time)
				{
					me.spread.recoiltime = me.spread.recoiltime + 0.0225;
					me.spread.recoil--;
				}
			}
		}
		
			static int last;
			if (me.curWeaponID != last) // FIX: This doesn't catch when you have a weapon and you buy the same weapon
			{
				prevammo = 0;

				me.spread.recoil = 0;
				me.spread.prevtime = 0;
				DefaultSpreadVar(me.curWeaponID);
				me.spread.recoiltime = time;
				me.spread.firing = false;
				last = me.curWeaponID;
			}

		if (to->weapondata[me.curWeaponID].m_fInReload)
		{
			me.spread.recoil = 0;
			me.spread.prevtime = 0;
			DefaultSpreadVar(me.curWeaponID);
			me.spread.recoiltime = time;
			me.spread.firing = false;
		}
	}*/
	if(runfuncs)
	{
		me.spread.random_seed = random_seed;

		me.spread.gtime = time;

		me.prcflags = to->client.flags;

		if (cmd->buttons & IN_ATTACK && CanCurWeaponAttack()) // catch case when pistol and IN_ATTACK is always on and not firing
		{
		//	PrimaryAttack();
		}
		else if (!(cmd->buttons & (IN_ATTACK | IN_ATTACK2)))
		{
			if (me.spread.firing)
			{
				me.spread.firing = false;

				if (me.spread.recoil > 15)
					me.spread.recoil = 15;

				me.spread.recoiltime = time + 0.4;
			}

			if (IsCurWeaponSec())
			{
				me.spread.recoil = 0;
			}
			else if (me.spread.recoil > 0)
			{
				if (me.spread.recoiltime <= time)
				{
					me.spread.recoiltime = me.spread.recoiltime + 0.0225;
					me.spread.recoil--;
				}
			}
		}

		for (i=0;i<WeaponList.size();i++)
		{
			if (WeaponList[i].Id == to->client.m_iId)
			{
				if (!WeaponList[i].CurWeapon) // FIX: This doesn't catch when you have a weapon and you buy the same weapon
				{
					prevammo = 0;

					me.spread.recoil = 0;
					me.spread.prevtime = 0;
					DefaultSpreadVar(WeaponList[i].Id);
					me.spread.recoiltime = time;
					me.spread.firing = true;
				}

				WeaponList[i].CurWeapon = true;
			}
			else
				WeaponList[i].CurWeapon = false;
		}

		for (i=0;i<MAX_WEAPONS;i++)
		{
			// this assumes (i == wd[i].m_iId)
			index = GetWeaponIndexByID(i);
			if (index == -1)
				continue;

			if (to->weapondata[i].m_iId)
				memcpy(&WeaponList[index].weapondata, &to->weapondata[i], sizeof(weapon_data_t));
			else
				memset(&WeaponList[index].weapondata, 0, sizeof(weapon_data_t));
		}

		if (IsReloading())
		{
			Id = GetCurWeaponId();

			me.spread.recoil = 0;
			me.spread.prevtime = 0;
			DefaultSpreadVar(Id);
			me.spread.recoiltime = time;
			me.spread.firing = false;
		}
	}
}

void cNoSpread::PrimaryAttack(void)
{
	int id;

	id = me.iWeapon;

	switch (id)
	{
	case 26:
		if (me.spread.prevtime)
		{
			me.spread.spreadvar = me.spread.spreadvar - (0.35 * (0.4 - (me.spread.gtime - me.spread.prevtime)));

			if (me.spread.spreadvar > 0.9)
				me.spread.spreadvar = 0.9f;
			else if (me.spread.spreadvar < 0.55)
				me.spread.spreadvar = 0.55f;
		}

		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;

		break;
	case 10:
		if (me.spread.prevtime)
		{
			me.spread.spreadvar = me.spread.spreadvar - (0.275 * (0.325 - (me.spread.gtime - me.spread.prevtime)));

			if (me.spread.spreadvar > 0.88)
				me.spread.spreadvar = 0.88f;
			else if (me.spread.spreadvar < 0.55)
				me.spread.spreadvar = 0.55f;
		}

		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;

		break;
	case 14:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = ((float)me.spread.recoil * me.spread.recoil * me.spread.recoil) / 200.0f + 0.35f;

		if (me.spread.spreadvar > 1.25)
			me.spread.spreadvar = 1.25f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 15:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = ((float)me.spread.recoil * me.spread.recoil * me.spread.recoil) / 215.0f + 0.3f;

		if (me.spread.spreadvar > 1.0)
			me.spread.spreadvar = 1.0f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 11:
		if (me.spread.prevtime)
		{
			me.spread.spreadvar = me.spread.spreadvar - (0.25 * (0.275 - (me.spread.gtime - me.spread.prevtime)));

			if (me.spread.spreadvar > 0.92)
				me.spread.spreadvar = 0.92f;
			else if (me.spread.spreadvar < 0.725)
				me.spread.spreadvar = 0.725f;
		}

		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;

		break;
	case 17:
		//if (!IsCurWeaponInBurst())
			me.spread.recoil++;

		if (me.spread.prevtime)
		{
			me.spread.spreadvar = me.spread.spreadvar - (0.275 * (0.325 - (me.spread.gtime - me.spread.prevtime)));

			if (me.spread.spreadvar > 0.9)
				me.spread.spreadvar = 0.9f;
			else if (me.spread.spreadvar < 0.6)
				me.spread.spreadvar = 0.6f;
		}

		me.spread.prevtime = me.spread.gtime;

		break;
	case 1:
		if (me.spread.prevtime)
		{
			me.spread.spreadvar = me.spread.spreadvar - (0.3 * (0.325 - (me.spread.gtime - me.spread.prevtime)));

			if (me.spread.spreadvar > 0.9)
				me.spread.spreadvar = 0.9f;
			else if (me.spread.spreadvar < 0.6)
				me.spread.spreadvar = 0.6f;
		}

		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;

		break;
	case 24:
		if (me.spread.brokentime)
		{
			me.spread.spreadvar = 0.55 + (0.3 * (me.spread.gtime - me.spread.brokentime));

			if (me.spread.spreadvar > 0.98)
				me.spread.spreadvar = 0.98f;
		}

		me.spread.recoil++;
		me.spread.brokentime = me.spread.gtime;
		me.spread.firing = true;

		break;
	case 13:
		if (me.spread.brokentime)
		{
			me.spread.spreadvar = 0.65 + (0.35 * (me.spread.gtime - me.spread.brokentime));

			if (me.spread.spreadvar > 0.98)
				me.spread.spreadvar = 0.98f;
		}

		me.spread.recoil++;
		me.spread.brokentime = me.spread.gtime;
		me.spread.firing = true;

		break;
	case 16:
		if (me.spread.prevtime)
		{
			me.spread.spreadvar = me.spread.spreadvar - (0.275 * (0.3 - (me.spread.gtime - me.spread.prevtime)));

			if (me.spread.spreadvar > 0.92)
				me.spread.spreadvar = 0.92f;
			else if (me.spread.spreadvar < 0.6)
				me.spread.spreadvar = 0.6f;
		}

		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;
		break;
	case 28:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 200.0f + 0.35;

		if (me.spread.spreadvar > 1.25)
			me.spread.spreadvar = 1.25f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 27:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 220.0f + 0.3;

		if (me.spread.spreadvar > 1)
			me.spread.spreadvar = 1.0f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 8:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 215.0f + 0.3;

		if (me.spread.spreadvar > 1.0)
			me.spread.spreadvar = 1.0f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 20:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 175.0f + 0.4;

		if (me.spread.spreadvar > 0.9)
			me.spread.spreadvar = 0.9f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 22:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 220.0f + 0.3;

		if (me.spread.spreadvar > 1)
			me.spread.spreadvar = 1.0f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 19:
		me.spread.recoil++;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 220.1f + 0.45; // CS 1.6 FIX

		if (me.spread.spreadvar > 0.75)
			me.spread.spreadvar = 0.75f;

		me.spread.prevtime = me.spread.gtime;
		me.spread.firing = true;

		break;
	case 7:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 200.0f + 0.6;

		if (me.spread.spreadvar > 1.65)
			me.spread.spreadvar = 1.65f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 30:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil / 175.0f + 0.45;

		if (me.spread.spreadvar > 1)
			me.spread.spreadvar = 1.0f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 23:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 200.0f + 0.55;

		if (me.spread.spreadvar > 1.4)
			me.spread.spreadvar = 1.4f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 12:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil / 210.0f + 0.5;

		if (me.spread.spreadvar > 1.0)
			me.spread.spreadvar = 1.0f;

		me.spread.prevtime = me.spread.gtime;

		break;
	case 18:
		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;
		me.spread.firing = true;

		break;
	case 3:
		me.spread.recoil++;
		me.spread.prevtime = me.spread.gtime;
		me.spread.firing = true;

		break;
	default:
		break;
	}

	return;
}

float cNoSpread::GetVecSpread(float *velocity)
{
	bool ducking;
	int recoil;
	float tmpvelocity[3], spread = 0;

	recoil = me.spread.recoil;

	if (gEngfuncs.GetEntityByIndex(me.entindex)->curstate.usehull)
		ducking = true;
	else
		ducking = false;

	float speed = Vector(velocity).Length();
	int id = me.iWeapon;

	switch (id)
	{
	case WEAPONLIST_DEAGLE:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.25 * (1.0f - me.spread.spreadvar);
			else if (me.pmFlags & FL_DUCKING)
				spread = 0.115 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.13 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.5 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_ELITE:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.175 * (1.0f - me.spread.spreadvar);
			else if (me.pmFlags & FL_DUCKING)
				spread = 0.08 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.1 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.3 * (1.0f - me.spread.spreadvar);

		break;
case WEAPONLIST_GALIL:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.04;
			else
				spread = me.spread.spreadvar * 0.0375;
		}
		else
			spread = me.spread.spreadvar * 0.4 + 0.03;

		break;
	case WEAPONLIST_FAMAS:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.03;
			else
				spread = me.spread.spreadvar * 0.020;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .04;
		break;
	case WEAPONLIST_FIVESEVEN:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.255 * (1.0f - me.spread.spreadvar);
			else if (me.pmFlags & FL_DUCKING)
				spread = 0.075 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.15 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.5 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_GLOCK18:
        {
				if (!(me.pmFlags & FL_ONGROUND))
					spread = 1.2 * (1 - me.spread.spreadvar);
				else if (speed)
					spread = 0.185 * (1 - me.spread.spreadvar);
				else if (me.pmFlags & FL_DUCKING)
					spread = 0.095 * (1 - me.spread.spreadvar);
				else
					spread = 0.3 * (1 - me.spread.spreadvar);
        }
		break;
	case WEAPONLIST_P228:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.255 * (1.0f - me.spread.spreadvar);
			else if (me.pmFlags & FL_DUCKING)
				spread = 0.075 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.15 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.5 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_G3SG1:
		if (me.pmFlags & FL_ONGROUND)
		{
			 if (speed > 100.0f)
				spread = 0.15f;
			else if (me.pmFlags & FL_DUCKING)
				spread = 0.04f * (1.0f - me.spread.spreadvar);
			else
				spread = 0.06f * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 0.45f * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_SG550:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.15f;
			else if (me.pmFlags & FL_DUCKING)
				spread = 0.04 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.05 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 0.45 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_USP:
		if (me.pmFlags & FL_ONGROUND)
			{
				if (speed)
					spread = 0.225 * (1.0f - me.spread.spreadvar);
				else if (me.pmFlags & FL_DUCKING)
					spread = 0.08 * (1.0f - me.spread.spreadvar);
				else
					spread = 0.1 * (1.0f - me.spread.spreadvar);
			}
			else
				spread = 1.2 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_AK47:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.04;
			else
				spread = me.spread.spreadvar * 0.0275;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .04;

		break;
	case WEAPONLIST_SG552:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.035;
			else
				spread = me.spread.spreadvar * 0.02;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .035;

		break;
	case WEAPONLIST_AUG:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.035;
			else
				spread = me.spread.spreadvar * 0.02;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .035;

		break;
	case WEAPONLIST_M249:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.095 + 0.045;
			else
				spread = me.spread.spreadvar * 0.03;
		}
		else
			spread = me.spread.spreadvar * 0.5 + .045;

		break;
	case WEAPONLIST_M4A1:
		if (me.pmFlags & FL_ONGROUND)
		{

			{
				if (speed > 140.0f)
					spread = me.spread.spreadvar * 0.07 + 0.035;
				else
					spread = me.spread.spreadvar * 0.025;
			}
		}
		else
			spread = me.spread.spreadvar * 0.4 + .035;

		break;
	case WEAPONLIST_MP5:
		if (me.pmFlags & FL_ONGROUND)
			spread = 0.04 * me.spread.spreadvar;
		else
			spread = 0.2 * me.spread.spreadvar;
		break;
	case WEAPONLIST_MAC10:
		if (me.pmFlags & FL_ONGROUND)
			spread = 0.03 * me.spread.spreadvar;
		else
			spread = 0.375 * me.spread.spreadvar;

		break;
	case WEAPONLIST_P90:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed > 170.0f)
				spread = me.spread.spreadvar * 0.115;
			else
				spread = me.spread.spreadvar * 0.045;
		}
		else
			spread = me.spread.spreadvar * 0.3;

		break;
	case WEAPONLIST_TMP:
		if (me.pmFlags & FL_ONGROUND)
			spread = 0.03 * me.spread.spreadvar;
		else
			spread = 0.25 * me.spread.spreadvar;

		break;
	case WEAPONLIST_UMP45:
		if (me.pmFlags & FL_ONGROUND)
			spread = 0.04 * me.spread.spreadvar;
		else
			spread = 0.24 * me.spread.spreadvar;

		break;
	case WEAPONLIST_AWP:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed < 10.0f)
			{
				if (me.pmFlags & FL_DUCKING)
					spread = 0;
				else
					spread = 0.001f;
			}
			else if (speed < 140.0f)
			{
				spread = 0.1f;
			}
			else
				spread = 0.25f;
		}
		else
			spread = 0.85f;

		if (!(me.iFOV < 90.0f))
			spread += 0.08f;

		break;
	case WEAPONLIST_SCOUT:
		if (me.pmFlags & FL_ONGROUND)
		{
			if (speed < 170.0f)
			{
				if (me.pmFlags & FL_DUCKING)
					spread = 0;
				else
					spread = 0.007f;
			}
			else
				spread = 0.075f;
		}
		else
			spread = 0.2f;

		if (!(me.iFOV < 90.0f))
			spread += 0.025f;

		break;
	default:
		spread = 0;
		break;
	}

	return spread;

}

void cNoSpread::GetSpreadXY(unsigned int seed, int future, float *velocity, float *vec)
{
	float vecspread;

	vec[0] = UTIL_SharedRandomFloat(seed + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 1 + future, -0.5, 0.5);

	vec[1] = UTIL_SharedRandomFloat(seed + 2 + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 3 + future, -0.5, 0.5);

	vecspread = GetVecSpread(velocity);

	vec[0] *= vecspread;
	vec[1] *= vecspread;

	return;
}

void cNoSpread::GetRecoilOffset(unsigned int seed, int future, float *inangles, float *velocity, float *outangles)
{
/*	float forward[3], right[3], up[3], vecDir[3];
	float view[3], dest[3], diff[3], spread[2];

	AngleVectors(inangles, forward, right, up);

	spread[0] = 1.0f;
	spread[1] = 1.0f;
	GetSpreadXY(seed, future, velocity, spread);

	vecDir[0] = forward[0] + spread[0] * right[0] + spread[1] * up[0];
	view[0] = 8192 * vecDir[0];

	vecDir[1] = forward[1] + spread[0] * right[1] + spread[1] * up[1];
	view[1] = 8192 * vecDir[1];

	vecDir[2] = forward[2] + spread[0] * right[2] + spread[1] * up[2];
	view[2] = 8192 * vecDir[2];

	VectorAngles(view, dest);
	dest[0] *= -1;

	diff[0] = inangles[0] - dest[0];
	diff[1] = inangles[1] - dest[1];
	diff[2] = 0;

	//outangles[0] = inangles[0] + diff[0];

	if (inangles[0] + diff[0] > 89)
		inangles[0] = 89;

	if (inangles[0] + diff[0] < -89)
		inangles[0] = -89;

	//outangles[1] =  inangles[1] + diff[1];

	if (inangles[1] + diff[1] < 0)
		inangles[1] += 360;

	if (inangles[1] > 360)
		inangles[1] -= 360;

	outangles[2] = inangles[2];*/

	float forward[3], right[3], up[3], vecDir[3];
	float view[3], dest[3], spread[2];

	gEngfuncs.pfnAngleVectors(inangles, forward, right, up);

	spread[0] = 1.0f;
	spread[1] = 1.0f;
	GetSpreadXY(seed, future, velocity, spread);

	vecDir[0] = forward[0] + spread[0] * right[0] + spread[1] * up[0];
	view[0] = 8192 * vecDir[0];

	vecDir[1] = forward[1] + spread[0] * right[1] + spread[1] * up[1];
	view[1] = 8192 * vecDir[1];

	vecDir[2] = forward[2] + spread[0] * right[2] + spread[1] * up[2];
	view[2] = 8192 * vecDir[2];

	VectorAngles(view, dest);
	dest[0] *= -1;

	outangles[0] = inangles[0] - dest[0];
	outangles[1] = inangles[1] - dest[1];
	outangles[2] = 0;
}