#include "hooks.hpp"
#include "logger.hpp"
#include "lib/detours.h"

typedef void* (*R_RegisterFont_t)(const char* pszFontName, int idk);
R_RegisterFont_t R_RegisterFont = (R_RegisterFont_t)0x4EB8B0;

namespace Hooks {

	const float* Colorr;
	const char* teext;

	float xPos;
	float yPos;
	const float* textColorr;
	const char* textFont;
	float fontSize;

	void* textureMaterial;


	int (*CG_DrawEngineText_Stub)(const char* Text, int a2, void* Font, float x, float y, float a6, float a7, float a8, const float* pColor, int a10);
	int CG_DrawEngineText_Hook(const char* Text, int a2, void* Font, float x, float y, float a6, float a7, float a8, const float* pColor, int a10) {
		textFont = *(char**)Font;
		teext = Text;
		xPos = x;
		yPos = y;
		textColorr = pColor;
		fontSize = a6;

		if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_CL_DrawText))
		{
			auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_CL_DrawText);
			for (auto it = v.begin(); it != v.end(); it++)
			{
				try
				{
					luabind::call_function<void>(*it, DrawTextInternal(teext, xPos, yPos, textColorr, textFont, fontSize));
				}
				catch (const std::exception& TheError)
				{
					Logger::append(Logger::kLogType::ERROR, "Error inside CL_DrawTextInternal Hook: %s\n", lua_tostring(LuaState::pLuaState, -1));
				}
			}
		}
		return CG_DrawEngineText_Stub(teext, a2, R_RegisterFont(textFont, 0), xPos, yPos, fontSize, fontSize, a8, textColorr, a10);
	}

	void InitCG_DrawEngineText_Hook() {
		Hooks::CG_DrawEngineText_Stub = (int(*)(const char* , int , void* , float , float , float , float , float, const float* , int ))DetourFunction((PBYTE)0x509D80, (PBYTE)Hooks::CG_DrawEngineText_Hook); 		Logger::append(Logger::kLogType::SUCCESS, "CL_DrawStretchPic Hooked %p\n", Hooks::CL_DrawStretchPic_Stub);
	}

	void(*CL_DrawStretchPic_Stub)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float s1, float t1, float s2, float t2, const float* color, void* material);
	void CL_DrawStretchPic_Hook(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float s1, float t1, float s2, float t2, const float* color, void* material) {
		const char* Shader = *(char**)material;
		Colorr = color;
		textureMaterial = material;
		
		if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_CL_DRAWSTRETCHPIC))
		{
			auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_CL_DRAWSTRETCHPIC);
			for (auto it = v.begin(); it != v.end(); it++)
			{
				try
				{
					luabind::call_function<void>(*it, DrawStretchPic(Shader, Colorr, textureMaterial));
				}
				catch (const std::exception& TheError)
				{
					Logger::append(Logger::kLogType::ERROR, "Error inside CL_DrawStretchPic Hook: %s\n", lua_tostring(LuaState::pLuaState, -1));
				}
			}
		}
		CL_DrawStretchPic_Stub(scrPlace, x, y, w, h, horzAlign, vertAlign, s1, t1, s2, t2, Colorr, textureMaterial);
	}

	void initCLDrawStretchPic_Hook() {
		Hooks::CL_DrawStretchPic_Stub = (void(*)(int, float, float, float, float, int, int, float, float, float, float, const float*, void*))DetourFunction((PBYTE)0x00412490, (PBYTE)Hooks::CL_DrawStretchPic_Hook); 		Logger::append(Logger::kLogType::SUCCESS, "CL_DrawStretchPic Hooked %p\n", Hooks::CL_DrawStretchPic_Stub);
	}
}