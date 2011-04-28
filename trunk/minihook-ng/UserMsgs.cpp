#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "UserMsgs.h"
#include "client.h"
#include "NoSpread.h"

// Counterstrike
int hLogo(const char *pszName, int iSize, void *pbuf)
{
	return pLogo(pszName, iSize, pbuf);
}

int hResetHUD(const char *pszName, int iSize, void *pbuf)
{
	int Id = GetPriWeaponId();
	if (Id == WEAPONLIST_SG550 || Id == WEAPONLIST_G3SG1)
		me.spread.brokentime = 0.0f; // This catches all cases except when you buy one and than shoot some bullets and that buy another

	me.spread.recoil = 0;
	me.spread.prevtime = 0;
	gNoSpread.DefaultSpreadVar(Id);
	me.spread.firing = false;

	return pResetHUD(pszName, iSize, pbuf);
}

int hGameMode(const char *pszName, int iSize, void *pbuf)
{
	return pGameMode(pszName, iSize, pbuf);
}

int hInitHUD(const char *pszName, int iSize, void *pbuf)
{
	return pInitHUD(pszName, iSize, pbuf);
}

int hViewMode(const char *pszName, int iSize, void *pbuf)
{
	return pViewMode(pszName, iSize, pbuf);
}

int hSetFOV(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ( pbuf, iSize );
	me.iFOV = READ_BYTE();
	if(!me.iFOV)   { me.iFOV=90; }

	if(me.iFOV==90){ me.inZoomMode=false; }
	else           { me.inZoomMode=true;  } 

	return pSetFOV(pszName, iSize, pbuf);
}

int hHLTV(const char *pszName, int iSize, void *pbuf)
{
	return pHLTV(pszName, iSize, pbuf);
}

int hSpecHealth(const char *pszName, int iSize, void *pbuf)
{
	return pSpecHealth(pszName, iSize, pbuf);
}

int hConcuss(const char *pszName, int iSize, void *pbuf)
{
	return pConcuss(pszName, iSize, pbuf);
}

int hReloadSound(const char *pszName, int iSize, void *pbuf)
{
	return pReloadSound(pszName, iSize, pbuf);
}

int hBombDrop(const char *pszName, int iSize, void *pbuf)
{
	return pBombDrop(pszName, iSize, pbuf);
}

int hBombPickup(const char *pszName, int iSize, void *pbuf)
{
	return pBombPickup(pszName, iSize, pbuf);
}

int hADStop(const char *pszName, int iSize, void *pbuf)
{
	return pADStop(pszName, iSize, pbuf);
}

int hHostagePos(const char *pszName, int iSize, void *pbuf)
{
	return pHostagePos(pszName, iSize, pbuf);
}

int hHostageK(const char *pszName, int iSize, void *pbuf)
{
	return pHostageK(pszName, iSize, pbuf);
}

int hCZCareerHUD(const char *pszName, int iSize, void *pbuf)
{
	return pCZCareerHUD(pszName, iSize, pbuf);
}

int hShadowIdx(const char *pszName, int iSize, void *pbuf)
{
	return pShadowIdx(pszName, iSize, pbuf);
}

int hBotVoice(const char *pszName, int iSize, void *pbuf)
{
	return pBotVoice(pszName, iSize, pbuf);
}

int hBrass(const char *pszName, int iSize, void *pbuf)
{
	return pBrass(pszName, iSize, pbuf);
}

int hFog(const char *pszName, int iSize, void *pbuf)
{
	return pFog(pszName, iSize, pbuf);
}

int hShowTimer(const char *pszName, int iSize, void *pbuf)
{
	return pShowTimer(pszName, iSize, pbuf);
}

int hTeamNames(const char *pszName, int iSize, void *pbuf)
{
	return pTeamNames(pszName, iSize, pbuf);
}

int hFeign(const char *pszName, int iSize, void *pbuf)
{
	return pFeign(pszName, iSize, pbuf);
}

int hDetpack(const char *pszName, int iSize, void *pbuf)
{
	return pDetpack(pszName, iSize, pbuf);
}

int hMOTD(const char *pszName, int iSize, void *pbuf)
{
	return pMOTD(pszName, iSize, pbuf);
}

int hBuildSt(const char *pszName, int iSize, void *pbuf)
{
	return pBuildSt(pszName, iSize, pbuf);
}

int hRandomPC(const char *pszName, int iSize, void *pbuf)
{
	return pRandomPC(pszName, iSize, pbuf);
}

int hServerName(const char *pszName, int iSize, void *pbuf)
{
	return pServerName(pszName, iSize, pbuf);
}

int hScoreInfo(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);
	int idx = READ_BYTE();
	PlayerInfo& r = vPlayers[idx];

	r.frags  = READ_SHORT();
	r.deaths = READ_SHORT();

	if(r.frags<=0 )   { r.ratio=0; }
	else              { r.ratio = (double)r.frags / ((r.deaths<=0)?1:r.deaths); }

	// update bestplayer
	r.bestplayer = false;
	bool foundbetter = false;
	for(int i=0;i<MAX_VPLAYERS;i++)
	{
		if     ( r.ratio < vPlayers[i].ratio ) foundbetter = true;
		else if( r.ratio > vPlayers[i].ratio ) vPlayers[i].bestplayer=false;
	}
	if(!foundbetter) r.bestplayer = true;

	
	// score handling:
	if(idx==me.entindex)
	{
		static int lastfrags=0;
		static int lastdeaths=0;

		if(me.headshots>r.frags || r.frags==0) 
		{ 
			// reset statistics
			me.headshots = 0; 
			me.hspercent = 0;
			lastfrags    = r.frags;
			lastdeaths   = r.deaths;
		}
	}

	return pScoreInfo(pszName, iSize, pbuf);
}

int hTeamScore(const char *pszName, int iSize, void *pbuf)
{
	return pTeamScore(pszName, iSize, pbuf);
}

int hTeamInfo(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf,iSize);
	int px = READ_BYTE();
	char *teamtext = READ_STRING();

	updateLocalPlayer();
	if( strstr(teamtext, "TERRORIST"))
	{
		vPlayers[px].team = TEAM_TERROR;
		if(px==me.entindex){ me.team = TEAM_TERROR; }
	}
	else if( strstr(teamtext, "CT"))
	{
		vPlayers[px].team = TEAM_CT;
		if(px==me.entindex){ me.team = TEAM_CT; }
	}
	else
	{
		vPlayers[px].team = -1;
		if(px==me.entindex){ me.team = -1; }
	}

	return pTeamInfo(pszName, iSize, pbuf);
}

int hLocation(const char *pszName, int iSize, void *pbuf)
{
	return pLocation(pszName, iSize, pbuf);
}

int hSpectator(const char *pszName, int iSize, void *pbuf)
{
	return pSpectator(pszName, iSize, pbuf);
}

int hAllowSpec(const char *pszName, int iSize, void *pbuf)
{
	return pAllowSpec(pszName, iSize, pbuf);
}

int hForceCam(const char *pszName, int iSize, void *pbuf)
{
	return pForceCam(pszName, iSize, pbuf);
}

int hVGUIMenu(const char *pszName, int iSize, void *pbuf)
{
	return pVGUIMenu(pszName, iSize, pbuf);
}

int hTutorText(const char *pszName, int iSize, void *pbuf)
{
	return pTutorText(pszName, iSize, pbuf);
}

int hTutorLine(const char *pszName, int iSize, void *pbuf)
{
	return pTutorLine(pszName, iSize, pbuf);
}

int hTutorState(const char *pszName, int iSize, void *pbuf)
{
	return pTutorState(pszName, iSize, pbuf);
}

int hTutorClose(const char *pszName, int iSize, void *pbuf)
{
	return pTutorClose(pszName, iSize, pbuf);
}

int hBuyClose(const char *pszName, int iSize, void *pbuf)
{
	return pBuyClose(pszName, iSize, pbuf);
}

int hSpecHealth2(const char *pszName, int iSize, void *pbuf)
{
	return pSpecHealth2(pszName, iSize, pbuf);
}

int hBotProgress(const char *pszName, int iSize, void *pbuf)
{
	return pBotProgress(pszName, iSize, pbuf);
}

int hNVGToggle(const char *pszName, int iSize, void *pbuf)
{
	return pNVGToggle(pszName, iSize, pbuf);
}

int iLastWeaponID = 0;
int hCurWeapon(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ( pbuf, iSize );
	int iState = READ_BYTE();
	int iID    = READ_CHAR();
	int iClip  = READ_CHAR();
	if (iState) me.iClip = iClip;

	WeaponListCurWeapon(iState, iID, iClip);
	playerItems.msgCurWeapon (iState,iID,iClip);

	if (iID != iLastWeaponID)
	{
		iLastWeaponID      = iID;
		me.spread.recoil   = 0;
		me.spread.prevtime = 0;
		me.spread.firing   = false;
		gNoSpread.DefaultSpreadVar(iID);
	}

	// update our own weaponID:
	if(iState)
	{
		char * name = playerItems.getNamebyId(iID);

		if(!strcmp(name,"mp5navy")) me.iWeapon = WEAPONLIST_MP5;
		else me.iWeapon = iID;
	}

	return pCurWeapon(pszName, iSize, pbuf);
}

int hWeaponList(const char *pszName, int iSize, void *pbuf)
{
	char *weaponname;
	int ammo1type, max1, ammo2type, max2, slot, slotpos, id, flags;

	BEGIN_READ(pbuf, iSize);

	weaponname = READ_STRING();

	ammo1type = READ_CHAR();
	max1 = READ_BYTE();

	ammo2type = READ_CHAR();
	max2 = READ_BYTE();

	slot = READ_CHAR();
	slotpos = READ_CHAR();

	id = READ_CHAR();
	flags = READ_BYTE();

	WeaponListAdd(weaponname, ammo1type, max1, ammo2type, max2, slot, slotpos, id, flags);

	updateLocalPlayer();
	playerItems.msgWeaponList(iSize,pbuf);
	return pWeaponList(pszName, iSize, pbuf);
}

int hAmmoPickup(const char *pszName, int iSize, void *pbuf)
{
	return pAmmoPickup(pszName, iSize, pbuf);
}

int hWeapPickup(const char *pszName, int iSize, void *pbuf)
{
	return pWeapPickup(pszName, iSize, pbuf);
}

int hItemPickup(const char *pszName, int iSize, void *pbuf)
{
	return pItemPickup(pszName, iSize, pbuf);
}

int hHideWeapon(const char *pszName, int iSize, void *pbuf)
{
	return pHideWeapon(pszName, iSize, pbuf);
}

int hAmmoX(const char *pszName, int iSize, void *pbuf)
{
	return pAmmoX(pszName, iSize, pbuf);
}

int hCrosshair(const char *pszName, int iSize, void *pbuf)
{
	return pCrosshair(pszName, iSize, pbuf);
}

int hHealth(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ( pbuf, iSize );
	playerItems.health = READ_BYTE();
	return pHealth(pszName, iSize, pbuf);
}

int hDamage(const char *pszName, int iSize, void *pbuf)
{
	return pDamage(pszName, iSize, pbuf);
}

int hRadar(const char *pszName, int iSize, void *pbuf)
{
	return pRadar(pszName, iSize, pbuf);
}

int hScoreAttrib(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);
    int idx  = READ_BYTE();
    int info = READ_BYTE();
    vPlayers[idx].iInfo = info;

	//ApiImports->killDebuggers();

	if(info&1) { vPlayers[idx].setDead (); }
	else       { vPlayers[idx].setAlive(); }


	if(idx==me.entindex) me.alive = ((info&1)==0);
	return pScoreAttrib(pszName, iSize, pbuf);
}

int hClCorpse(const char *pszName, int iSize, void *pbuf)
{
	return pClCorpse(pszName, iSize, pbuf);
}

int hReceiveW(const char *pszName, int iSize, void *pbuf)
{
	return pReceiveW(pszName, iSize, pbuf);
}

int hSayText(const char *pszName, int iSize, void *pbuf)
{
	return pSayText(pszName, iSize, pbuf);
}

int hSendAudio(const char *pszName, int iSize, void *pbuf)
{
	return pSendAudio(pszName, iSize, pbuf);
}

int hGeiger(const char *pszName, int iSize, void *pbuf)
{
	return pGeiger(pszName, iSize, pbuf);
}

int hTrain(const char *pszName, int iSize, void *pbuf)
{
	return pTrain(pszName, iSize, pbuf);
}

int hBattery(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ( pbuf, iSize );
	playerItems.armor = READ_BYTE();
	return pBattery(pszName, iSize, pbuf);
}

int hArmorType(const char *pszName, int iSize, void *pbuf)
{
	return pArmorType(pszName, iSize, pbuf);
}

int hFlashlight(const char *pszName, int iSize, void *pbuf)
{
	return pFlashlight(pszName, iSize, pbuf);
}

int hFlashBat(const char *pszName, int iSize, void *pbuf)
{
	return pFlashBat(pszName, iSize, pbuf);
}

int hHudText(const char *pszName, int iSize, void *pbuf)
{
	return pHudText(pszName, iSize, pbuf);
}

int hHudTextPro(const char *pszName, int iSize, void *pbuf)
{
	return pHudTextPro(pszName, iSize, pbuf);
}

int hHudTextArgs(const char *pszName, int iSize, void *pbuf)
{
	return pHudTextArgs(pszName, iSize, pbuf);
}

int hGameTitle(const char *pszName, int iSize, void *pbuf)
{
	return pGameTitle(pszName, iSize, pbuf);
}

int hStatusText(const char *pszName, int iSize, void *pbuf)
{
	return pStatusText(pszName, iSize, pbuf);
}

int hStatusValue(const char *pszName, int iSize, void *pbuf)
{
	return pStatusValue(pszName, iSize, pbuf);
}

int hDeathMsg(const char *pszName, int iSize, void *pbuf)
{
	//DeathMsg: [B]Killer [B]Victim [B]Headshot [S]Weapon Name
	BEGIN_READ( pbuf, iSize );
	int killer = READ_BYTE();
	int victim = READ_BYTE();
	int headshot = READ_BYTE();
	char* weaponName = READ_STRING();

	vPlayers[victim].setDead();
	if ((!victim || victim == -1))//suicide or team change
	{
		vPlayers[killer].setDead();
	}

	if(victim == me.entindex)
		me.alive = false;

	if(killer==me.entindex && headshot)
	{
		me.headshots++;
	}

	return pDeathMsg(pszName, iSize, pbuf);
}

int hSecAmmoVal(const char *pszName, int iSize, void *pbuf)
{
	return pSecAmmoVal(pszName, iSize, pbuf);
}

int hSecAmmoIcon(const char *pszName, int iSize, void *pbuf)
{
	return pSecAmmoIcon(pszName, iSize, pbuf);
}

int hTextMsg(const char *pszName, int iSize, void *pbuf)
{
	return pTextMsg(pszName, iSize, pbuf);
}

int hStatusIcon(const char *pszName, int iSize, void *pbuf)
{
	return pStatusIcon(pszName, iSize, pbuf);
}

int hMoney(const char *pszName, int iSize, void *pbuf)
{
	return pMoney(pszName, iSize, pbuf);
}

int hBlinkAcct(const char *pszName, int iSize, void *pbuf)
{
	return pBlinkAcct(pszName, iSize, pbuf);
}

int hRoundTime(const char *pszName, int iSize, void *pbuf)
{
	return pRoundTime(pszName, iSize, pbuf);
}

int hBarTime(const char *pszName, int iSize, void *pbuf)
{
	return pBarTime(pszName, iSize, pbuf);
}

int hBarTime2(const char *pszName, int iSize, void *pbuf)
{
	return pBarTime2(pszName, iSize, pbuf);
}

int hTaskTime(const char *pszName, int iSize, void *pbuf)
{
	return pTaskTime(pszName, iSize, pbuf);
}

int hScenario(const char *pszName, int iSize, void *pbuf)
{
	return pScenario(pszName, iSize, pbuf);
}

int hShowMenu(const char *pszName, int iSize, void *pbuf)
{
	return pShowMenu(pszName, iSize, pbuf);
}

int hVoiceMask(const char *pszName, int iSize, void *pbuf)
{
	return pVoiceMask(pszName, iSize, pbuf);
}

int hReqState(const char *pszName, int iSize, void *pbuf)
{
	return pReqState(pszName, iSize, pbuf);
}

pfnUserMsgHook pLogo;
pfnUserMsgHook pResetHUD;
pfnUserMsgHook pGameMode;
pfnUserMsgHook pInitHUD;
pfnUserMsgHook pViewMode;
pfnUserMsgHook pSetFOV;
pfnUserMsgHook pHLTV;
pfnUserMsgHook pSpecHealth;
pfnUserMsgHook pConcuss;
pfnUserMsgHook pReloadSound;
pfnUserMsgHook pBombDrop;
pfnUserMsgHook pBombPickup;
pfnUserMsgHook pADStop;
pfnUserMsgHook pHostagePos;
pfnUserMsgHook pHostageK;
pfnUserMsgHook pCZCareerHUD;
pfnUserMsgHook pShadowIdx;
pfnUserMsgHook pBotVoice;
pfnUserMsgHook pBrass;
pfnUserMsgHook pFog;
pfnUserMsgHook pShowTimer;
pfnUserMsgHook pTeamNames;
pfnUserMsgHook pFeign;
pfnUserMsgHook pDetpack;
pfnUserMsgHook pMOTD;
pfnUserMsgHook pBuildSt;
pfnUserMsgHook pRandomPC;
pfnUserMsgHook pServerName;
pfnUserMsgHook pScoreInfo;
pfnUserMsgHook pTeamScore;
pfnUserMsgHook pTeamInfo;
pfnUserMsgHook pLocation;
pfnUserMsgHook pSpectator;
pfnUserMsgHook pAllowSpec;
pfnUserMsgHook pForceCam;
pfnUserMsgHook pVGUIMenu;
pfnUserMsgHook pTutorText;
pfnUserMsgHook pTutorLine;
pfnUserMsgHook pTutorState;
pfnUserMsgHook pTutorClose;
pfnUserMsgHook pBuyClose;
pfnUserMsgHook pSpecHealth2;
pfnUserMsgHook pBotProgress;
pfnUserMsgHook pNVGToggle;
pfnUserMsgHook pCurWeapon;
pfnUserMsgHook pWeaponList;
pfnUserMsgHook pAmmoPickup;
pfnUserMsgHook pWeapPickup;
pfnUserMsgHook pItemPickup;
pfnUserMsgHook pHideWeapon;
pfnUserMsgHook pAmmoX;
pfnUserMsgHook pCrosshair;
pfnUserMsgHook pHealth;
pfnUserMsgHook pDamage;
pfnUserMsgHook pRadar;
pfnUserMsgHook pScoreAttrib;
pfnUserMsgHook pClCorpse;
pfnUserMsgHook pReceiveW;
pfnUserMsgHook pSayText;
pfnUserMsgHook pSendAudio;
pfnUserMsgHook pGeiger;
pfnUserMsgHook pTrain;
pfnUserMsgHook pBattery;
pfnUserMsgHook pArmorType;
pfnUserMsgHook pFlashlight;
pfnUserMsgHook pFlashBat;
pfnUserMsgHook pHudText;
pfnUserMsgHook pHudTextPro;
pfnUserMsgHook pHudTextArgs;
pfnUserMsgHook pGameTitle;
pfnUserMsgHook pStatusText;
pfnUserMsgHook pStatusValue;
pfnUserMsgHook pDeathMsg;
pfnUserMsgHook pSecAmmoVal;
pfnUserMsgHook pSecAmmoIcon;
pfnUserMsgHook pTextMsg;
pfnUserMsgHook pStatusIcon;
pfnUserMsgHook pMoney;
pfnUserMsgHook pBlinkAcct;
pfnUserMsgHook pRoundTime;
pfnUserMsgHook pBarTime;
pfnUserMsgHook pBarTime2;
pfnUserMsgHook pTaskTime;
pfnUserMsgHook pScenario;
pfnUserMsgHook pShowMenu;
pfnUserMsgHook pVoiceMask;
pfnUserMsgHook pReqState;

// Day of defeat
int hYouDied(const char *pszName, int iSize, void *pbuf)
{
	return pYouDied(pszName, iSize, pbuf);
}

int hBloodPuff(const char *pszName, int iSize, void *pbuf)
{
	return pBloodPuff(pszName, iSize, pbuf);
}

int hHandSignal(const char *pszName, int iSize, void *pbuf)
{
	return pHandSignal(pszName, iSize, pbuf);
}

int hUseSound(const char *pszName, int iSize, void *pbuf)
{
	return pUseSound(pszName, iSize, pbuf);
}

int hScoreInfoLong(const char *pszName, int iSize, void *pbuf)
{
	return pScoreInfoLong(pszName, iSize, pbuf);
}

int hMapMarker(const char *pszName, int iSize, void *pbuf)
{
	return pMapMarker(pszName, iSize, pbuf);
}

int hWaveTime(const char *pszName, int iSize, void *pbuf)
{
	return pWaveTime(pszName, iSize, pbuf);
}

int hWaveStatus(const char *pszName, int iSize, void *pbuf)
{
	return pWaveStatus(pszName, iSize, pbuf);
}

int hWideScreen(const char *pszName, int iSize, void *pbuf)
{
	return pWideScreen(pszName, iSize, pbuf);
}

int hFrags(const char *pszName, int iSize, void *pbuf)
{
	return pFrags(pszName, iSize, pbuf);
}

int hObjScore(const char *pszName, int iSize, void *pbuf)
{
	return pObjScore(pszName, iSize, pbuf);
}

int hPStatus(const char *pszName, int iSize, void *pbuf)
{
	return pPStatus(pszName, iSize, pbuf);
}

int hScoreShort(const char *pszName, int iSize, void *pbuf)
{
	return pScoreShort(pszName, iSize, pbuf);
}

int hPClass(const char *pszName, int iSize, void *pbuf)
{
	return pPClass(pszName, iSize, pbuf);
}

int hPTeam(const char *pszName, int iSize, void *pbuf)
{
	return pPTeam(pszName, iSize, pbuf);
}

int hRoundState(const char *pszName, int iSize, void *pbuf)
{
	return pRoundState(pszName, iSize, pbuf);
}

int hCurMarker(const char *pszName, int iSize, void *pbuf)
{
	return pCurMarker(pszName, iSize, pbuf);
}

int hTimeLeft(const char *pszName, int iSize, void *pbuf)
{
	return pTimeLeft(pszName, iSize, pbuf);
}

int hScope(const char *pszName, int iSize, void *pbuf)
{
	return pScope(pszName, iSize, pbuf);
}

int hGameRules(const char *pszName, int iSize, void *pbuf)
{
	return pGameRules(pszName, iSize, pbuf);
}

int hCameraView(const char *pszName, int iSize, void *pbuf)
{
	return pCameraView(pszName, iSize, pbuf);
}

int hResetSens(const char *pszName, int iSize, void *pbuf)
{
	return pResetSens(pszName, iSize, pbuf);
}

int hObject(const char *pszName, int iSize, void *pbuf)
{
	return pObject(pszName, iSize, pbuf);
}

int hClientAreas(const char *pszName, int iSize, void *pbuf)
{
	return pClientAreas(pszName, iSize, pbuf);
}

int hInitObj(const char *pszName, int iSize, void *pbuf)
{
	return pInitObj(pszName, iSize, pbuf);
}

int hSetObj(const char *pszName, int iSize, void *pbuf)
{
	return pSetObj(pszName, iSize, pbuf);
}

int hStartProg(const char *pszName, int iSize, void *pbuf)
{
	return pStartProg(pszName, iSize, pbuf);
}

int hStartProgF(const char *pszName, int iSize, void *pbuf)
{
	return pStartProgF(pszName, iSize, pbuf);
}

int hProgUpdate(const char *pszName, int iSize, void *pbuf)
{
	return pProgUpdate(pszName, iSize, pbuf);
}

int hCancelProg(const char *pszName, int iSize, void *pbuf)
{
	return pCancelProg(pszName, iSize, pbuf);
}

int hTimerStatus(const char *pszName, int iSize, void *pbuf)
{
	return pTimerStatus(pszName, iSize, pbuf);
}

int hPlayersIn(const char *pszName, int iSize, void *pbuf)
{
	return pPlayersIn(pszName, iSize, pbuf);
}

int hPShoot(const char *pszName, int iSize, void *pbuf)
{
	return pPShoot(pszName, iSize, pbuf);
}

int hAmmoShort(const char *pszName, int iSize, void *pbuf)
{
	return pAmmoShort(pszName, iSize, pbuf);
}

int hReloadDone(const char *pszName, int iSize, void *pbuf)
{
	return pReloadDone(pszName, iSize, pbuf);
}

int hCapMsg(const char *pszName, int iSize, void *pbuf)
{
	return pCapMsg(pszName, iSize, pbuf);
}

int hClanTimer(const char *pszName, int iSize, void *pbuf)
{
	return pClanTimer(pszName, iSize, pbuf);
}

pfnUserMsgHook pYouDied;
pfnUserMsgHook pBloodPuff;
pfnUserMsgHook pHandSignal;
pfnUserMsgHook pUseSound;
pfnUserMsgHook pScoreInfoLong;
pfnUserMsgHook pMapMarker;
pfnUserMsgHook pWaveTime;
pfnUserMsgHook pWaveStatus;
pfnUserMsgHook pWideScreen;
pfnUserMsgHook pFrags;
pfnUserMsgHook pObjScore;
pfnUserMsgHook pPStatus;
pfnUserMsgHook pScoreShort;
pfnUserMsgHook pPClass;
pfnUserMsgHook pPTeam;
pfnUserMsgHook pRoundState;
pfnUserMsgHook pCurMarker;
pfnUserMsgHook pTimeLeft;
pfnUserMsgHook pScope;
pfnUserMsgHook pGameRules;
pfnUserMsgHook pCameraView;
pfnUserMsgHook pResetSens;
pfnUserMsgHook pObject;
pfnUserMsgHook pClientAreas;
pfnUserMsgHook pInitObj;
pfnUserMsgHook pSetObj;
pfnUserMsgHook pStartProg;
pfnUserMsgHook pStartProgF;
pfnUserMsgHook pProgUpdate;
pfnUserMsgHook pCancelProg;
pfnUserMsgHook pTimerStatus;
pfnUserMsgHook pPlayersIn;
pfnUserMsgHook pPShoot;
pfnUserMsgHook pAmmoShort;
pfnUserMsgHook pReloadDone;
pfnUserMsgHook pCapMsg;
pfnUserMsgHook pClanTimer;

// Deathmatch classic
int hQItems(const char *pszName, int iSize, void *pbuf)
{
	return pQItems(pszName, iSize, pbuf);
}

pfnUserMsgHook pQItems;

// Halflife
int hValClass(const char *pszName, int iSize, void *pbuf)
{
	return pValClass(pszName, iSize, pbuf);
}

int hSpecFade(const char *pszName, int iSize, void *pbuf)
{
	return pSpecFade(pszName, iSize, pbuf);
}

int hResetFade(const char *pszName, int iSize, void *pbuf)
{
	return pResetFade(pszName, iSize, pbuf);
}

int hBench(const char *pszName, int iSize, void *pbuf)
{
	return pBench(pszName, iSize, pbuf);
}

pfnUserMsgHook pValClass;
pfnUserMsgHook pSpecFade;
pfnUserMsgHook pResetFade;
pfnUserMsgHook pBench;

// oposing force
int hHudColor(const char *pszName, int iSize, void *pbuf)
{
	return pHudColor(pszName, iSize, pbuf);
}

int hOldWeapon(const char *pszName, int iSize, void *pbuf)
{
	return pOldWeapon(pszName, iSize, pbuf);
}

int hSetMenuTeam(const char *pszName, int iSize, void *pbuf)
{
	return pSetMenuTeam(pszName, iSize, pbuf);
}

int hStatsInfo(const char *pszName, int iSize, void *pbuf)
{
	return pStatsInfo(pszName, iSize, pbuf);
}

int hStatsPlayer(const char *pszName, int iSize, void *pbuf)
{
	return pStatsPlayer(pszName, iSize, pbuf);
}

int hTeamFull(const char *pszName, int iSize, void *pbuf)
{
	return pTeamFull(pszName, iSize, pbuf);
}

int hPlayerIcon(const char *pszName, int iSize, void *pbuf)
{
	return pPlayerIcon(pszName, iSize, pbuf);
}

int hCTFScore(const char *pszName, int iSize, void *pbuf)
{
	return pCTFScore(pszName, iSize, pbuf);
}

int hCustomIcon(const char *pszName, int iSize, void *pbuf)
{
	return pCustomIcon(pszName, iSize, pbuf);
}

int hFlagIcon(const char *pszName, int iSize, void *pbuf)
{
	return pFlagIcon(pszName, iSize, pbuf);
}

int hFlagTimer(const char *pszName, int iSize, void *pbuf)
{
	return pFlagTimer(pszName, iSize, pbuf);
}

int hPlyrBrowse(const char *pszName, int iSize, void *pbuf)
{
	return pPlyrBrowse(pszName, iSize, pbuf);
}

pfnUserMsgHook pHudColor;
pfnUserMsgHook pOldWeapon;
pfnUserMsgHook pSetMenuTeam;
pfnUserMsgHook pStatsInfo;
pfnUserMsgHook pStatsPlayer;
pfnUserMsgHook pTeamFull;
pfnUserMsgHook pPlayerIcon;
pfnUserMsgHook pCTFScore;
pfnUserMsgHook pCustomIcon;
pfnUserMsgHook pFlagIcon;
pfnUserMsgHook pFlagTimer;
pfnUserMsgHook pPlyrBrowse;

// team fortress classic