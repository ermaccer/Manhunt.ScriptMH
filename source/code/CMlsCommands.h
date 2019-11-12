#pragma once

#define PushMessage 1001
#define WriteMemory 1002
#define ReadMemory  1003
#define KeyHit      1004

namespace CMlsCommands {
	void Hook();
	int HookLoader(int a1);
	void __fastcall ProcessNewCommands(int ptr);
}