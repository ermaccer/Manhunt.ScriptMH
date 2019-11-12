#include "CMlsCommands.h"
#include "ManhuntSDK.h"
#include "..\MemoryMgr.h"
#include <Windows.h>
#include <iostream>

int jmpPoint_false = 0x482073;
int jmpPoint_last = 0x482080;
int _edx;

using namespace MLSOperators;

void __declspec(naked) CMlsCommands::Hook()
{
	_asm {
		cmp edx, 773
	    jg  next
		mov ecx, ebx
		mov eax, 0x57AE60
		call eax
		jmp jmpPoint_last

		next:
		cmp edx, 1004
		jg jump
		mov ecx, ebx
		call ProcessNewCommands
		jmp jmpPoint_last

		jump:
		jmp jmpPoint_false
	}
}

int CMlsCommands::HookLoader(int a1)
{
	//printf("Attempting to load %s\n", (char*)a1);
	return CallAndReturn<int,0x47F1A0,int>(a1);
}

void __fastcall CMlsCommands::ProcessNewCommands(int ptr)
{
	char textBuffer[256];
	char* message;
	int MP_addr, MP_value, MP_size;
	int MPK_size, MPK_addr, MPK_retn;
	int GK_key;
	switch (*(int*)(ptr + 1128))
	{
	case PushMessage: 
		GetParam(ptr);
		message = (char*)GetStringParam(ptr);
		printf("%s\n",message);
		break;
	case WriteMemory:
		MP_value= GetParam(ptr);
		MP_size = GetParam(ptr);
		MP_addr = GetParam(ptr);
		switch (MP_size)
		{
		case 1:
			Memory::VP::Patch<char>(MP_addr, MP_value);
			break;
		case 2:
			Memory::VP::Patch<short>(MP_addr, MP_value);
			break;
		case 4:
			Memory::VP::Patch<int>(MP_addr, MP_value);
			break;
		default:
			printf("1002 (WriteMemory) ERROR | Wrong size! (%d)\n", MP_size);
			break;
		}
		break;
	case ReadMemory:
		MPK_size = GetParam(ptr);
		MPK_addr = GetParam(ptr);
		switch (MPK_size)
		{
		case 1:
			MPK_retn = *(char*)(MPK_addr);
			break;
		case 2:
			MPK_retn = *(short*)(MPK_addr);
			break;
		case 4:
			MPK_retn = *(int*)(MPK_addr);
			break;
		default:
			printf("1003 (ReadMemory) ERROR | Wrong size! (%d) Returning 0...\n", MPK_size);
			MPK_retn = 0;
			break;
		}
		*(int*)(ptr + 32) = MPK_retn;
		break;
	case KeyHit:
		GK_key = GetParam(ptr);
		*(int*)(ptr + 32) = (GetKeyState(GK_key) & 0x8000) != 0;
		break;
	default:
		break;
		return;
	}
}
