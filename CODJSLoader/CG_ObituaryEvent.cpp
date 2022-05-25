#include "hooks.hpp"
#include "CentityState.hpp"
#include "lib/detours.h"
#include "logger.hpp"
#include "CentityStateWrapper.hpp"

namespace Hooks {


	typedef void(__cdecl* tCG_Obituary)(void);
	static tCG_Obituary CG_Obituary_Stub;

	CEntityState_t EntState = NULL;

	void test(CEntityState_t test) {
		if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_CG_OBITUARY))
		{
			auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_CG_OBITUARY);
			for (auto it = v.begin(); it != v.end(); it++)
			{
				try
				{
					luabind::call_function<void>(*it, CentityStateWrapper(test));
				}
				catch (const std::exception& TheError)
				{
					Logger::append(Logger::kLogType::ERROR, "Error inside HOOK_CG_OBITUARY Hook: %s\n", lua_tostring(LuaState::pLuaState, -1));

					char buf[255];
					snprintf(buf, sizeof(buf), "Error inside HOOK_CG_OBITUARY Hook: %s %s\n", lua_tostring(LuaState::pLuaState, -1), TheError.what());
					Logger::debugPrint(buf);
				}
			}
		}
	}

	_declspec(naked)void hkCG_Obituary()
	{

		_asm pushad;

		_asm mov EntState, EAX

		test(EntState);

		_asm mov EAX, EntState

		_asm popad;

		_asm jmp[CG_Obituary_Stub]
	}
	


	void initObituaryHook() {
		Hooks::CG_Obituary_Stub = (Hooks::tCG_Obituary)DetourFunction((PBYTE)0x00586C90, (PBYTE)Hooks::hkCG_Obituary); Logger::append(Logger::kLogType::SUCCESS, "CG_Obituary Hooked %p\n", Hooks::CG_Obituary_Stub);

	}


}