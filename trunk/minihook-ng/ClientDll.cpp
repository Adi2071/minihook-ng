#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"
#include "Calculations.h"
#include "Drawing.h"

#include "MenuElem.h"
#include "MenuDraw.h"

//========================= 
// Initialize
// 
// Called when the DLL is first loaded.
//=========================
int Initialize( cl_enginefunc_t *pEnginefuncs, int iVersion )
{
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
// HUD_Redraw
// 
// called every screen frame to
// redraw the HUD.
//==========================
int HUD_Redraw( float time, int intermission )
{
	int Result = gClientDll.HUD_Redraw(time, intermission);
	CMenuDraw::Draw(gMenu, 0, 0);
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

//===============
// CL_CreateMove
// 
// Send the intended movement message to the server
// if active == 1 then we are 1) not playing back demos ( where our commands are ignored ) and
// 2 ) we have finished signing on to server
//===============
void CL_CreateMove ( float frametime, struct usercmd_s *cmd, int active )
{	
	return gClientDll.CL_CreateMove(frametime, cmd, active);
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
	gClientDll.V_CalcRefdef(pparams);
	VectorCopy(pparams->viewangles, viewangles);
	VectorCopy(pparams->vieworg, vieworg);
}

//=======================
// HUD_AddEntity
// 	Return 0 to filter entity from visible list for rendering
//=======================
int HUD_AddEntity( int type, struct cl_entity_s *ent, const char *modelname )
{
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
	return gClientDll.HUD_PostRunCmd(from, to, cmd, runfuncs, time, random_seed);
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
	return gClientDll.HUD_Key_Event(down, keynum, pszCurrentBinding);
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