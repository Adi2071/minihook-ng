#ifndef __OFFSETSCAN__
#define __OFFSETSCAN__

#pragma once

class COffsets
{
private:
	DWORD ClBase, ClSize;
	DWORD HwBase, HwSize;

public:
	bool Initialize(void);
	void *ClientFuncs(void);
	void *EngineFuncs(void);
	void *EngineStudio(void);
	void *FOV(void);
	void *GlobalTime(void);
	void *PlayerMove(void);
	void *RefParams(void);
	void *StudioModelRenderer(void);
};

extern COffsets gOffsets;

#endif