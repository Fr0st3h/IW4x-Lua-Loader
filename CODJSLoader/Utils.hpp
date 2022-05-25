#pragma once
#include "Colour.hpp"
#include "vector.h"
#include "Structs.hpp"
#include <Windows.h>
#include <WinUser.h>
#include "Structs.hpp"
#include "vector.h"

class Utils
{

public:

	
	float DotProduct(Vector hax, Vector Vector)
	{
		return (hax.x * Vector.x) + (hax.y * Vector.y) + (hax.z * Vector.z);
	}

	Vector SubstractVector(Vector Vec1, Vector Vec2)
	{
		Vector Output;
		Output.x = Vec1.x - Vec2.x;
		Output.y = Vec1.y - Vec2.y;
		Output.z = Vec1.z - Vec2.z;
		return Output;
	}

	bool WorldToScreen(Vector World, Vector& Screen)
	{
		Vector Position = SubstractVector(World, Structs::refdef->vOrigin);
		Vector Transform;

		Transform.x = DotProduct(Position, Structs::refdef->vViewAxis[1]);
		Transform.y = DotProduct(Position, Structs::refdef->vViewAxis[2]);
		Transform.z = DotProduct(Position, Structs::refdef->vViewAxis[0]);

		if (Transform.z < 0.1f)
			return false;

		Vector2D Center = { (float)Structs::refdef->iWidth * 0.5f, (float)Structs::refdef->iHeight * 0.5f };

		Screen.x = Center.x * (1 - (Transform.x / Structs::refdef->fovX / Transform.z));
		Screen.y = Center.y * (1 - (Transform.y / Structs::refdef->fovY / Transform.z));

		return true;
	}

	bool EngineW2s(Vector* vWorldLocationV, Vector2D* ScreenV)
	{
		float vWorldLocation[3];
		float Screen[2];

		vWorldLocation[0] = vWorldLocationV->x;
		vWorldLocation[1] = vWorldLocationV->y;
		vWorldLocation[2] = vWorldLocationV->z;

		return WorldToScreenE(0, GSM(0), vWorldLocation, ScreenV);
	}

	void UI_PlaySound(int local, const char* sound, int system)
	{
		SND_PlayLocalSoundAliasByName(local, sound, system);
	}

	void iPrintlnBold(int client, const char* message) {
		CG_BoldGameMessage(client, message);
	}

	int Sys_Millisecond() {
		return Sys_Milliseconds();
	}

	void Cbuf_AddTextFunc(int localClient, const char* text) {
		Cbuf_AddText(localClient, text);
	}

	void Dvar_SetStringByNameFunc(const char* cvar, const char* val) {
		Dvar_SetStringByName(cvar, val);
	}

	int CL_IsGameInitialized() {
		return CL_IsCgameInitialized();
	}

	Vector2D getMousePosition() {
		POINT mouse;
		GetCursorPos(&mouse);
		Vector2D mouseVector;
		mouseVector.x = mouse.x;
		mouseVector.y = mouse.y;
		return mouseVector;
	}

	unsigned short RegisterTag(const char* szName)
	{
		return RegisterTag_((char*)szName);
	}

	void* Material_RegisterHandleFunc(const char* mat, int t) {
		return Material_RegisterHandle(mat, t);
	}

private:
	typedef int(*SND_PlayLocalSoundAliasByName_t)(int localClientNum, const char* sound, int sys);
	typedef bool(__cdecl* CG_WorldPosToScreenPosReal_t)(int, unsigned int, float*, Vector2D*);
	typedef unsigned int(__cdecl* ScrPlace_GetActivePlacement_t)(int i);
	typedef char* (__cdecl* CG_BoldGameMessage_t)(int localClientNum, const char* msg);
	typedef int(__cdecl* Sys_Milliseconds_t)();
	typedef void(__cdecl* Dvar_SetStringByName_t)(const char* cvar, const char* value);
	typedef void(__cdecl* Cbuf_AddText_t)(int localClientNum, const char* text);
	typedef int(__cdecl* CL_IsCgameInitialized_t)();
	typedef unsigned short(__cdecl* tRegisterTag)(char* szName);
	void* (*Material_RegisterHandle)(const char* material, int imageTract) = (void* (*)(const char*, int))0x00505E60;


	CG_WorldPosToScreenPosReal_t WorldToScreenE = CG_WorldPosToScreenPosReal_t(0x00502F20);
	ScrPlace_GetActivePlacement_t GSM = ScrPlace_GetActivePlacement_t(0x004F8940);
	SND_PlayLocalSoundAliasByName_t SND_PlayLocalSoundAliasByName = (SND_PlayLocalSoundAliasByName_t)0x00685E10;
	CG_BoldGameMessage_t CG_BoldGameMessage = CG_BoldGameMessage_t(0x00455DD0);
	Sys_Milliseconds_t Sys_Milliseconds = Sys_Milliseconds_t(0x42A660);
	Dvar_SetStringByName_t Dvar_SetStringByName = Dvar_SetStringByName_t(0x44F060);
	Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x404B20);
	CL_IsCgameInitialized_t CL_IsCgameInitialized = CL_IsCgameInitialized_t(0x43EB20);
	tRegisterTag RegisterTag_ = (tRegisterTag)0x004BC450;








};

