// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "MemoryMgr.h"
#include "code\CMlsCommands.h"
#include "code\ManhuntSDK.h"
#include <iostream>

using namespace Memory::VP;


void Init()
{
	InjectHook(0x482062, CMlsCommands::Hook, PATCH_JUMP);
	InjectHook(0x47F0C7, CMlsCommands::HookLoader,PATCH_CALL);
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (*(int*)0x63BC93 != 0x24448B66)
		{
			MessageBoxA(0, "Invalid executable!", "ScriptMH", 0);
		}
		else Init();
	}
}