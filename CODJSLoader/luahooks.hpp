#pragma once
#include "luabind\luabind.hpp"

#include <tuple>
#include <unordered_map>
#include <vector>

namespace LuaHooks
{
	enum HookType
	{
		HOOK_TEST,
		HOOK_KEYBOARD,
		HOOK_PREGAME_RENDER,
		HOOK_CL_DRAWSTRETCHPIC,
		HOOK_BULLETHITEVENT,
		HOOK_CG_OBITUARY,
		HOOK_CL_DrawText
	};

	class Hooks
	{
	public:
		bool RegisterHook(HookType type, luabind::object f)
		{
			if (HasHook(type) && !AllowsMultipleHooks(type))
				return false;

			std::get<0>(m_Hooks[(HookType)type]) = true;
			std::get<1>(m_Hooks[(HookType)type]).push_back(f);
			return true;
		}

		void DisableAllExcept(HookType type)
		{
			for (auto it = m_Hooks.begin(); it != m_Hooks.end(); it++)
			{
				if (it->first != type)
					std::get<0>(it->second) = false;
			}
		}

		void EnableAllHooks()
		{
			for (auto it = m_Hooks.begin(); it != m_Hooks.end(); it++)
				std::get<0>(it->second) = true;
		}

		bool AllowsMultipleHooks(HookType type)
		{
			return true;
		}

		bool HasHook(HookType type)
		{
			auto it = m_Hooks.find(type);
			return it != m_Hooks.end() && std::get<0>(*it);
		}

		std::vector<luabind::object> GetCallbacks(HookType type)
		{
			if (std::get<0>(m_Hooks[type]))
				return std::get<1>(m_Hooks[type]);
			else return std::vector<luabind::object>();
		}

		void Reset()
		{
			m_Hooks.clear();
		}
	private:
		std::unordered_map<HookType, std::tuple<bool, std::vector<luabind::object>>> m_Hooks;
	};
}