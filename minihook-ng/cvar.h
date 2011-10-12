#pragma once

struct hookcvar_s {
	float inpvs;
	float aim;
	float aimspot;
	float shoottarget;
	float recoilcap;
	float speedreload;
	float predahead;
	float nospread;
	float norecoil;
	float novisrecoil;
	float drawspread;
	//Visuals
	float light;
	float tlight;
	float bone;
	float crosshair;
	float lambert;
	float chams;
	float zoomall;
	float triggerbot;
	float wallsensitivity;
	float autofire;
	float bunnyhop;
	float spinbot;
	float speed;
	float strafe;
	float strafeangle;
};
extern struct hookcvar_s cvar;
extern struct hookcvar_s panicvars;

struct debugvar_s {
	float aimtarget;
};
extern struct debugvar_s dvar;

void togglePanic(void);
