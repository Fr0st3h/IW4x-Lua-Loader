#include "luastate.hpp"

namespace LuaState
{
	LuaHooks::Hooks gHooks;
	lua_State* pLuaState;

	void initialize(void)
	{
		unload();

		pLuaState = luaL_newstate();

		luabind::open(pLuaState);
		luaL_openlibs(pLuaState);
	}

	void unload(void)
	{
		if (pLuaState != nullptr)
		{
			lua_close(pLuaState);
			pLuaState = nullptr;
		}
	}
}