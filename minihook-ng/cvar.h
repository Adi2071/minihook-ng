#pragma once

struct hookcvar_s {
	float inpvs;
	float aim;
	float predahead;
	float nospread;
	float norecoil;
	float novisrecoil;
	//Visuals
	float light;
	float tlight;
	float bone;
	float crosshair;
	float zoomall;
	float triggerbot;
	float wallsensitivity;
	float autofire;
	float bunnyhop;
	float spinbot;
};
extern struct hookcvar_s cvar;

struct debugvar_s {
	float aimtarget;
};
extern struct debugvar_s dvar;

