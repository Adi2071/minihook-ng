
#ifndef CLIENT_H
#define CLIENT_H

#include <windows.h>
#include <string>
#include <vector>
#undef NDEBUG
#include <assert.h>
#include "cvar.h"
#include "hlsdk_headers/wrect.h"
#include "hlsdk_headers/cl_dll.h"
#include "hlsdk_headers/util_vector.h"
#include "hlsdk_headers/cl_entity.h"
#include "timehandling.h"
#include "weaponslist.h"
#include "playeritems.h"
#include "util.h"

#define TEAM_TERROR 1
#define TEAM_CT		2

bool bIsEntValid(cl_entity_s * ent);
void updateLocalPlayer();

//the following is from ogc
// from cldll_int.h 
#ifndef CDLL_INT_H
typedef unsigned char 		byte;
typedef unsigned short 		word;


typedef struct
{
	char *name;
	short ping;
	byte thisplayer;  // TRUE if this is the calling player

  // stuff that's unused at the moment,  but should be done
	byte spectator;
	byte packetloss;

	char *model;
	short topcolor;
	short bottomcolor;

} hud_player_info_t;
#endif

//================================================================
#define USP_SILENCER (1 << 0)
#define GLOCK18_BURST (1 << 1)
#define M4A1_SILENCER (1 << 2)
//================================================================

typedef struct
{
	unsigned int random_seed;
	int recoil;
	float gtime;
	float prevtime;
	float brokentime; // This is only supposed to be set to zero when you buy the sg550 or the g3sg1
	// not when you reload, switch weapons or pick up a weapon, this is do to the
	// cs bugs for these guns (valve fix your code please)
	float spreadvar;
	float lastSG550SpreadVar;
	float recoiltime;
	bool firing;
	int WeaponState;
}spread_info;

struct local_player_info
{
	local_player_info():team(0),iClip(0),iFOV(0)
		,inZoomMode(false)
		,alive(true),headshots(0),entindex(0)
	{}

	int team;
	//struct cl_entity_s *ent;
	int iWeapon;
	int iClip;
	int iFOV;  // holds the current FOV in CS, not the one which OGC has set.
	bool inZoomMode;
	bool alive;
	float punchangle[3];
	float lastpunch[3];
	int pmFlags; 
	int pmMoveType; // movetype 5 = ladder
	float pmVelocity[3];
	float pmEyePos[3];

	float viewAngles[3];

	float frametime;

	int entindex;
	//int kills;  // already found in playerinfo
	//int deaths; // already found in playerinfo
	int headshots;
	float hspercent;
	int prcflags;
	spread_info spread;
};
extern local_player_info me;



//================================================================
enum    { MAX_TARGET_SPOTS=55 };
class PlayerInfo 
{
private:
	int     m_lastUpdateType;
	double  m_lastUpdateTime;
	vec3_t   m_origin;
	char    m_weapon[32];

	bool alive;
	int entindex;
protected:
	friend class VecPlayers;
	void PlayerInfo::init( int _entindex) 
	{ 
		team=2;
		iInfo=0;
		entinfo.name="\\missing-name\\";
		entinfo.ping=0;
		entinfo.thisplayer=0;
		entinfo.spectator=0;
		entinfo.packetloss=0;
		entinfo.model="missing-model";
		entinfo.topcolor=0;
		numTargetSpots=0;
		alive=false;
		entindex = _entindex;
		distance = 1000.0;
		visible  = false;
		gotbones = false;
		frags=0;
		deaths=0;
		ratio=0;
		bestplayer=false;
		m_lastUpdateType=0;
		strcpy(m_weapon,"N-A");
	}
private:
	hud_player_info_t entinfo;

public:
	void updateEntInfo();
	const char* getName() const { return entinfo.name; }

	int    team;
	int    iInfo;
	float  distance;
	bool   visible;

	bool gotbones;

	// infos needed for points system:
	int    frags;
	int    deaths;
	float  ratio;
	bool   bestplayer; // based on ratio, not frags!
	float  fovangle;   // minimum fov a player is in

	// aimbot points
	float points;

	// model based aiming data:
	int     numTargetSpots;
	vec3_t  TargetSpots[MAX_TARGET_SPOTS];

	//enum   { UPDATE_MISSING=0, UPDATE_ADDENT=1, UPDATE_SOUND_RADAR=2};

	void setAlive() { alive = true;  }
	void setDead () { alive = false; m_lastUpdateType=UPDATE_MISSING; }
	bool isAlive () { return  alive; }

	struct cl_entity_s * getEnt() { return gEngfuncs.GetEntityByIndex(entindex); }

	// position update reporting
	void   updateClear    ()
	{ 
		m_lastUpdateType=UPDATE_MISSING; 
	}
	
	void   updateAddEntity (const float* neworg)
	{ 
		if(alive)
		{
			m_lastUpdateType=UPDATE_ADDENT; 
			m_lastUpdateTime=ClientTime::current; 
			VectorCopy(neworg,m_origin); 
		}
	}
	void   updateSoundRadar(const float* neworg)   
	{ 
		if(alive)
		{
			if( m_lastUpdateType!=UPDATE_ADDENT || timeSinceLastUpdate()>0.3 ) // dont mess with hud_addentity updates
			{
				m_lastUpdateType=UPDATE_SOUND_RADAR;  
				m_lastUpdateTime=ClientTime::current; 
				VectorCopy(neworg,m_origin); 
			}
		}
	}

	// position update queries
	enum UPDATE_TYPES   { UPDATE_MISSING=0, UPDATE_ADDENT=1, UPDATE_SOUND_RADAR=2};
	bool   isUpdated       ()    { return m_lastUpdateType!=UPDATE_MISSING; }
	bool   isUpdatedAddEnt ()    { return m_lastUpdateType==UPDATE_ADDENT;  }
	int    updateType()          { return m_lastUpdateType; }
	vec3_t  origin()       { return m_origin; }
	float  timeSinceLastUpdate() { return (float)(ClientTime::current-m_lastUpdateTime); }
	

	// weapon update:
	const char* getWeapon() { return m_weapon; }
	void setWeapon(const char* newname)
	{
		register int len = strlen(newname);
		if(len && len<30) { strcpy(m_weapon,newname); }
	}

public:
	PlayerInfo() { init(0); }
};

//================================================================
enum{  MAX_VPLAYERS =36 };
class VecPlayers
{
private:
	PlayerInfo* players;
public:
	~VecPlayers() { delete[] players; }
	VecPlayers() 
	{ 
		players = new PlayerInfo[MAX_VPLAYERS];
		for(int i=0;i<MAX_VPLAYERS;i++) { players[i].init(i); }
	}

	inline PlayerInfo& operator [] (unsigned int i)
	{
		if(i>=MAX_VPLAYERS) {return players[0];}
		else                {return players[i];}
	}
	
	inline unsigned int size() { return MAX_VPLAYERS; }

	void ClearTargetSpots(void) {
		for(int i = 0; i < size(); i++) {
			players[i].gotbones = false;
			players[i].numTargetSpots = 0;
		}
	}
};
extern VecPlayers vPlayers;
extern float newangles[3];
#endif
