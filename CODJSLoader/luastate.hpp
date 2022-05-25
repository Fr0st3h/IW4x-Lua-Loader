#pragma once

#include <lua.hpp>

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include <luabind/exception_handler.hpp>

#include "luahooks.hpp"

namespace LuaState
{
	extern LuaHooks::Hooks gHooks;
	extern lua_State* pLuaState;

	void initialize(void);
	void unload(void);
}