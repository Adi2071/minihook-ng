#include <windows.h>
#include "MemoryScan.h"
#include "OffsetScan.h"

COffsets gOffsets;

bool COffsets::Initialize(void)
{
	ClBase = (DWORD)GetModuleHandle("client.dll");
	ClSize = (DWORD)0x00159000;
	
	HwBase = (DWORD)GetModuleHandle("hw.dll");
	HwSize = (DWORD)0x0122A000;
	
	if (!(ClBase && HwBase))
	{
		ClBase = HwBase = (DWORD)GetModuleHandle(NULL);
		ClSize = HwSize = (DWORD)0x02116000;
	}
	
	return (ClBase && HwBase);
}

void *COffsets::ClientFuncs(void)
{
	PCHAR String = "ScreenFade";
	DWORD Address = (DWORD)FindMemoryClone(HwBase, HwBase+HwSize, String, strlen(String));
	return (void*)*(DWORD*)(FindReference(HwBase, HwBase+HwSize, Address) + 0x13);
}

void *COffsets::EngineFuncs(void)
{
	PCHAR String = "ScreenFade";
	DWORD Address = FindMemoryClone(HwBase, HwBase+HwSize, String, strlen(String));
	return (void*)*(DWORD*)(FindReference(HwBase, HwBase+HwSize, Address) + 0x0D);
}

void *COffsets::EngineStudio(void)
{
	PCHAR String = "Couldn't get client .dll studio model rendering interface.";
	DWORD Address = FindMemoryClone(HwBase, HwBase+HwSize, String, strlen(String));
	return (void*)*(DWORD*)(FindReference(HwBase, HwBase+HwSize, Address) - 0x14);
}

void *COffsets::FOV(void)
{
	UCHAR Sig[] = "\xDB\x44\x24\x0C\x85\xFF\xD9\x54\x24\x0C\xD9\x1D\xFF\xFF\xFF\xFF\x75\x05\x89\x5E\x58\xEB\x03\x89\x7E\x58\x39\x5E\x58\x75\x16\xC7\x46\x18\x00\x00\x00\x00\x5F\x5E\xB8\x01\x00\x00\x00\x5B\x81\xC4\x08\x04\x00\x00\xC3";
	return (void*)*(DWORD*)(FindMemoryClone(ClBase, ClBase+ClSize, Sig, sizeof(Sig)-1) + 0x0C);
}

void *COffsets::GlobalTime(void)
{
	UCHAR Sig[] = "\x74\x47\xDD\x05\xFF\xFF\xFF\xFF\x51\x8D\x4C\x24\x08\xD9\x5C\x24\x04\xD9\x44\x24\x04\xD9\x1C\x24\x51\xFF\xD0\x83\xC4\x08\x85\xC0\x74\x27";
	return (void*)*(DWORD*)(FindMemoryClone(HwBase, HwBase+HwSize, Sig, sizeof(Sig)-1) + 0x04);
}

void *COffsets::PlayerMove(void)
{
	UCHAR Sig[] = "\xA1\xFF\xFF\xFF\xFF\x8B\x0D\xFF\xFF\xFF\xFF\x8B\x95\xFF\xFF\xFF\xFF\x8D\x74\x24\xFF";
	return (void*)**(DWORD**)(FindMemoryClone(HwBase, HwBase+HwSize, Sig, sizeof(Sig)-1) + 0x01);
}

void *COffsets::RefParams(void)
{
	UCHAR Sig[] = "\x53\x8B\x5C\x24\xFF\x56\x57\xB9\xFF\xFF\xFF\xFF\x8B\xF3\xBF\xFF\xFF\xFF\xFF\x68";
	return (void*)*(DWORD*)(FindMemoryClone(HwBase, HwBase+HwSize, Sig, sizeof(Sig)-1) + 0x0F);
}

void *COffsets::StudioModelRenderer(void)
{
	UCHAR Sig[] = "\x56\x8B\xF1\xE8\xFF\xFF\xFF\xFF\xC7\x06\xFF\xFF\xFF\xFF\xC6\x86\xFF\xFF\xFF\xFF\xFF\x8B\xC6\x5E\xC3";
	return (void*)*(DWORD*)(FindMemoryClone(ClBase, ClBase+ClSize, Sig, sizeof(Sig)-1) + 0x0A);
}