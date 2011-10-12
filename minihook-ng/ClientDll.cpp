#include <windows.h>
#include <string>
#include <vector>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "Calculations.h"
#include "Drawing.h"
#include "util.h"

#include "MenuElem.h"
#include "MenuDraw.h"
#include "MenuControl.h"

#include "client.h"
#include "NoSpread.h"
#include "norecoil.h"
#include "textures.h"
#include "perfectwall.h"
#include "BoneAimbot.h"

#include "HookPanel.h"
extern HookPanel* p_hkRootPanel;

using namespace std;

local_player_info me;
VecPlayers vPlayers;
VecTargets vTargets;

CMenuElem gDebug("DEBUG", ELEM_BASEMENU, NULL);

//credit Tetsuo
extern int Cstrike_SequenceInfo[] = 
{
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, // 0..9   
    0,    1,    2,    0,    1,    2,    0,    1,    2,    0, // 10..19 
    1,    2,    0,    1,    1,    2,    0,    1,    1,    2, // 20..29 
    0,    1,    2,    0,    1,    2,    0,    1,    2,    0, // 30..39 
    1,    2,    0,    1,    2,    0,    1,    2,    0,    1, // 40..49 
    2,    0,    1,    2,    0,    0,    0,    8,    0,    8, // 50..59 
    0,    16,   0,   16,    0,    0,    1,    1,    2,    0, // 60..69  Updates thanks to Tetsuo <3
    1,    1,    2,    0,    1,    0,    1,    0,    1,    2, // 70..79 
    0,    1,    2,   32,   40,   32,   40,   32,   32,   32, // 80..89
   33,   32,   33,   34,   64,    4,   34,   32,   32,    4, // 90..99
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4, // 100..109
    4														 // 110
};  

//credit Sploosh of GD
void AdjustSpeed(double x)
{
	DWORD d, ds;
	DWORD dwSpeedptr = (DWORD)pGlobalSpeed;
	
    VirtualProtect((PVOID)dwSpeedptr, 8, PAGE_EXECUTE_READWRITE, &d);
	*(double*)dwSpeedptr = (x * 1000);
	VirtualProtect((PVOID)dwSpeedptr, 8,d,&ds);
}

void DefaultSpeed(void)
{
	AdjustSpeed(1);
}

//========================================================================================
static bool isFakePlayer(int ax, cl_entity_s* ent);
//========================================================================================
static inline float GetDistanceFrom(const float* pos);
//========================================================================================
static void playerCalcExtraData(int ax, cl_entity_s* ent);
//========================================================================================

bool bIsEntValid(cl_entity_s * ent)
{
	cl_entity_s* localEnt = gEngfuncs.GetLocalPlayer();

	if(ent && ent != localEnt && !(ent->curstate.effects & EF_NODRAW) && ent->player && !ent->curstate.spectator 
		&& ent->curstate.solid && !(ent->curstate.messagenum < localEnt->curstate.messagenum))
		return true;

	return false;
}

bool ValidTarget(cl_entity_s* ent)
{
	int nPlayers = vPlayers.size();
	if(!bIsEntValid(ent)) { return false; }

	int entindex = ent->index;

	for(int px = 0; px < nPlayers; px++)
	{
		PlayerInfo& pi = vPlayers[px];

		if( (pi.getEnt() == ent) && (pi.team != me.team) )
		{
			return true;
		}
	}

	return false;
}

//========================================================================================
void updateLocalPlayer()
{
	me.entindex = 0;
	cl_entity_s * itsme = gEngfuncs.GetLocalPlayer();
	if(itsme)
	{
		me.entindex = itsme->index;
	}
}

//========================================================================================
static bool isFakePlayer(int ax, cl_entity_s* ent)
{
	register PlayerInfo& r = vPlayers[ax];

	if( ent->curstate.effects&EF_NODRAW ) { return true; }
	if( ax==me.entindex )                 { return true; }
	switch(ent->curstate.rendermode)
	{
	/*case kRenderTransColor:
	case kRenderTransTexture: 
		if( ent->curstate.renderamt<128 ) { return true;  }
		else                              { return false; }*/
	case kRenderNormal: { return false; }
	//default:            { return true;  }
	}
}

//========================================================================================
static inline float GetDistanceFrom(const float* pos)
{	
	register double a = pos[0] - me.pmEyePos[0];
	register double b = pos[1] - me.pmEyePos[1];
	register double c = pos[2] - me.pmEyePos[2];
	return sqrt(a*a + b*b + c*c);
}

//========================================================================================
void PlayerInfo::updateEntInfo()
{
	// this is the only place where pfnGetPlayerInfo should be called
	gEngfuncs.pfnGetPlayerInfo(entindex, &entinfo);

	if(!entinfo.name ) { entinfo.name  = "\\missing-name\\"; }
	if(!entinfo.model) { entinfo.model = "unknown model";    } 
}

//========================================================================================
static void playerCalcExtraData(int ax, cl_entity_s* ent)
{
	PlayerInfo& r = vPlayers[ax];

	// playername and model
	r.updateEntInfo();

	// weapon
	if( gStudio.GetModelByIndex )
	{
		model_s* mdl = gStudio.GetModelByIndex( ent->curstate.weaponmodel );
		if(mdl && mdl->name )  
		{
			char tmp[32];
			char szName[120];

			strcpy(szName,mdl->name);

			int len = strlen(szName);

			if( len > 14 && len < 120 )	// DOD source...
			{
				// e.g. "modles/w_awp.mdl"
				if (strstr(szName, "shield"))
				{
					strcpy(tmp,szName+23); 
					len -= 23;
				}
				else
				{
					strcpy(tmp,szName+9); 
					len -=9;
				}
				tmp[len-4] = 0;                          // strip ".mdl"
				r.setWeapon(tmp);
			}
		}
	}

	// distance
	r.distance  = GetDistanceFrom (r.origin()); if(r.distance<1) r.distance=1; // avoid division by zero
}


//========================= 
// Initialize
// 
// Called when the DLL is first loaded.
//=========================
int Initialize( cl_enginefunc_t *pEnginefuncs, int iVersion )
{
	int retval = gClientDll.Initialize(pEnginefuncs, iVersion);
	if(!retval)
	{
		return retval;
	}

	SCREENINFO si;
	si.iSize = sizeof(SCREENINFO);
	gEngfuncs.pfnGetScreenInfo(&si);

	m_iCenterX = si.iWidth / 2;
	m_iCenterY = si.iHeight / 2;

	//Visuals menu-------------------------------
	CMenuElem crosshair("Crosshair", ELEM_VALUE, &cvar.crosshair);
	crosshair.SetMaximumValue(2.0f);
	CMenuElem meLight("Light (me)", ELEM_VALUE, &cvar.light);
	CMenuElem targetLight("Targetlight (aimbot)", ELEM_VALUE, &cvar.tlight);
	CMenuElem showBone("Skeleton", ELEM_VALUE, &cvar.bone);
	//CMenuElem drawSpread("Draw Spread", ELEM_VALUE, &cvar.drawspread);
	//CMenuElem lambert("Lambert", ELEM_VALUE, &cvar.lambert);
	CMenuElem zoomAll("Zoom with all weapons", ELEM_VALUE, &cvar.zoomall);


	CMenuElem visualsMenu("Visuals", ELEM_SUBMENU, NULL);
	visualsMenu.AddElement(crosshair);
	visualsMenu.AddElement(meLight);
	visualsMenu.AddElement(targetLight);
	visualsMenu.AddElement(showBone);
	//visualsMenu.AddElement(drawSpread);
	//visualsMenu.AddElement(lambert);
	visualsMenu.AddElement(zoomAll);


	//Spread menu-------------------------------
	CMenuElem noSpread("NoSpread", ELEM_VALUE, &cvar.nospread);
	noSpread.SetMaximumValue(2.0f);

	CMenuElem noRecoil("NoRecoil", ELEM_VALUE, &cvar.norecoil);
	CMenuElem noVisRecoil("No Visual Recoil", ELEM_VALUE, &cvar.novisrecoil);

	CMenuElem spreadMenu("Spread Correction", ELEM_SUBMENU, NULL);
	spreadMenu.AddElement(noSpread);
	spreadMenu.AddElement(noRecoil);
	spreadMenu.AddElement(noVisRecoil);

	//Weapons menu
	CMenuElem autoAim("Autoaim", ELEM_VALUE, &cvar.aim);
	autoAim.SetMaximumValue(2.0f);
	CMenuElem aimSpot("Aimspot", ELEM_VALUE, &cvar.aimspot);
	aimSpot.SetMaximumValue(3.0f);
	CMenuElem aimPred("Aim prediction", ELEM_VALUE, &cvar.predahead);
	aimPred.SetMaximumValue(2.0f);
	CMenuElem speedReload("Speed Reload", ELEM_VALUE, &cvar.speedreload);
	CMenuElem shootTarget("Shoot target", ELEM_VALUE, &cvar.shoottarget);
	CMenuElem recoilCap("Recoil limit", ELEM_VALUE, &cvar.recoilcap);
	recoilCap.SetMaximumValue(15.0f);
	CMenuElem autoFire("Autofire (rapid pistol)", ELEM_VALUE, &cvar.autofire);
	CMenuElem triggerBot("Triggerbot", ELEM_VALUE, &cvar.triggerbot);
	triggerBot.SetMaximumValue(2.0f);

	CMenuElem weaponsMenu("Weapon Options", ELEM_SUBMENU, NULL);
	weaponsMenu.AddElement(autoAim);
	weaponsMenu.AddElement(aimSpot);
	weaponsMenu.AddElement(speedReload);
	weaponsMenu.AddElement(shootTarget);
	weaponsMenu.AddElement(recoilCap);
	weaponsMenu.AddElement(aimPred);
	weaponsMenu.AddElement(autoFire);
	weaponsMenu.AddElement(triggerBot);

	//Others menu
	CMenuElem bunnyHop("Bunny Hop", ELEM_VALUE, &cvar.bunnyhop);
	CMenuElem spinBot("Spin Bot", ELEM_VALUE, &cvar.spinbot);
	CMenuElem speedHack("Speedhack", ELEM_VALUE, &cvar.speed);
	speedHack.SetMaximumValue(2.0f);

	CMenuElem othersMenu("Fun Shit", ELEM_SUBMENU, NULL);
	othersMenu.AddElement(bunnyHop);
	othersMenu.AddElement(spinBot);
	othersMenu.AddElement(speedHack);

	//Add all elements to basemenu-------------------------------
	gMenu.Initialize();
	gMenu.AddElement(visualsMenu);
	gMenu.AddElement(spreadMenu);
	gMenu.AddElement(weaponsMenu);
	gMenu.AddElement(othersMenu);

	//Debug Menu
	CMenuElem aimTarget("gAimbot.target", ELEM_VALUE, &dvar.aimtarget);

	gDebug.Initialize();
	gDebug.AddElement(aimTarget);

	pEngfuncs->Con_Printf("minihook-ng loaded.\n");
	return retval;
}

//=========================
// HUD_Init
// 
// Called whenever the client connects
// to a server.  Reinitializes all 
// the hud variables.
//=========================
void HUD_Init( void )
{
	gClientDll.HUD_Init();
	gEngfuncs.pfnClientCmd("unbind ins");
	gEngfuncs.pfnClientCmd("unbind del");
}

//=========================
// HUD_VidInit
// 
// Called when the game initializes
// and whenever the vid_mode is changed
// so the HUD can reinitialize itself.
//=========================
int HUD_VidInit( void )
{
	return gClientDll.HUD_VidInit();
}

//=========================
// DrawingDraw
// 
// called in HUD_Redraw to
// draw things using the
// Drawing* functions
//==========================
void DrawingDraw(void)
{
	if(cvar.bone) {
		float screen[2];
		for(int i = 0; i < MAX_VPLAYERS; i++) {
			int j = (int)cvar.bone;
			for(int j = 0; j < vPlayers[i].numTargetSpots; j++) {
				if(CalcScreen(vPlayers[i].TargetSpots[j], screen)) {
					if(vPlayers[i].team == TEAM_TERROR) {
						DrawingSetColor(255, 0, 0, 255);
					}
					else if(vPlayers[i].team == TEAM_CT) {
						DrawingSetColor(0, 0, 255, 255);
					}
					if(j == BONE_HEAD)
					{
						DrawingSetColor(0, 255, 0, 255);
						DrawingDrawCircle(screen[0], screen[1], 2);
					}
					else
					{
						DrawingDrawCircle(screen[0], screen[1], 1);
					}
				}
			}
		}
	}

	if(cvar.crosshair) {
		int velfactor = (int)VectorLength(me.pmVelocity)/50.0f;
		int recfactor = me.spread.recoil;
		if(recfactor > 10)
			recfactor = 10;
		int offset = velfactor + recfactor;

		DrawingSetColor(255, 0, 0, 255);
		switch((int)cvar.crosshair) {
		case 1: {
			DrawingDrawLine(m_iCenterX-9, m_iCenterY+1, m_iCenterX+10, m_iCenterY+1);
			DrawingDrawLine(m_iCenterX+1, m_iCenterY-10, m_iCenterX+1, m_iCenterY+10);
			break;
				}

		case 2: {
			DrawingDrawLine(m_iCenterX-9-offset, m_iCenterY+1, m_iCenterX-offset, m_iCenterY+1);
			DrawingDrawLine(m_iCenterX+offset, m_iCenterY+1, m_iCenterX+9+offset, m_iCenterY+1);
			DrawingDrawLine(m_iCenterX+1, m_iCenterY-10-offset, m_iCenterX+1, m_iCenterY-offset);
			DrawingDrawLine(m_iCenterX+1, m_iCenterY+offset, m_iCenterX+1, m_iCenterY+10+offset);
				}

		default:
			break;
		}
	}
}

void DrawSpread()
{
	vec3_t spreadangles;
	vec3_t forward;
	vec3_t eyepos;
	vec3_t screen;

	if(cvar.drawspread && me.weapon)
	{
		pmtrace_t tr;
		VectorAdd(me.viewAngles, me.spread.drawangles, spreadangles);

		gEngfuncs.pfnAngleVectors(me.viewAngles, forward, NULL, NULL);

		gEngfuncs.pEventAPI->EV_SetTraceHull(2);
		eyepos = me.pmEyePos;
		gEngfuncs.pEventAPI->EV_PlayerTrace(eyepos, eyepos + (forward * playerItems.CurDistance()),PM_GLASS_IGNORE, -1, &tr);

		CalcScreen(tr.endpos, screen);

		DrawingBegin();
		DrawingSetColor(255, 0, 0, 255);
		DrawingDrawCircle(screen.x-1, screen.y-1, 3);
		DrawingEnd();
	}
}

//=========================
// HUD_Redraw
// 
// called every screen frame to
// redraw the HUD.
//==========================
int HUD_Redraw( float time, int intermission )
{
	int Result = gClientDll.HUD_Redraw(time, intermission);
	updateLocalPlayer();

	if(cvar.aim && me.alive)
	{
		if(gAimbot.target != BAD_TARGET)
		{
			// silent aim is number two
			if(cvar.aim != 2.0f) gEngfuncs.SetViewAngles(gAimbot.targetAngles);
		}
	}

	//DrawSpread();

	DrawingBegin();
	DrawingDraw();
	DrawingEnd();

	CMenuDraw::Draw(gMenu, 100, 100);
	CMenuDraw::Draw(gDebug, 400, 100);

	//vPlayers.ClearTargetSpots();
	return Result;
}

//=========================
// HUD_UpdateClientData
// 
// called every time shared client
// dll/engine data gets changed,
// and gives the cdll a chance
// to modify the data.
// 
// returns 1 if anything has been changed, 0 otherwise.
//=========================
int HUD_UpdateClientData(client_data_t *pcldata, float flTime )
{
	if(pcldata)
		WeaponListUpdate(pcldata->iWeaponBits);

	return gClientDll.HUD_UpdateClientData(pcldata, flTime);
}

//=========================
// HUD_Reset
// 
// Called at start and end of demos to restore to "non"HUD state.
//=========================
void HUD_Reset( void )
{
	return gClientDll.HUD_Reset();
}

//==========
// HUD_PlayerMoveInit
//==========
void HUD_PlayerMoveInit( struct playermove_s *ppmove )
{
	InitTextureTypes(ppmove);
	return gClientDll.HUD_PlayerMoveInit(ppmove);
}

//==========
// HUD_PlayerMoveTexture
//==========
char HUD_PlayerMoveTexture( char *name )
{
	return gClientDll.HUD_PlayerMoveTexture(name);
}	

//==========
// HUD_PlayerMove
//==========
void HUD_PlayerMove( struct playermove_s *ppmove, int server )
{
	me.pmFlags = ppmove->flags;
	me.pmMoveType = ppmove->movetype;
	VectorCopy(ppmove->velocity,me.pmVelocity);

	// copy origin+angles
	gEngfuncs.pEventAPI->EV_LocalPlayerViewheight(me.pmEyePos);

	me.pmEyePos[0] += ppmove->origin[0];
	me.pmEyePos[1] += ppmove->origin[1];
	me.pmEyePos[2] += ppmove->origin[2];

	me.viewAngles[0] = ppmove->angles[0];
	me.viewAngles[1] = ppmove->angles[1];
	me.viewAngles[2] = ppmove->angles[2];

	return gClientDll.HUD_PlayerMove(ppmove, server);
}

//==========
// IN_ActivateMouse
//==========
void IN_ActivateMouse (void)
{
	return gClientDll.IN_ActivateMouse();
}

//==========
// IN_DeactivateMouse
//==========
void IN_DeactivateMouse (void)
{
	return gClientDll.IN_DeactivateMouse();
}

//==========
// IN_MouseEvent
//==========
void IN_MouseEvent (int mstate)
{
	return gClientDll.IN_MouseEvent(mstate);
}

//==========
// IN_Accumulate
//==========
void IN_Accumulate (void)
{
	return gClientDll.IN_Accumulate();
}

//==================
// IN_ClearStates
//==================
void IN_ClearStates (void)
{
	return gClientDll.IN_ClearStates();
}


void FixupAngleDifference(usercmd_t *cmd, usercmd_t &OriginalCmd)
{
	// thanks tetsuo for this copy/paste
	cl_entity_t *pLocal;
	Vector viewforward, viewright, viewup, aimforward, aimright, aimup, vTemp;
	float newforward, newright, newup, newmagnitude, fTime;
	float forward = OriginalCmd.forwardmove;
	float right = OriginalCmd.sidemove;
	float up = OriginalCmd.upmove;

	pLocal = gEngfuncs.GetLocalPlayer();
	if(!pLocal)
		return;

	// this branch makes sure your horizontal velocity is not affected when fixing up the movement angles -- it isn't specific to spinning and you can use it with the source tetsuo posted in his forum too
	if(pLocal->curstate.movetype == MOVETYPE_WALK)
	{
		gEngfuncs.pfnAngleVectors(Vector(0.0f, OriginalCmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	}
	else
	{
		gEngfuncs.pfnAngleVectors(OriginalCmd.viewangles, viewforward, viewright, viewup);
	}

	// this branch makes sure your horizontal velocity is not affected when fixing up the movement angles -- it isn't specific to spinning and you can use it with the source tetsuo posted in his forum too
	if(pLocal->curstate.movetype == MOVETYPE_WALK)
	{
		gEngfuncs.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	}
	else
	{
		gEngfuncs.pfnAngleVectors(cmd->viewangles, aimforward, aimright, aimup);
	}

	newforward = DotProduct(forward * viewforward.Normalize(), aimforward) + DotProduct(right * viewright.Normalize(), aimforward) + DotProduct(up * viewup.Normalize(), aimforward);
	newright = DotProduct(forward * viewforward.Normalize(), aimright) + DotProduct(right * viewright.Normalize(), aimright) + DotProduct(up * viewup.Normalize(), aimright);
	newup = DotProduct(forward * viewforward.Normalize(), aimup) + DotProduct(right * viewright.Normalize(), aimup) + DotProduct(up * viewup.Normalize(), aimup);

	cmd->forwardmove = newforward;
	cmd->sidemove = newright;
	cmd->upmove = newup;
}  

void do_triggerbot( struct usercmd_s* cmd, bool canattack, float* aim, float* spread, float* recoil )
{
	//trigger bot
	if(cvar.triggerbot && me.weapon && canattack)
	{
		//todo: fix triggerbot to shoot normally when nospread/norecoil is on
		vec3_t vTrace;
		float distance = playerItems.CurDistance();
		float flShot[3],flForward[3];

		flShot[0] = aim[0] - spread[0] + recoil[0];
		flShot[1] = aim[1] - spread[1] + recoil[1];
		flShot[2] = aim[2] - spread[2] + recoil[2];

		gEngfuncs.pfnAngleVectors(flShot, flForward, NULL, NULL);

		vTrace[0] = me.pmEyePos[0] + flForward[0] * distance;
		vTrace[1] = me.pmEyePos[1] + flForward[1] * distance;
		vTrace[2] = me.pmEyePos[2] + flForward[2] * distance;

		int entIgnore = -1;
		bool wall = false;

		if(cvar.triggerbot == 2.0f)
		{
			entIgnore = 0;
			wall = true;
		}

		pmtrace_t tr;

		gEngfuncs.pEventAPI->EV_SetTraceHull(2);
		gEngfuncs.pEventAPI->EV_PlayerTrace(me.pmEyePos, vTrace, PM_TRACELINE_PHYSENTSONLY, entIgnore, &tr);

		int iEnt = gEngfuncs.pEventAPI->EV_IndexFromTrace(&tr);

		cl_entity_s *ent = gEngfuncs.GetEntityByIndex(iEnt);

		if ( ValidTarget(ent))
		{
			int damage = 1;
			if(wall)
			{
				damage = CanPenetrate(me.pmEyePos, tr.endpos, 
					playerItems.CurDistance(), 
					playerItems.CurPenetration(),
					playerItems.CurBulletType(),
					playerItems.CurDamage(),
					playerItems.CurWallPierce()
					);
			}

			if(damage > 0)
			{
				cmd->buttons |= IN_ATTACK;
			}
		}
	}
}

//===============
// CL_CreateMove
// 
// Send the intended movement message to the server
// if active == 1 then we are 1) not playing back demos ( where our commands are ignored ) and
// 2 ) we have finished signing on to server
//===============
double keyspeed = 0.0;
void CL_CreateMove ( float frametime, struct usercmd_s *cmd, int active )
{	
	struct usercmd_s g_OriginalCmd;

	float outspread[3],outrecoil[3];
	float tmpspread[3], tmprecoil[3];
	float aimangles[3];

	bool canAttack = false;
	bool bAttacking = false;

	gClientDll.CL_CreateMove(frametime, cmd, active);
	me.frametime = frametime;
	memcpy(&g_OriginalCmd,cmd,sizeof(usercmd_s));

	//bunnyhop
	if (cvar.bunnyhop && !( me.pmFlags & FL_ONGROUND ) && me.pmMoveType != 5 )
	{
		if ( cmd->buttons & IN_JUMP )
			cmd->buttons &= ~IN_JUMP;
	}

	if(me.weapon)
	{
		canAttack = (me.weapon->weapondata.m_flNextPrimaryAttack - cmd->msec / 1000) <= 0.0f;
		bAttacking = (cmd->buttons&IN_ATTACK) && canAttack;
	}

	if(cvar.aim && gAimbot.target != BAD_TARGET) {
		VectorCopy(gAimbot.targetAngles, cmd->viewangles);
	}

	//save our aiming angles
	VectorCopy(cmd->viewangles, aimangles);

	// Get nospread and norecoil offsets
	gNoSpread.GetRecoilOffset(me.spread.random_seed,1,cmd->viewangles,me.pmVelocity,tmpspread);
	ApplyNorecoil(me.punchangle,tmprecoil);

	// apply norecoil to the angles if its on
	if(cvar.norecoil)
	{
		VectorCopy(tmprecoil, outrecoil);
		VectorClear(tmprecoil);
	}

	// change triggerbot operation based on the state of nospread
	if(cvar.nospread)
	{
		// we have nospread on, don't take spread into account, recoil was already
		// cleared if it was on
		do_triggerbot(cmd, canAttack, aimangles, vec3_t(0,0,0), tmprecoil);
	}
	else
	{
		// do the triggerbot with recoil and spread compensation
		do_triggerbot(cmd, canAttack, aimangles, tmpspread, tmprecoil);
	}

	if((cvar.shoottarget > 0.0f) && (gAimbot.target != -1)) {
		bool bShoot = true;
		if(cvar.recoilcap > 0.0f) {
			if(me.spread.recoil > (int)cvar.recoilcap) {
				bShoot = false;
			}
		}

		if(bShoot == true && canAttack) {
			cmd->buttons |= IN_ATTACK;
		}
	}

	bAttacking = (cmd->buttons&IN_ATTACK) && canAttack;

	if( ((cvar.nospread == 1.0f) && ((cmd->buttons&IN_ATTACK && CanCurWeaponAttack()) || me.spread.burst) ) || (cvar.nospread == 2.0f) )
	{
		// apply nospread if its on and were shooting or bursting, or if its on constant
		VectorCopy(tmpspread, outspread);
	}

	VectorCopy(aimangles, cmd->viewangles);
	//spin
	if( cvar.spinbot && (!bAttacking) ) {
		//thx tabris
		int iHasShiftHeld = GetAsyncKeyState(VK_LSHIFT);
		if(me.pmMoveType == MOVETYPE_WALK && !iHasShiftHeld && !(cmd->buttons & IN_USE))
		{
			cmd->viewangles.y = fmod(gEngfuncs.GetClientTime() * 2.0f * 360.0f, 360.0f);
		} 
	}

	if(cvar.autofire) {
		if(bAttacking) {
			cmd->buttons |= IN_ATTACK;
		} else {
			cmd->buttons &= ~IN_ATTACK;
		}
	}


	// autoreload if we dryfirin'
	if( (me.weapon) && (me.weapon->CAmmo == 0) && (cmd->buttons&IN_ATTACK))
	{
		cmd->buttons &= ~IN_ATTACK;
		cmd->buttons |= IN_RELOAD;
	}

	int sequence = Cstrike_SequenceInfo[gEngfuncs.GetEntityByIndex(me.entindex)->curstate.sequence];
	double speed = 1.0;
	speed += keyspeed;

	if(cvar.speedreload && sequence == SEQUENCE_RELOAD) {
		speed = 100.0;
	}

	if(cvar.speed)
	{
		if(cvar.speed == 1.0)
		{
			speed = 100.0;
		}
		else if(cvar.speed == 2.0)
		{
			if(GetAsyncKeyState(VK_MBUTTON))
			{
				speed = 100.0;
			}
		}
	}

	if(speed != 1.0) {
		AdjustSpeed(speed);
	}
	else {
		if(*pGlobalSpeed != 1000.0) {
			DefaultSpeed();
		}
	}

	//me.spread.drawangles[0] = outrecoil[0] - outspread[0];
	//me.spread.drawangles[1] = outrecoil[1] - outspread[1];

	if(cvar.novisrecoil)
	{
		me.spread.visangles[0] = outspread[0] - (outrecoil[0]/2.0f);
		me.spread.visangles[1] = outspread[1] - (outrecoil[1]/2.0f);
	}
	else
	{
		me.spread.visangles[0] = outspread[0] - outrecoil[0];
		me.spread.visangles[1] = outspread[1] - outrecoil[1];
	}

	if((cvar.aim == 2.0f) && (gAimbot.target != BAD_TARGET))
	{
		me.spread.visangles[0] += (aimangles[0] - g_OriginalCmd.viewangles[0]);
		me.spread.visangles[1] += (aimangles[1] - g_OriginalCmd.viewangles[1]);
	}

	VectorAdd(cmd->viewangles, outspread, cmd->viewangles);
	VectorSubtract(cmd->viewangles, outrecoil, cmd->viewangles);


	/*Fix walkvectors when doing spinbot and nospread/norecoil.
	Nospread on guns like AWP can affect the viewangles so much
	that when you walk forward it looks like you are drunk without
	this fix. */
	FixupAngleDifference(cmd, g_OriginalCmd);
}

//==================
// CL_IsThirdPerson
//==================
int CL_IsThirdPerson( void )
{
	return gClientDll.CL_IsThirdPerson();
}

//==================
// CL_CameraOffset
//==================
void CL_CameraOffset( float *ofs )
{
	return gClientDll.CL_CameraOffset(ofs);
}

//===========
// KB_Find
// 
// Allows the engine to get a kbutton_t directly ( so it can check +mlook state, etc ) for saving out to .cfg files
//===========
struct kbutton_s *KB_Find( const char *name )
{
	return gClientDll.KB_Find(name);
}

//=================
// CAM_Think
//=================
void CAM_Think( void )
{
	return gClientDll.CAM_Think();
}

//=================
// V_CalcRefdef
//=================
void V_CalcRefdef( struct ref_params_s *pparams )
{
	if( pparams->nextView == 0 )
	{
		// recoil
		VectorCopy(me.punchangle, me.lastpunch);
		VectorCopy(pparams->punchangle,me.punchangle);

		//visual norecoil
		if(cvar.novisrecoil) {
			pparams->punchangle[0] = 0;
			pparams->punchangle[1] = 0;
			pparams->punchangle[2] = 0;  
		}

		if(!me.alive)
		{
			// avoid problems with free chase cam view
			// where me.pmOrigin is the viewed player
			VectorCopy(pparams->vieworg,me.pmEyePos);
			gAimbot.target = BAD_TARGET;
		}

		if(cvar.aim && me.alive)
		{
			gAimbot.FindTarget();
			dvar.aimtarget = gAimbot.target;
		}
		vPlayers.ClearTargetSpots();

	}
	gClientDll.V_CalcRefdef(pparams);
	//	VectorCopy(pparams->viewangles, viewangles);
	//	VectorCopy(pparams->vieworg, vieworg);
}

static void AddEntityPlayer(struct cl_entity_s *ent)
{
	int px = ent->index;

	if(ent->curstate.solid) { vPlayers[px].setAlive(); }
	else { vPlayers[px].setDead(); }

	// filter local player out out and set me.alive
	if(ent->index == me.entindex) 
	{ 
		me.alive = vPlayers[px].isAlive();

		vPlayers[px].distance = 100000.0;
		vPlayers[px].visible  = false;
		vPlayers[px].fovangle = 360;
		vPlayers[px].points   = -999999;
		vPlayers[px].updateClear(); 
		return;
	}
	// filter trash entities
	if( !isFakePlayer(px,ent) && vPlayers[px].isAlive() )
	{
		vPlayers[px].updateAddEntity(ent->origin);

		playerCalcExtraData(px,ent);
		//playerRenderOptions(ent);

		ent->curstate.rendermode = 0; // fix render mode
	}
}

//=======================
// HUD_AddEntity
// 	Return 0 to filter entity from visible list for rendering
//=======================
int HUD_AddEntity( int type, struct cl_entity_s *ent, const char *modelname )
{
	if( ent->player) { AddEntityPlayer(ent); }
	return gClientDll.HUD_AddEntity(type, ent, modelname);
}


//========================
// HUD_CreateEntities
// 	
// Gives us a chance to add additional entities to the render this frame
//========================
void HUD_CreateEntities( void )
{
	return gClientDll.HUD_CreateEntities();
}


//================
// HUD_DrawNormalTriangles
// 
// Non-transparent triangles-- add them here
//================
void HUD_DrawNormalTriangles( void )
{
	return gClientDll.HUD_DrawNormalTriangles();
}


//================
// HUD_DrawTransparentTriangles
// 
// Render any triangles with transparent rendermode needs here
//================
void HUD_DrawTransparentTriangles( void )
{
	return gClientDll.HUD_DrawTransparentTriangles();
}

//========================
// HUD_StudioEvent
// 
// The entity's studio model description indicated an event was
// fired during this frame, handle the event by it's tag ( e.g., muzzleflash, sound )
//========================
void HUD_StudioEvent( const struct mstudioevent_s *pevent, const struct cl_entity_s *entity )
{
	return gClientDll.HUD_StudioEvent(pevent, entity);
}

//====================
// HUD_PostRunCmd
// 
// Client calls this during prediction, after it has moved the player and updated any info changed into to->
// time is the current client clock based on prediction
// cmd is the command that caused the movement, etc
// runfuncs is 1 if this is the first time we've predicted this command.  If so, sounds and effects should play, otherwise, they should
// be ignored
//====================
void HUD_PostRunCmd( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed )
{
	gClientDll.HUD_PostRunCmd(from, to, cmd, runfuncs, time, random_seed);
	gNoSpread.HUD_PostRunCmd(from,to,cmd,runfuncs,time,random_seed);
}

//====================
// HUD_PostRunCmd
//====================
void HUD_Shutdown( void )
{
	return gClientDll.HUD_Shutdown();
}

//========================
// HUD_TxferLocalOverrides
// 
// The server sends us our origin with extra precision as part of the clientdata structure, not during the normal
// playerstate update in entity_state_t.  In order for these overrides to eventually get to the appropriate playerstate
// structure, we need to copy them into the state structure at this point.
//========================
void HUD_TxferLocalOverrides( struct entity_state_s *state, const struct clientdata_s *client )
{
	return gClientDll.HUD_TxferLocalOverrides(state, client);
}

//========================
// HUD_ProcessPlayerState
// 
// We have received entity_state_t for this player over the network.  We need to copy appropriate fields to the
// playerstate structure
//========================
void HUD_ProcessPlayerState( struct entity_state_s *dst, const struct entity_state_s *src )
{
	return gClientDll.HUD_ProcessPlayerState(dst, src);
}

//========================
// HUD_TxferPredictionData

// Because we can predict an arbitrary number of frames before the server responds with an update, we need to be able to copy client side prediction data in
// from the state that the server ack'd receiving, which can be anywhere along the predicted frame path ( i.e., we could predict 20 frames into the future and the server ack's
// up through 10 of those frames, so we need to copy persistent client-side only state from the 10th predicted frame to the slot the server
// update is occupying.
//========================
void HUD_TxferPredictionData ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd )
{
	return gClientDll.HUD_TxferPredictionData(ps, pps, pcd, ppcd, wd, pwd);
}

//====================
// Demo_ReadBuffer
// 
// Engine wants us to parse some data from the demo stream
//====================
void Demo_ReadBuffer( int size, unsigned char *buffer )
{
	return gClientDll.Demo_ReadBuffer(size, buffer);
}

//===============================
// HUD_ConnectionlessPacket
// 
// Return 1 if the packet is valid.  Set response_buffer_size if you want to send a response packet.  Incoming, it holds the max
//  size of the response_buffer, so you must zero it out if you choose not to respond.
//===============================
int	HUD_ConnectionlessPacket( const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size )
{
	return gClientDll.HUD_ConnectionlessPacket(net_from, args, response_buffer, response_buffer_size);
}

//===============================
// HUD_GetHullBounds
// 
//  Engine calls this to enumerate player collision hulls, for prediction.  Return 0 if the hullnumber doesn't exist.
//===============================
int HUD_GetHullBounds( int hullnumber, float *mins, float *maxs )
{
	return gClientDll.HUD_GetHullBounds(hullnumber, mins, maxs);
}

//=========================
// HUD_Frame
// 
// Called by engine every frame that client .dll is loaded
//=========================
void HUD_Frame( double time )
{
	return gClientDll.HUD_Frame(time);
}

//===========
// HUD_Key_Event
// 
// Return 1 to allow engine to process the key, otherwise, act on it as needed
//===========
int HUD_Key_Event( int down, int keynum, const char *pszCurrentBinding )
{
	if( (keynum == K_HOME) && down )
	{
		gDebug.bShow = !gDebug.bShow;
		return 0;
	}
	
	if((keynum == K_DEL) && down) {
		togglePanic();
		return 0;
	}

	if(CMenuControl::HUD_Key_Event(down, keynum, pszCurrentBinding)) {
		return gClientDll.HUD_Key_Event(down, keynum, pszCurrentBinding);
	}

	return 0;
}

//================
// CL_UpdateTEnts
// 
// Simulation and cleanup of temporary entities
//================
void HUD_TempEntUpdate (double frametime, double client_time, double cl_gravity, TEMPENTITY **ppTempEntFree, TEMPENTITY **ppTempEntActive, int ( *Callback_AddVisibleEntity )( cl_entity_t *pEntity ), void ( *Callback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ) )
{
	if(cvar.light)
	{
		if(me.alive)
		{
			dlight_t	*dl		= gEngfuncs.pEfxAPI->CL_AllocDlight(0);

			if(me.team==TEAM_TERROR)//if the player is in team 1 (T)
			{
				dl->color.r = 255; //assign these colors
				dl->color.g = 50;
				dl->color.b = 50;
			}
			if(me.team==TEAM_CT)//if the player is on team2 (CT)
			{
				dl->color.r = 50; //assign these colors
				dl->color.g = 50;
				dl->color.b = 255;
			}
			dl->origin	=	me.pmEyePos; // this is the origin (location of the players)
			dl->radius	=	150; //radius of the light
			dl->die		=	client_time + 0.01; //after how long the light gets killed.
		}

	}
	if(cvar.tlight)
	{
		if((gAimbot.target != BAD_TARGET) && cvar.aim)
		{
			dlight_t	*dl		= gEngfuncs.pEfxAPI->CL_AllocDlight(0);
			PlayerInfo&  target = vPlayers[gAimbot.target];

			if(target.team==TEAM_TERROR)//if the player is in team 1 (T)
			{
				dl->color.r = 255; //assign these colors
				dl->color.g = 50;
				dl->color.b = 50;
			}
			if(target.team==TEAM_CT)//if the player is on team2 (CT)
			{
				dl->color.r = 50; //assign these colors
				dl->color.g = 50;
				dl->color.b = 255;
			}

			dl->origin	=	target.origin(); // this is the origin (location of the players)
			dl->radius	=	150; //radius of the light
			dl->die		=	client_time + 0.01; //after how long the light gets killed.
		}
	}
	ClientTime::reportMapTime(client_time);
	return gClientDll.HUD_TempEntUpdate(frametime, client_time, cl_gravity, ppTempEntFree, ppTempEntActive, Callback_AddVisibleEntity, Callback_TempEntPlaySound);
}

//================
// HUD_GetUserEntity
// 
// If you specify negative numbers for beam start and end point entities, then
//  the engine will call back into this function requesting a pointer to a cl_entity_t 
//  object that describes the entity to attach the beam onto.
// 
// Indices must start at 1, not zero.
//================
cl_entity_t *HUD_GetUserEntity( int index )
{
	return gClientDll.HUD_GetUserEntity(index);
}

//=========================
// HUD_VoiceStatus
// 
// Called when a player starts or stops talking.
//=========================
void HUD_VoiceStatus(int entindex, qboolean bTalking)
{
	return gClientDll.HUD_VoiceStatus(entindex, bTalking);
}

//=========================
// HUD_DirectorEvent
// 
// Called when a director event message was received
//=========================

//===================
// HUD_GetStudioModelInterface
// 
// Export this function for the engine to use the studio renderer class to render objects.
//===================
int HUD_GetStudioModelInterface( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio )
{
	return gClientDll.HUD_GetStudioModelInterface(version, ppinterface, pstudio);
}