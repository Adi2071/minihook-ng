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

using namespace std;

local_player_info me;
VecPlayers vPlayers;

cvar_t* recoilVar1 = NULL;
cvar_t* recoilVar2 = NULL;

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
	case kRenderTransColor:
	case kRenderTransTexture: 
		if( ent->curstate.renderamt<128 ) { return true;  }
		else                              { return false; }
	case kRenderNormal: { return false; }
	default:            { return true;  }
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

void playerLights()
{
	for (int ax=0;ax<vPlayers.size();ax++)
	{
		cl_entity_t	*mee		= gEngfuncs.GetLocalPlayer();
        cl_entity_t *ent	= gEngfuncs.GetEntityByIndex(ax);
		dlight_t	*dl		= gEngfuncs.pEfxAPI->CL_AllocDlight(0);

		int px = ax;

		if(vPlayers[px].isAlive() && vPlayers[px].isUpdated())//if the player is alive
		{
			if(mee->index == ent->index) //Check if the player is you
			{continue;} //if it is, continue without drawing the light.
			
			if(vPlayers[px].team==1)//if the player is in team 1 (T)
			{
				dl->color.r = 255; //assign these colors
				dl->color.g = 50;
				dl->color.b = 50;
			}
			if(vPlayers[px].team==2)//if the player is on team2 (CT)
			{
				dl->color.r = 50; //assign these colors
				dl->color.g = 50;
				dl->color.b = 255;
			}
			
			dl->origin	=	vPlayers[px].origin(); // this is the origin (location of the players)
			dl->radius	=	200; //radius of the light
			dl->die		=	gEngfuncs.GetClientTime() + 0.2; //after how long the light gets killed.
		}
	}
}

//========================= 
// Initialize
// 
// Called when the DLL is first loaded.
//=========================
int Initialize( cl_enginefunc_t *pEnginefuncs, int iVersion )
{
	SCREENINFO si;
	si.iSize = sizeof(SCREENINFO);
	gEngfuncs.pfnGetScreenInfo(&si);

	m_iCenterX = si.iWidth / 2;
	m_iCenterY = si.iHeight / 2;

	//Visuals menu-------------------------------
	CMenuElem crosshair("Crosshair", ELEM_VALUE, &cvar.crosshair);
	crosshair.SetMaximumValue(2.0f);
	CMenuElem dlightFollow("PlayerLights", ELEM_VALUE, &cvar.dlightfollow);
	CMenuElem showBone("Show Bones", ELEM_VALUE, &cvar.bone);


	CMenuElem visualsMenu("Visuals", ELEM_SUBMENU, NULL);
	visualsMenu.AddElement(crosshair);
	visualsMenu.AddElement(dlightFollow);
	visualsMenu.AddElement(showBone);
	

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
	CMenuElem zoomAll("Zoom All Weapons", ELEM_VALUE, &cvar.zoomall);
	CMenuElem autoFire("Autofire", ELEM_VALUE, &cvar.autofire);

	CMenuElem weaponsMenu("Weapon Stuff", ELEM_SUBMENU, NULL);
	weaponsMenu.AddElement(zoomAll);
	weaponsMenu.AddElement(autoFire);

	//Others menu
	CMenuElem bunnyHop("Bunny Hop", ELEM_VALUE, &cvar.bunnyhop);
	CMenuElem spinBot("Spin Bot", ELEM_VALUE, &cvar.spinbot);

	CMenuElem othersMenu("Others", ELEM_SUBMENU, NULL);
	othersMenu.AddElement(bunnyHop);
	othersMenu.AddElement(spinBot);

	//Add all elements to basemenu-------------------------------
	gMenu.Initialize();
	gMenu.AddElement(visualsMenu);
	gMenu.AddElement(spreadMenu);
	gMenu.AddElement(weaponsMenu);
	gMenu.AddElement(othersMenu);

	//Cvars-------------------------------
	recoilVar1 = gEngfuncs.pfnRegisterVariable("mini_recoilvar1", "20", FCVAR_SERVER);
	recoilVar2 = gEngfuncs.pfnRegisterVariable("mini_recoilvar2", "-35", FCVAR_SERVER);

	return gClientDll.Initialize(pEnginefuncs, iVersion);
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

	return gClientDll.HUD_Init();
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

	if(cvar.bone) {
		float screen[2];
		for(int i = 0; i < MAX_VPLAYERS; i++) {
			for(int j = 0; j < vPlayers[i].numTargetSpots; j++) {
				if(CalcScreen(vPlayers[i].TargetSpots[j], screen)) {
					if(vPlayers[i].team == TEAM_TERROR) {
						DrawingSetColor(255, 0, 0, 255);
					}
					else if(vPlayers[i].team == TEAM_CT) {
						DrawingSetColor(0, 0, 255, 255);
					}
					DrawingDrawCircle(screen[0], screen[1], 2);
				}
			}
		}
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

	if(cvar.dlightfollow) {
		playerLights();
	}

	DrawingBegin();
	DrawingDraw();
	DrawingEnd();

	CMenuDraw::Draw(gMenu, 100, 100);
	
	vPlayers.ClearTargetSpots();
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

//===============
// CL_CreateMove
// 
// Send the intended movement message to the server
// if active == 1 then we are 1) not playing back demos ( where our commands are ignored ) and
// 2 ) we have finished signing on to server
//===============
void CL_CreateMove ( float frametime, struct usercmd_s *cmd, int active )
{	
	vec3_t outspread,outrecoil;
	struct usercmd_s g_OriginalCmd;

	gClientDll.CL_CreateMove(frametime, cmd, active);

	me.frametime = frametime;

	memcpy(&g_OriginalCmd,cmd,sizeof(usercmd_s));

	//bunnyhop
	if (cvar.bunnyhop && !( me.pmFlags & FL_ONGROUND ) && me.pmMoveType != 5 )
	{
		if ( cmd->buttons & IN_JUMP )
			cmd->buttons &= ~IN_JUMP;
	}
	bool bAttacking = false;
	if(GetCurWeapon()) {
		bAttacking = cmd->buttons&IN_ATTACK && ((GetCurWeapon()->weapondata.m_flNextPrimaryAttack - cmd->msec / 1000) <= 0.0f);
		if(cvar.autofire) {
			if(bAttacking) {
				cmd->buttons &= IN_ATTACK;
			} else {
				cmd->buttons &= ~IN_ATTACK;
			}
		}
	}

	//spin
	if(!bAttacking && cvar.spinbot) {
		//thx tabris
		int iHasShiftHeld = GetAsyncKeyState(VK_LSHIFT);
		if(me.pmMoveType == MOVETYPE_WALK && !iHasShiftHeld && !(cmd->buttons & IN_USE))
		{
			cmd->viewangles.y = fmod(gEngfuncs.GetClientTime() * 5.0f * 360.0f, 360.0f);
		} 
	}

	if(cvar.norecoil)// && !IsCurWeaponSec())
		ApplyNorecoil(frametime,me.punchangle,outrecoil);

	if((cmd->buttons & IN_ATTACK && CanCurWeaponAttack() && cvar.nospread == 1.0f) || cvar.nospread == 2.0f)
	{
		gNoSpread.GetRecoilOffset(me.spread.random_seed,1,cmd->viewangles,me.pmVelocity,outspread);
	}

	newangles[0] = outspread[0] - outrecoil[0];
	newangles[1] = outspread[1] - outrecoil[1];

	cmd->viewangles[0] += newangles[0];
	cmd->viewangles[1] += newangles[1];

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
		}
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