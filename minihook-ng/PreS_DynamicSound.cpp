#include <windows.h>
#include "SDKInclude.h"
#include "TransInclude.h"

void PreS_DynamicSound(int Index, char* Sound, float* Origin)
{

}

LONG WINAPI PreS_DynamicSound_Handler(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	if(ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP )
	{ 
		if (ExceptionInfo->ExceptionRecord->ExceptionAddress == pPreS_DynamicSound)
		{
			int		Index	= (int)	 	*(DWORD*)(ExceptionInfo->ContextRecord->Esp + 0x04);
			char	*Sound	= (char*)	*(DWORD*)(ExceptionInfo->ContextRecord->Esp + 0x0C);
			float	*Origin	= (float*)	*(DWORD*)(ExceptionInfo->ContextRecord->Esp + 0x10);

			PreS_DynamicSound(Index, Sound, Origin);

			ExceptionInfo->ContextRecord->Esp -= 0x48;
			ExceptionInfo->ContextRecord->Eip += 0x3;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}
	return EXCEPTION_CONTINUE_SEARCH;
}