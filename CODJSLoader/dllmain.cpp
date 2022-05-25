#include <Windows.h>
#include "lib/detours.h"
#include <mmsystem.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "luastate.hpp"

#include "lib/luabind-0.9.1/luabind/luabind.hpp"
#include "lib/lua-5.2.0/src/lua.hpp"

#include "lib/luabind-0.9.1/luabind/operator.hpp"
#include "lib/luabind-0.9.1/luabind/exception_handler.hpp"

#include "logger.hpp"

#include "binds.hpp"

#include "hooks.hpp"

#include "Structs.hpp"

#include <debugapi.h>

#include "Hooking.hpp"

#include "Utils.hpp"
#include "Drawing.hpp"


FILE* file = nullptr;
void InitConsole() {
	AllocConsole();
	SetConsoleTitle(L"Console: CODLUA");
	freopen_s(&file, "CONOUT$", "w", stdout);
}

lua_State* pLuaState;
bool disableMenuPaint = false;

void notification(std::string notification, int time) {
	int width = 1920;
	int height = 1080;
	int slideTime = 75;

	Utils utils;
	static int startTime = utils.Sys_Millisecond();
	int duration = 2000;
	int bHeight = 74;

	float titleSize = 0.9;
	float msgSize = 0.9;

	const char* titleFont = "fonts/normalFont";
	const char* msgFont = "fonts/normalFont";

	height = height / 5;
	height = height * 4;

	if (utils.Sys_Millisecond() < startTime || (startTime + duration) < utils.Sys_Millisecond()) {
		return;
	}
	else if (utils.Sys_Millisecond() - startTime < slideTime) {
		int diffH = height / 5;
		int diff = utils.Sys_Millisecond() - startTime;
		float scale = 1.0 - ((1.0 * diff) / (1.0 * slideTime));
		diffH = (diffH * scale);
		height += diffH;
	}
	else  if (utils.Sys_Millisecond() - startTime > (duration - slideTime)) {
		int diffH = height / 5;
		int diff = (startTime + duration) - utils.Sys_Millisecond();
		float scale = 1.0 - ((1.0 * diff) / (1.0 * slideTime));
		diffH = (diffH * scale);
		height += diffH;
	}

	height += bHeight / 2;
	bHeight += (bHeight % 2);

	Drawing drawing;

	drawing.drawShader(width / 2 - (225 / 2), (height - bHeight / 2) + 50, 225, bHeight, 0, 0, 0, 200);


}

void ReloadScript()
{
	Logger::append(Logger::kLogType::NORMAL, "Reloading script\n");
	Logger::debugPrint("[+] Reloading script.lua..");
	LuaState::gHooks.Reset();
	Sleep(500);
	LuaState::initialize();
	Binds::initialize();
	notification("test", 5000);
	disableMenuPaint = false;
}
typedef char* (__cdecl* LoadModdableRawfile_t)(int a1, const char* filename);
typedef int(__cdecl* Scr_GetFunctionHandle_t)(const char*, const char*);
typedef int(__cdecl* Scr_LoadScript_t)(const char*);
LoadModdableRawfile_t LoadModdableRawfile = LoadModdableRawfile_t(0x61ABC0);
Scr_LoadScript_t Scr_LoadScript = Scr_LoadScript_t(0x45D940);
Scr_GetFunctionHandle_t Scr_GetFunctionHandle = Scr_GetFunctionHandle_t(0x4234F0);
void* LoadModdableRawfileFunc(const char* filename)
{
	return LoadModdableRawfile(0, filename);
}

int LoadScriptAndLabel(const std::string& script, const std::string& label)
{
	printf("Loading script %s.gsc...\n", script.data());

	if (!Scr_LoadScript(script.data()))
	{
		printf("Script %s encountered an error while loading. (doesn't exist?)", script.data());
		printf(reinterpret_cast<char*>(0x70B810), script.data());
	}
	else
	{
		printf("Script %s.gsc loaded successfully.\n", script.data());
	}

	//printf("Finding script handle %s::%s...\n", script.data(), label.data());
	int handle = Scr_GetFunctionHandle(script.data(), label.data());
	if (handle)
	{
		//printf("Script handle %s::%s loaded successfully.\n", script.data(), label.data());
		return handle;
	}

	//printf("Script handle %s::%s couldn't be loaded. (file with no entry point?)\n", script.data(), label.data());
	return handle;
}

bool down = false;
struct CODJSThread
{
	static DWORD WINAPI CodJSFunctionThread(void* pContext)
	{
		CODJSThread* codJsThread = static_cast<CODJSThread*>(pContext);

		if (Hooks::gWindowProc == NULL)
		{
			HWND hWindow = NULL;
			while (!(hWindow = FindWindowA("IW4", "IW4x: Multiplayer"))) Sleep(200);
			Hooks::gWindowProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)Hooks::NewWndProc);
			Logger::debugPrint("[+] Found IW4x Window.");
		}

		Logger::append(Logger::kLogType::SUCCESS, "Init Structs...\n");
		Logger::debugPrint("[+] Setting up structs..");
		Structs::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Init Lua...\n");
		Logger::debugPrint("[+] Initializing Lua..");
		LuaState::initialize();

		Logger::append(Logger::kLogType::SUCCESS, "Init LuaBinds...\n");
		Logger::debugPrint("[+] Initializing binds..");
		Binds::initialize();

		Logger::debugPrint("[*] CODLUA started.. Click F1 to reload script.lua");

		for (;;) {
			if (GetAsyncKeyState(VK_F1) && !down) {
				ReloadScript();
				down = true;
			}else if (!GetAsyncKeyState(VK_F1) && down) 
				down = false;
			
		}

		return 0;
	}
};


void(*Menu_PaintAll_Stub)(...);
void Menu_PaintAll_Hook(int A) {
	Menu_PaintAll_Stub(A);



	if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_PREGAME_RENDER) && !disableMenuPaint)
	{
		auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_PREGAME_RENDER);
		for (auto it = v.begin(); it != v.end(); it++)
		{
			try
			{
				luabind::call_function<void>(*it);
			}
			catch (const std::exception& TheError)
			{
				Logger::append(Logger::kLogType::ERROR, "Error inside Menu_PaintAll Hook: %s\n", lua_tostring(LuaState::pLuaState, -1));

				char buf[255];
				snprintf(buf, sizeof(buf), "Error inside Menu_PaintAll Hook: %s\n", lua_tostring(LuaState::pLuaState, -1));
				Logger::debugPrint(buf);
				disableMenuPaint = true;
			}
		}
	}
}
std::string ScriptName;
std::vector<int> ScriptHandles;
std::vector<std::string> ScriptNameStack;
unsigned short FunctionName;
std::unordered_map<std::string, std::string> ScriptStorage;
std::unordered_map<int, std::string> ScriptBaseProgramNum;

__declspec(naked) void StoreFunctionNameStub()
{
	__asm
	{
		mov eax, [esp - 8h]
		mov FunctionName, ax

		sub esp, 0Ch
		push 0
		push edi

		mov eax, 612DB6h
		jmp eax
	}
}

void StoreScriptName(const char* name)
{
	printf("Stored %s\n", name);
	ScriptNameStack.push_back(ScriptName);
	ScriptName = name;
}
typedef int(__cdecl* Scr_ExecThread_t)(int, int);
typedef int(__cdecl* Scr_FreeThread_t)(int);
typedef int(__cdecl* Scr_LoadGameType_t)();

Scr_ExecThread_t Scr_ExecThread = Scr_ExecThread_t(0x4AD0B0);
Scr_FreeThread_t Scr_FreeThread = Scr_FreeThread_t(0x4BD320);
Scr_LoadGameType_t Scr_LoadGameType = Scr_LoadGameType_t(0x4D9520);


void LoadGameType()
{
	printf("LoadGameType\n");
	for (auto handle : ScriptHandles)
	{
		Scr_FreeThread(Scr_ExecThread(handle, 0));
	}

	Scr_LoadGameType();
}

void RestoreScriptName()
{
	ScriptName = ScriptNameStack.back();
	ScriptNameStack.pop_back();
}

__declspec(naked) void RestoreScriptNameStub()
{
	printf("Restored script name\n");
	__asm
	{
		pushad
		call RestoreScriptName
		popad

		mov ds : 1CDEAA8h, ebp

		push 427E77h
		retn
	}
}

typedef void(__cdecl* GScr_LoadGameTypeScript_t)();
GScr_LoadGameTypeScript_t GScr_LoadGameTypeScript = GScr_LoadGameTypeScript_t(0x4ED9A0);

void LoadGameTypeScript()
{

	ScriptHandles.clear();

	int handle = LoadScriptAndLabel("test", "init");
	if (handle) ScriptHandles.push_back(handle);
	else
	{
		handle = LoadScriptAndLabel("test", "main");
		if (handle) ScriptHandles.push_back(handle);
	}
	printf("Found handle! %i\n", handle);

	GScr_LoadGameTypeScript();
}
typedef void(__cdecl* Scr_ShutdownAllocNode_t)();
typedef char* (__cdecl* SL_ConvertToString_t)(unsigned short stringValue);
SL_ConvertToString_t SL_ConvertToString = SL_ConvertToString_t(0x4EC1D0);

Scr_ShutdownAllocNode_t Scr_ShutdownAllocNode = Scr_ShutdownAllocNode_t(0x441650);
void FunctionError()
{
	printf("FUNCTION ERROR\n");
	std::string funcName = SL_ConvertToString(FunctionName);

	Scr_ShutdownAllocNode();

	
	printf("******* script compile error *******\n");
	printf("Error: unknown function %s in %s\n", funcName.data(), ScriptName.data());
	printf("************************************\n");

	printf("script compile error\nunknown function %s\n%s\n\n", funcName.data(), ScriptName.data());
}
void CompileError(unsigned int offset, const char* message, ...)
{
	printf("COMPILE ERROR\n");
	char msgbuf[1024] = { 0 };
	va_list v;
	va_start(v, message);
	_vsnprintf_s(msgbuf, sizeof(msgbuf), message, v);
	va_end(v);

	Scr_ShutdownAllocNode();

	printf( "******* script compile error *******\n");
	printf( "Error: %s ", msgbuf);
	printf( "************************************\n\n");

	printf("script compile error\n%s\n%s\n(see console for actual details)\n", msgbuf, ScriptName.data());
}

void ScrShutdownSystemStub(int num)
{
	// Scr_ShutdownSystem
	Utilss::Hook::Call<void(int)>(0x421EE0)(num);
}

//"setclientdvar", 33473




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	CODJSThread* foo = new CODJSThread();
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		InitConsole();

		Logger::append(Logger::kLogType::WARNING, "CODLUA loading...\n\n");
		char test[60];
		snprintf(test, sizeof(test), "[*] Starting CODLUA. Build: %s @ %s :)", __DATE__, __TIME__);
		Logger::debugPrint(test);


		CreateThread(NULL, 0, CODJSThread::CodJSFunctionThread, foo, 0L, NULL);
		Menu_PaintAll_Stub = (void(*)(...))DetourFunction((PBYTE)0x004EDF60, (PBYTE)Menu_PaintAll_Hook); Logger::append(Logger::kLogType::SUCCESS, "Menu_Paintall Hooked\n");
		//GSC
		//Utils::Hook(0x612E8D, FunctionError, HOOK_CALL).install()->quick();
		//Utils::Hook(0x612EA2, FunctionError, HOOK_CALL).install()->quick();
		//Utils::Hook(0x434260, CompileError, HOOK_JUMP).install()->quick();

	//	Utils::Hook(0x48EFFE, LoadGameType, HOOK_CALL).install()->quick();
	//	Utils::Hook(0x45D44A, LoadGameTypeScript, HOOK_CALL).install()->quick();

//		Utils::Hook(0x47548B, ScrShutdownSystemStub, HOOK_CALL).install()->quick();
//		Utils::Hook(0x4D06BA, ScrShutdownSystemStub, HOOK_CALL).install()->quick();

		//END GSC
		Hooks::initCGBulletHit_Hook();
		Hooks::initCLDrawStretchPic_Hook();
		Hooks::InitCG_DrawEngineText_Hook();
		Hooks::initObituaryHook();
		break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

