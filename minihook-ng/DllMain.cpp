#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include "Detour.h"
#include "ModuleSecurity.h"
#include "OffsetScan.h"
#include "SDKInclude.h"
#include "TransInclude.h"
#include "util.h"

// engine structure copies for global usage
StudioModelRenderer_t	gStudioModelRenderer;
ClientDll_t				gClientDll;
cl_enginefunc_t			gEngfuncs;
engine_studio_api_t		gStudio;

// engine structure pointers for hooking
StudioModelRenderer_t*	pStudioModelRenderer;
ClientDll_t*			pClientDll;
cl_enginefunc_t*		pEngfuncs;
engine_studio_api_t*	pStudio;
PVOID					pPreS_DynamicSound;

// exception handlers
HANDLE PreSHandler;

//===========================
// AddCommand
// Temporary cl_enginefuncs_s::AddCommand
//===========================
int AddCommand ( char *cmd_name, void (*function)(void) )
{
	return 0;
}

//===========================
// RegisterVariable
// Temporary cl_enginefuncs_s::pfnRegisterVariable
//===========================
cvar_t* RegisterVariable ( char *szName, char *szValue, int flags )
{
	cvar_t* pResult = gEngfuncs.pfnGetCvarPointer(szName);
	if(pResult != NULL)
		return pResult;

	return gEngfuncs.pfnRegisterVariable(szName, szValue, flags);
}

//===========================
// HookEvent
// Temporary cl_enginefuncs_s::pfnHookEvent
//===========================
void HookEvent (char *szName, void ( *pfnEvent )( struct event_args_s *args ))
{
	#define HOOK_EVENT(n) if (!strcmp(Name, #n)) { p##n = pfnEvent; return gEngfuncs.pfnHookEvent(szName, h##n); }

	char Name[200];
	strcpy(Name, szName+7);
	Name[strlen(Name)-3] = '\0';
	for(int i=0; i<strlen(Name); i++)
	{
		if(Name[i] == '\\' || Name[i] == ' ' || Name[i] == '/' || Name[i] == '.')
			Name[i] = '_';
	}

	// Counterstrike
	HOOK_EVENT(glock1);
	HOOK_EVENT(glock2);
	HOOK_EVENT(shotgun1);
	HOOK_EVENT(shotgun2);
	HOOK_EVENT(mp5);
	HOOK_EVENT(python);
	HOOK_EVENT(gauss);
	HOOK_EVENT(gaussspin);
	HOOK_EVENT(train);
	HOOK_EVENT(vehicle);
	HOOK_EVENT(usp);
	HOOK_EVENT(mp5n);
	HOOK_EVENT(ak47);
	HOOK_EVENT(aug);
	HOOK_EVENT(deagle);
	HOOK_EVENT(g3sg1);
	HOOK_EVENT(sg550);
	HOOK_EVENT(glock18);
	HOOK_EVENT(m249);
	HOOK_EVENT(m3);
	HOOK_EVENT(m4a1);
	HOOK_EVENT(mac10);
	HOOK_EVENT(p90);
	HOOK_EVENT(p228);
	HOOK_EVENT(awp);
	HOOK_EVENT(scout);
	HOOK_EVENT(sg552);
	HOOK_EVENT(tmp);
	HOOK_EVENT(fiveseven);
	HOOK_EVENT(ump45);
	HOOK_EVENT(xm1014);
	HOOK_EVENT(elite_left);
	HOOK_EVENT(elite_right);
	HOOK_EVENT(knife);
	HOOK_EVENT(galil);
	HOOK_EVENT(famas);
	HOOK_EVENT(decal_reset);
	HOOK_EVENT(createsmoke);
	HOOK_EVENT(createexplo);

	/*// DOD
	HOOK_EVENT(misc_train);
	HOOK_EVENT(weapons_colt);
	HOOK_EVENT(weapons_luger);
	HOOK_EVENT(weapons_m1carbine);
	HOOK_EVENT(weapons_garand);
	HOOK_EVENT(weapons_scopedkar);
	HOOK_EVENT(weapons_thompson);
	HOOK_EVENT(weapons_mp44);
	HOOK_EVENT(weapons_spring);
	HOOK_EVENT(weapons_kar);
	HOOK_EVENT(weapons_mp40);
	HOOK_EVENT(weapons_knife);
	HOOK_EVENT(weapons_bar);
	HOOK_EVENT(weapons_mg42);
	HOOK_EVENT(weapons_mg34);
	HOOK_EVENT(weapons_30cal);
	HOOK_EVENT(weapons_greasegun);
	HOOK_EVENT(weapons_fg42);
	HOOK_EVENT(weapons_k43);
	HOOK_EVENT(weapons_enfield);
	HOOK_EVENT(weapons_sten);
	HOOK_EVENT(weapons_bren);
	HOOK_EVENT(weapons_webley);
	HOOK_EVENT(weapons_scopedenfield);
	HOOK_EVENT(weapons_bazooka);
	HOOK_EVENT(weapons_pschreck);
	HOOK_EVENT(weapons_piat);
	HOOK_EVENT(weapons_mortar);
	HOOK_EVENT(weapons_melee);
	HOOK_EVENT(misc_pain);
	HOOK_EVENT(effects_smoke);
	HOOK_EVENT(effects_blood);
	HOOK_EVENT(effects_bloodstream);
	HOOK_EVENT(effects_tracers);
	HOOK_EVENT(effects_bubbletrails);
	HOOK_EVENT(effects_bubbles);
	HOOK_EVENT(effects_explosion);
	HOOK_EVENT(effects_sparkshower);
	HOOK_EVENT(misc_whizz);
	HOOK_EVENT(misc_usvoice);
	HOOK_EVENT(misc_gervoice);
	HOOK_EVENT(effects_bodydamage);
	HOOK_EVENT(misc_roundrestart);
	HOOK_EVENT(misc_camera);
	HOOK_EVENT(effects_helmet);
	HOOK_EVENT(misc_roundreset);
	HOOK_EVENT(effects_overheat);
	HOOK_EVENT(effects_rockettrail);
	HOOK_EVENT(effects_mortarshell);

	// Deathmatch Classic
	HOOK_EVENT(axe);
	HOOK_EVENT(axeswing);
	HOOK_EVENT(rocket);
	HOOK_EVENT(lightning);
	HOOK_EVENT(grenade);
	HOOK_EVENT(spike);
	HOOK_EVENT(superspike);
	HOOK_EVENT(gibs);
	HOOK_EVENT(teleport);
	HOOK_EVENT(trail);
	HOOK_EVENT(explosion);
	HOOK_EVENT(powerup);
	HOOK_EVENT(door_doorgoup);
	HOOK_EVENT(door_doorgodown);
	HOOK_EVENT(door_doorhittop);
	HOOK_EVENT(door_doorhitbottom);

	// Halflife
	HOOK_EVENT(mp52);
	HOOK_EVENT(crowbar);
	HOOK_EVENT(crossbow1);
	HOOK_EVENT(crossbow2);
	HOOK_EVENT(rpg);
	HOOK_EVENT(egon_fire);
	HOOK_EVENT(egon_stop);
	HOOK_EVENT(firehornet);
	HOOK_EVENT(tripfire);
	HOOK_EVENT(snarkfire);

	// Oposing force
	HOOK_EVENT(egon_effect);
	HOOK_EVENT(eagle);
	HOOK_EVENT(penguinfire);
	HOOK_EVENT(pipewrench);
	HOOK_EVENT(shock);
	HOOK_EVENT(spore);
	HOOK_EVENT(sniper);
	HOOK_EVENT(displacer);

	// Team fortress classic
	HOOK_EVENT(wpn_tf_sniperhit);
	HOOK_EVENT(wpn_tf_sg);
	HOOK_EVENT(wpn_tf_sgreload);
	HOOK_EVENT(wpn_tf_sgpump);
	HOOK_EVENT(wpn_tf_sniper);
	HOOK_EVENT(wpn_tf_ssg);
	HOOK_EVENT(wpn_tf_nail);
	HOOK_EVENT(wpn_tf_snail);
	HOOK_EVENT(wpn_tf_rpg);
	HOOK_EVENT(wpn_tf_ic);
	HOOK_EVENT(wpn_tf_ar);
	HOOK_EVENT(wpn_tf_acwu);
	HOOK_EVENT(wpn_tf_acwd);
	HOOK_EVENT(wpn_tf_acstart);
	HOOK_EVENT(wpn_tf_acfire);
	HOOK_EVENT(wpn_tf_acspin);
	HOOK_EVENT(wpn_tf_acsspin);
	HOOK_EVENT(wpn_tf_flame);
	HOOK_EVENT(wpn_tf_knife);
	HOOK_EVENT(wpn_tf_rail);
	HOOK_EVENT(wpn_tf_tranq);
	HOOK_EVENT(explode_tf_nailgren);
	HOOK_EVENT(wpn_tf_gl);
	HOOK_EVENT(wpn_tf_pipel);
	HOOK_EVENT(wpn_tf_axe);
	HOOK_EVENT(wpn_tf_mednormal);
	HOOK_EVENT(wpn_tf_medsuper);
	HOOK_EVENT(wpn_tf_medsteam);
	HOOK_EVENT(wpn_tf_axedecal);
	HOOK_EVENT(misc_tf_buildingevent);
	HOOK_EVENT(explode_tf_pipe);
	HOOK_EVENT(explode_tf_gren);
	HOOK_EVENT(explode_tf_engrgren);
	HOOK_EVENT(explode_tf_concuss);
	HOOK_EVENT(explode_tf_normalgren);
	HOOK_EVENT(explode_tf_mirvmain);
	HOOK_EVENT(explode_tf_mirv);
	HOOK_EVENT(explode_tf_fire);
	HOOK_EVENT(explode_tf_burn);
	HOOK_EVENT(explode_tf_gas);
	HOOK_EVENT(explode_tf_emp);
	HOOK_EVENT(explode_tf_ng);
	HOOK_EVENT(misc_gibs);
	HOOK_EVENT(misc_benchmark);
	*/

	return gEngfuncs.pfnHookEvent(szName, pfnEvent);
}

//===========================
// HookUserMsg
// Temporary cl_enginefuncs_s::pfnHookUserMsg
//===========================
int HookUserMsg(char *szMsgName, pfnUserMsgHook pfn)
{
	#define HOOK_MSG(n)	if(!stricmp(#n, szMsgName)){p##n = pfn;return gEngfuncs.pfnHookUserMsg(#n, h##n);}

	// Counterstrike
	HOOK_MSG(Logo);
	HOOK_MSG(ResetHUD);
	HOOK_MSG(GameMode);
	HOOK_MSG(InitHUD);
	HOOK_MSG(ViewMode);
	HOOK_MSG(SetFOV);
	HOOK_MSG(HLTV);
	HOOK_MSG(SpecHealth);
	HOOK_MSG(Concuss);
	HOOK_MSG(ReloadSound);
	HOOK_MSG(BombDrop);
	HOOK_MSG(BombPickup);
	HOOK_MSG(ADStop);
	HOOK_MSG(HostagePos);
	HOOK_MSG(HostageK);
	HOOK_MSG(CZCareerHUD);
	HOOK_MSG(ShadowIdx);
	HOOK_MSG(BotVoice);
	HOOK_MSG(Brass);
	HOOK_MSG(Fog);
	HOOK_MSG(ShowTimer);
	HOOK_MSG(TeamNames);
	HOOK_MSG(Feign);
	HOOK_MSG(Detpack);
	HOOK_MSG(MOTD);
	HOOK_MSG(BuildSt);
	HOOK_MSG(RandomPC);
	HOOK_MSG(ServerName);
	HOOK_MSG(ScoreInfo);
	HOOK_MSG(TeamScore);
	HOOK_MSG(TeamInfo);
	HOOK_MSG(Location);
	HOOK_MSG(Spectator);
	HOOK_MSG(AllowSpec);
	HOOK_MSG(ForceCam);
	HOOK_MSG(VGUIMenu);
	HOOK_MSG(TutorText);
	HOOK_MSG(TutorLine);
	HOOK_MSG(TutorState);
	HOOK_MSG(TutorClose);
	HOOK_MSG(BuyClose);
	HOOK_MSG(SpecHealth2);
	HOOK_MSG(BotProgress);
	HOOK_MSG(NVGToggle);
	HOOK_MSG(CurWeapon);
	HOOK_MSG(WeaponList);
	HOOK_MSG(AmmoPickup);
	HOOK_MSG(WeapPickup);
	HOOK_MSG(ItemPickup);
	HOOK_MSG(HideWeapon);
	HOOK_MSG(AmmoX);
	HOOK_MSG(Crosshair);
	HOOK_MSG(Health);
	HOOK_MSG(Damage);
	HOOK_MSG(Radar);
	HOOK_MSG(ScoreAttrib);
	HOOK_MSG(ClCorpse);
	HOOK_MSG(ReceiveW);
	HOOK_MSG(SayText);
	HOOK_MSG(SendAudio);
	HOOK_MSG(Geiger);
	HOOK_MSG(Train);
	HOOK_MSG(Battery);
	HOOK_MSG(ArmorType);
	HOOK_MSG(Flashlight);
	HOOK_MSG(FlashBat);
	HOOK_MSG(HudText);
	HOOK_MSG(HudTextPro);
	HOOK_MSG(HudTextArgs);
	HOOK_MSG(GameTitle);
	HOOK_MSG(StatusText);
	HOOK_MSG(StatusValue);
	HOOK_MSG(DeathMsg);
	HOOK_MSG(SecAmmoVal);
	HOOK_MSG(SecAmmoIcon);
	HOOK_MSG(TextMsg);
	HOOK_MSG(StatusIcon);
	HOOK_MSG(Money);
	HOOK_MSG(BlinkAcct);
	HOOK_MSG(RoundTime);
	HOOK_MSG(BarTime);
	HOOK_MSG(BarTime2);
	HOOK_MSG(TaskTime);
	HOOK_MSG(Scenario);
	HOOK_MSG(ShowMenu);
	HOOK_MSG(VoiceMask);
	HOOK_MSG(ReqState);

	/*// Day of defeat
	HOOK_MSG(YouDied);
	HOOK_MSG(BloodPuff);
	HOOK_MSG(HandSignal);
	HOOK_MSG(UseSound);
	HOOK_MSG(ScoreInfoLong);
	HOOK_MSG(MapMarker);
	HOOK_MSG(WaveTime);
	HOOK_MSG(WaveStatus);
	HOOK_MSG(WideScreen);
	HOOK_MSG(Frags);
	HOOK_MSG(ObjScore);
	HOOK_MSG(PStatus);
	HOOK_MSG(ScoreShort);
	HOOK_MSG(PClass);
	HOOK_MSG(PTeam);
	HOOK_MSG(RoundState);
	HOOK_MSG(CurMarker);
	HOOK_MSG(TimeLeft);
	HOOK_MSG(Scope);
	HOOK_MSG(GameRules);
	HOOK_MSG(CameraView);
	HOOK_MSG(ResetSens);
	HOOK_MSG(Object);
	HOOK_MSG(ClientAreas);
	HOOK_MSG(InitObj);
	HOOK_MSG(SetObj);
	HOOK_MSG(StartProg);
	HOOK_MSG(StartProgF);
	HOOK_MSG(ProgUpdate);
	HOOK_MSG(CancelProg);
	HOOK_MSG(TimerStatus);
	HOOK_MSG(PlayersIn);
	HOOK_MSG(PShoot);
	HOOK_MSG(AmmoShort);
	HOOK_MSG(ReloadDone);
	HOOK_MSG(CapMsg);
	HOOK_MSG(ClanTimer);

	// Deathmatch classic
	HOOK_MSG(QItems);

	// Halflife
	HOOK_MSG(ValClass);
	HOOK_MSG(SpecFade);
	HOOK_MSG(ResetFade);
	HOOK_MSG(Bench);

	// oposing force
	HOOK_MSG(HudColor);
	HOOK_MSG(OldWeapon);
	HOOK_MSG(SetMenuTeam);
	HOOK_MSG(StatsInfo);
	HOOK_MSG(StatsPlayer);
	HOOK_MSG(TeamFull);
	HOOK_MSG(PlayerIcon);
	HOOK_MSG(CTFScore);
	HOOK_MSG(CustomIcon);
	HOOK_MSG(FlagIcon);
	HOOK_MSG(FlagTimer);
	HOOK_MSG(PlyrBrowse);
	*/

	return gEngfuncs.pfnHookUserMsg(szMsgName, pfn);
}

//===========================
// SetupHooks
// Thread created when the dll loads
// place your event hooks here
//===========================
void SetupHooks(void)
{
	while(!FindWindow("valve001", NULL)) Sleep(100);
	Sleep(2000);

	if(!gOffsets.Initialize()) return;

	// find structs and classes
	pStudioModelRenderer = (StudioModelRenderer_t*)gOffsets.StudioModelRenderer();//OffsetCStudioModelRenderer();
	pClientDll = (ClientDll_t*)gOffsets.ClientFuncs();//OffsetExportTable();
	pEngfuncs = (cl_enginefunc_t*)gOffsets.EngineFuncs();//OffsetEngineFunc();
	pStudio = (engine_studio_api_t*)gOffsets.EngineStudio();//OffsetEngineStudio();
	//pPreS_DynamicSound = (void*)OffsetPreSDynSound();

	add_log("pStudioModelRenderer: 0x%X", pStudioModelRenderer);
	add_log("pClientDll: 0x%X", pClientDll);
	add_log("pEngfuncs: 0x%X", pEngfuncs);
	add_log("pStudio: 0x%X", pStudio);

	if(!pStudioModelRenderer || !pClientDll || !pEngfuncs || !pStudio)// || !pPreS_DynamicSound)
		return;

	// copy structs and classes
	RtlCopyMemory(&gStudioModelRenderer, pStudioModelRenderer, sizeof(StudioModelRenderer_t));
	RtlCopyMemory(&gClientDll, pClientDll, sizeof(ClientDll_t));
	RtlCopyMemory(&gEngfuncs, pEngfuncs, sizeof(cl_enginefunc_t));
	RtlCopyMemory(&gStudio, pStudio, sizeof(engine_studio_api_t));

	// hook ClientDll functions
	HookClientFunction(HUD_Redraw);
	HookClientFunction(HUD_UpdateClientData);
	HookClientFunction(HUD_PlayerMove);
	HookClientFunction(V_CalcRefdef);
	HookClientFunction(HUD_AddEntity);
	HookClientFunction(HUD_CreateEntities);
	HookClientFunction(HUD_DrawNormalTriangles);
	HookClientFunction(HUD_DrawTransparentTriangles);
	HookClientFunction(HUD_PostRunCmd);
	HookClientFunction(HUD_Frame);
	HookClientFunction(HUD_Key_Event);
	HookClientFunction(HUD_TempEntUpdate);

	// hook CStudioModelRenderer class functions
	DWORD dwOldProt;
	VirtualProtect(pStudioModelRenderer, sizeof(StudioModelRenderer_t), PAGE_READWRITE, &dwOldProt);
	HookRendererFunction(StudioRenderModel);
	HookRendererFunction(StudioRenderFinal);
	HookRendererFunction(StudioDrawPlayer);
	VirtualProtect(pStudioModelRenderer, sizeof(StudioModelRenderer_t), dwOldProt, &dwOldProt);

	// recall ClientDll & HUD initialization to hook events & usermsgs
	pEngfuncs->pfnHookEvent = &HookEvent;
	pEngfuncs->pfnHookUserMsg = &HookUserMsg;
	pEngfuncs->pfnAddCommand = &AddCommand;
	pEngfuncs->pfnRegisterVariable = &RegisterVariable;
	
	gClientDll.Initialize(pEngfuncs, CLDLL_INTERFACE_VERSION);
	gClientDll.HUD_Init();

	pEngfuncs->Con_Printf("minihook-ng loaded.");

	pEngfuncs->pfnHookEvent = gEngfuncs.pfnHookEvent;
	pEngfuncs->pfnHookUserMsg = gEngfuncs.pfnHookUserMsg;
	pEngfuncs->pfnAddCommand = gEngfuncs.pfnAddCommand;
	pEngfuncs->pfnRegisterVariable = gEngfuncs.pfnRegisterVariable;
}

Detour_c *detLoadLibrary = NULL;
typedef HMODULE (WINAPI* tLoadLibraryA)(LPCSTR);
tLoadLibraryA oLoadLibraryA = NULL;
HMODULE WINAPI xLoadLibraryA(LPCSTR lpFileName) {

	if(strstr(lpFileName, "client.dll")) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SetupHooks, NULL, 0, NULL);
		detLoadLibrary->RemoveDetour();
		return LoadLibraryA(lpFileName);
	}

	return oLoadLibraryA(lpFileName);
}

//===========================
// DllMain
// Module Entrypoint
//===========================
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, PVOID unused)
{
	if(fdwReason == DLL_PROCESS_ATTACH)
	{
		//HideModuleFromPEB(hinstDLL);
		//RemovePeHeader((DWORD)hinstDLL);
		init_log(hinstDLL);

		detLoadLibrary = new Detour_c((DWORD)LoadLibraryA, (DWORD)xLoadLibraryA);
		oLoadLibraryA = (tLoadLibraryA)detLoadLibrary->SetupDetour();
	}

	if(fdwReason == DLL_PROCESS_DETACH) {
		delete detLoadLibrary;
		deinit_log();
	}

	return TRUE;
}