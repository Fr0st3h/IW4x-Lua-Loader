#include "hooks.hpp"
#include "logger.hpp"
#include "vector.h"
#include "lib/detours.h"

namespace Hooks {


	char(*CG_BulletHitEvent_Stub)(int localClientNum, int sourceEntityNum, Vector* startPos, Vector* position, Vector* normal, int surfType, int event, char eventParam, int damage, int hitContents);
	char CG_BulletHitEvent_Hook(int localClientNum, int sourceEntityNum, Vector* startPos, Vector* position, Vector* normal, int surfType, int event, char eventParam, int damage, int hitContents) {

		if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_BULLETHITEVENT))
		{
			auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_BULLETHITEVENT);
			for (auto it = v.begin(); it != v.end(); it++)
			{
				try
				{
					luabind::call_function<void>(*it, BulletHit(event, startPos, position));
				}
				catch (const std::exception& TheError)
				{
					Logger::append(Logger::kLogType::ERROR, "Error inside CG_BulletHitEvent Hook: %s\n", lua_tostring(LuaState::pLuaState, -1));
				}
			}
		}
		
		return CG_BulletHitEvent_Stub(localClientNum, sourceEntityNum, startPos, position, normal, surfType, event, eventParam, damage, hitContents);
	}

	void initCGBulletHit_Hook() {
		Hooks::CG_BulletHitEvent_Stub = (char(*)(int, int, Vector*, Vector*, Vector*, int, int, char, int, int))DetourFunction((PBYTE)0x004FEB30, (PBYTE)Hooks::CG_BulletHitEvent_Hook); Logger::append(Logger::kLogType::SUCCESS, "CG_BulletHitEvent Hooked\n");
	}

}