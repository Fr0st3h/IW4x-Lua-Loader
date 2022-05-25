#include "binds.hpp"

#include "luastate.hpp"
#include "logger.hpp"
#include "events.h"
#include "Drawing.hpp"
#include "Colour.hpp"
#include "hooks.hpp"
#include "vector.h"
#include "StructWrapper.hpp"
#include "Utils.hpp"
#include "hudelemWrapper.h"
#include "CentityStateWrapper.hpp"

Drawing drawing;
Logger::Debug logger;
StructWrapper structWrapper;
Utils utils;
hudelemWrapper hudWrap;


namespace Binds
{
	void initialize(void)
	{

		luabind::module(LuaState::pLuaState)[
			luabind::class_<StructWrapper>("__Structs")
				.def("GetCentity", &StructWrapper::GetCentity)
				.def("GetCentityIndex", &StructWrapper::GetCentityIndex)
				.def("GetCClientIndex", &StructWrapper::GetCClientIndex),
				luabind::class_<LuaHooks::Hooks>("__Hooks")
				.def("Register", &LuaHooks::Hooks::RegisterHook),
				luabind::class_<Events::EventKeyboard>("EventKeyboard")
				.property("Type", &Events::EventKeyboard::GetType)
				.property("KeyCode", &Events::EventKeyboard::GetKeyCode),
				luabind::class_<Drawing>("__Drawing")
				.def("drawText", &Drawing::drawText)
				.def("drawShader", &Drawing::drawShader)
				.def("drawMat", &Drawing::drawMat)
				.def("GetTextWidth", &Drawing::TextWidth)
				.def("DrawLine", &Drawing::DrawLine),
				luabind::class_<Utils>("__Utils")
				.def("WorldToScreen", &Utils::WorldToScreen)
				.def("EngineW2s", &Utils::EngineW2s)
				.def("UI_PlaySound", &Utils::UI_PlaySound)
				.def("iPrintlnBold", &Utils::iPrintlnBold)
				.def("Sys_Millisecond", &Utils::Sys_Millisecond)
				.def("Cbuf_AddText", &Utils::Cbuf_AddTextFunc)
				.def("Dvar_SetStringByName", &Utils::Dvar_SetStringByNameFunc)
				.def("CL_IsGameInitialized", &Utils::CL_IsGameInitialized)
				.def("getMousePosition", &Utils::getMousePosition)
				.def("RegisterTag", &Utils::RegisterTag)
				.def("Material_RegisterHandle", &Utils::Material_RegisterHandleFunc),
				luabind::class_<Hooks::DrawStretchPic>("EventCLDrawStretchPic")
				.property("getShader", &Hooks::DrawStretchPic::getShader)
				.def("setColor", &Hooks::DrawStretchPic::setColor)
				.def("setMaterial", &Hooks::DrawStretchPic::setMaterial),
				luabind::class_<Hooks::DrawTextInternal>("EventCLDrawTextInternal")
				.def("setText", &Hooks::DrawTextInternal::setText)
				.property("getText", &Hooks::DrawTextInternal::getText)
				.def("setX", &Hooks::DrawTextInternal::setX)
				.def("setY", &Hooks::DrawTextInternal::setY)
				.property("getX", &Hooks::DrawTextInternal::getX)
				.property("getY", &Hooks::DrawTextInternal::getY)
				.def("setColor", &Hooks::DrawTextInternal::setColor)
				.property("getFont", &Hooks::DrawTextInternal::getFont)
				.def("setFont", &Hooks::DrawTextInternal::setFont)
				.property("getFontSize", &Hooks::DrawTextInternal::getFontSize)
				.def("setFontSize", &Hooks::DrawTextInternal::setFontSize),
				luabind::class_<Logger::Debug>("__Debug")
				.def("Print", &Logger::Debug::debugPrint),
				luabind::class_<Vector2D>("Vector2")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float>())
				.def(luabind::const_self + luabind::const_self)
				.def(luabind::const_self - luabind::const_self)
				.property("X", &Vector2D::x, &Vector2D::x)
				.property("Y", &Vector2D::y, &Vector2D::y),
				luabind::class_<Vector>("Vector3")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float, float>())
				.def(luabind::const_self + luabind::const_self)
				.def(luabind::const_self - luabind::const_self)
				.def(luabind::const_self * luabind::const_self)
				.def(luabind::const_self / luabind::const_self)
				.def(luabind::const_self * luabind::other<float>())
				.def(luabind::const_self / luabind::other<float>())
				.def("Length", &Vector::Length)
				.def("Length2D", &Vector::Length2D)
				.property("X", &Vector::x, &Vector::x)
				.property("Y", &Vector::y, &Vector::y)
				.property("Z", &Vector::z, &Vector::z),
				luabind::class_<CentityWrapper>("CentityWrapper")
				.def("GetOrigin", &CentityWrapper::getOrigin),
				luabind::class_<CClientWrapper>("CClientWrapper")
				.def("GetName", &CClientWrapper::getName)
				.def("IsShooting", &CClientWrapper::isShooting)
				.def("GetTeam", &CClientWrapper::getTeam),
				luabind::class_<Hooks::BulletHit>("EventBulletHit")
				.property("getEvent", &Hooks::BulletHit::getEvent)
				.property("getPos", &Hooks::BulletHit::getPos),
				luabind::class_<hudelemWrapper>("__Hud")
				.def("TestSpawn", &hudelemWrapper::testSpawn),
				luabind::class_<CentityStateWrapper>("CentityStateWrapper")
				.property("getKillerClientNum", &CentityStateWrapper::getKillerClientNum)
				.property("getKillerWeaponNum", &CentityStateWrapper::getKillerWeaponNum)
				.property("getVictimClientNum", &CentityStateWrapper::getVictimClientNum)
				.property("getVictimWeaponNum", &CentityStateWrapper::getVictimWeaponNum)
				.property("getKillType", &CentityStateWrapper::getKillType)
		];


		try
		{
			luabind::globals(LuaState::pLuaState)["KEY_NONE"] = Events::KEY_NONE;
			luabind::globals(LuaState::pLuaState)["BUTTON_LEFT"] = Events::BUTTON_LEFT;
			luabind::globals(LuaState::pLuaState)["BUTTON_RIGHT"] = Events::BUTTON_RIGHT;
			luabind::globals(LuaState::pLuaState)["BUTTON_MIDDLE"] = Events::BUTTON_MIDDLE;
			luabind::globals(LuaState::pLuaState)["BUTTON_MOUSE4"] = Events::BUTTON_MOUSE4;
			luabind::globals(LuaState::pLuaState)["BUTTON_MOUSE5"] = Events::BUTTON_MOUSE5;
			luabind::globals(LuaState::pLuaState)["KEY_BACK"] = Events::KEY_BACK;
			luabind::globals(LuaState::pLuaState)["KEY_TAB"] = Events::KEY_TAB;
			luabind::globals(LuaState::pLuaState)["KEY_CLEAR"] = Events::KEY_CLEAR;
			luabind::globals(LuaState::pLuaState)["KEY_RETURN"] = Events::KEY_RETURN;
			luabind::globals(LuaState::pLuaState)["KEY_SHIFT"] = Events::KEY_SHIFT;
			luabind::globals(LuaState::pLuaState)["KEY_CONTROL"] = Events::KEY_CONTROL;
			luabind::globals(LuaState::pLuaState)["KEY_ALT"] = Events::KEY_ALT;
			luabind::globals(LuaState::pLuaState)["KEY_PAUSE"] = Events::KEY_PAUSE;
			luabind::globals(LuaState::pLuaState)["KEY_CAPITAL"] = Events::KEY_CAPITAL;
			luabind::globals(LuaState::pLuaState)["KEY_ESCAPE"] = Events::KEY_ESCAPE;
			luabind::globals(LuaState::pLuaState)["KEY_SPACE"] = Events::KEY_SPACE;
			luabind::globals(LuaState::pLuaState)["KEY_PRIOR"] = Events::KEY_PRIOR;
			luabind::globals(LuaState::pLuaState)["KEY_NEXT"] = Events::KEY_NEXT;
			luabind::globals(LuaState::pLuaState)["KEY_END"] = Events::KEY_END;
			luabind::globals(LuaState::pLuaState)["KEY_HOME"] = Events::KEY_HOME;
			luabind::globals(LuaState::pLuaState)["KEY_LEFT"] = Events::KEY_LEFT;
			luabind::globals(LuaState::pLuaState)["KEY_UP"] = Events::KEY_UP;
			luabind::globals(LuaState::pLuaState)["KEY_RIGHT"] = Events::KEY_RIGHT;
			luabind::globals(LuaState::pLuaState)["KEY_DOWN"] = Events::KEY_DOWN;
			luabind::globals(LuaState::pLuaState)["KEY_PRINT"] = Events::KEY_PRINT;
			luabind::globals(LuaState::pLuaState)["KEY_INSERT"] = Events::KEY_INSERT;
			luabind::globals(LuaState::pLuaState)["KEY_DELETE"] = Events::KEY_DELETE;
			luabind::globals(LuaState::pLuaState)["KEY_0"] = Events::KEY_0;
			luabind::globals(LuaState::pLuaState)["KEY_1"] = Events::KEY_1;
			luabind::globals(LuaState::pLuaState)["KEY_2"] = Events::KEY_2;
			luabind::globals(LuaState::pLuaState)["KEY_3"] = Events::KEY_3;
			luabind::globals(LuaState::pLuaState)["KEY_4"] = Events::KEY_4;
			luabind::globals(LuaState::pLuaState)["KEY_5"] = Events::KEY_5;
			luabind::globals(LuaState::pLuaState)["KEY_6"] = Events::KEY_6;
			luabind::globals(LuaState::pLuaState)["KEY_7"] = Events::KEY_7;
			luabind::globals(LuaState::pLuaState)["KEY_8"] = Events::KEY_8;
			luabind::globals(LuaState::pLuaState)["KEY_9"] = Events::KEY_9;
			luabind::globals(LuaState::pLuaState)["KEY_A"] = Events::KEY_A;
			luabind::globals(LuaState::pLuaState)["KEY_B"] = Events::KEY_B;
			luabind::globals(LuaState::pLuaState)["KEY_C"] = Events::KEY_C;
			luabind::globals(LuaState::pLuaState)["KEY_D"] = Events::KEY_D;
			luabind::globals(LuaState::pLuaState)["KEY_E"] = Events::KEY_E;
			luabind::globals(LuaState::pLuaState)["KEY_F"] = Events::KEY_F;
			luabind::globals(LuaState::pLuaState)["KEY_G"] = Events::KEY_G;
			luabind::globals(LuaState::pLuaState)["KEY_H"] = Events::KEY_H;
			luabind::globals(LuaState::pLuaState)["KEY_I"] = Events::KEY_I;
			luabind::globals(LuaState::pLuaState)["KEY_J"] = Events::KEY_J;
			luabind::globals(LuaState::pLuaState)["KEY_K"] = Events::KEY_K;
			luabind::globals(LuaState::pLuaState)["KEY_L"] = Events::KEY_L;
			luabind::globals(LuaState::pLuaState)["KEY_M"] = Events::KEY_M;
			luabind::globals(LuaState::pLuaState)["KEY_N"] = Events::KEY_N;
			luabind::globals(LuaState::pLuaState)["KEY_O"] = Events::KEY_O;
			luabind::globals(LuaState::pLuaState)["KEY_P"] = Events::KEY_P;
			luabind::globals(LuaState::pLuaState)["KEY_Q"] = Events::KEY_Q;
			luabind::globals(LuaState::pLuaState)["KEY_R"] = Events::KEY_R;
			luabind::globals(LuaState::pLuaState)["KEY_S"] = Events::KEY_S;
			luabind::globals(LuaState::pLuaState)["KEY_T"] = Events::KEY_T;
			luabind::globals(LuaState::pLuaState)["KEY_U"] = Events::KEY_U;
			luabind::globals(LuaState::pLuaState)["KEY_V"] = Events::KEY_V;
			luabind::globals(LuaState::pLuaState)["KEY_W"] = Events::KEY_W;
			luabind::globals(LuaState::pLuaState)["KEY_X"] = Events::KEY_X;
			luabind::globals(LuaState::pLuaState)["KEY_Y"] = Events::KEY_Y;
			luabind::globals(LuaState::pLuaState)["KEY_Z"] = Events::KEY_Z;
			luabind::globals(LuaState::pLuaState)["KEY_LWIN"] = Events::KEY_LWIN;
			luabind::globals(LuaState::pLuaState)["KEY_RWIN"] = Events::KEY_RWIN;
			luabind::globals(LuaState::pLuaState)["KEY_APPS"] = Events::KEY_APPS;
			luabind::globals(LuaState::pLuaState)["KEY_SLEEP"] = Events::KEY_SLEEP;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD0"] = Events::KEY_NUMPAD0;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD1"] = Events::KEY_NUMPAD1;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD2"] = Events::KEY_NUMPAD2;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD3"] = Events::KEY_NUMPAD3;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD4"] = Events::KEY_NUMPAD4;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD5"] = Events::KEY_NUMPAD5;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD6"] = Events::KEY_NUMPAD6;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD7"] = Events::KEY_NUMPAD7;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD8"] = Events::KEY_NUMPAD8;
			luabind::globals(LuaState::pLuaState)["KEY_NUMPAD9"] = Events::KEY_NUMPAD9;
			luabind::globals(LuaState::pLuaState)["KEY_MULTIPLY"] = Events::KEY_MULTIPLY;
			luabind::globals(LuaState::pLuaState)["KEY_ADD"] = Events::KEY_ADD;
			luabind::globals(LuaState::pLuaState)["KEY_SEPARATOR"] = Events::KEY_SEPARATOR;
			luabind::globals(LuaState::pLuaState)["KEY_SUBTRACT"] = Events::KEY_SUBTRACT;
			luabind::globals(LuaState::pLuaState)["KEY_DECIMAL"] = Events::KEY_DECIMAL;
			luabind::globals(LuaState::pLuaState)["KEY_DIVIDE"] = Events::KEY_DIVIDE;
			luabind::globals(LuaState::pLuaState)["KEY_F1"] = Events::KEY_F1;
			luabind::globals(LuaState::pLuaState)["KEY_F2"] = Events::KEY_F2;
			luabind::globals(LuaState::pLuaState)["KEY_F3"] = Events::KEY_F3;
			luabind::globals(LuaState::pLuaState)["KEY_F4"] = Events::KEY_F4;
			luabind::globals(LuaState::pLuaState)["KEY_F5"] = Events::KEY_F5;
			luabind::globals(LuaState::pLuaState)["KEY_F6"] = Events::KEY_F6;
			luabind::globals(LuaState::pLuaState)["KEY_F7"] = Events::KEY_F7;
			luabind::globals(LuaState::pLuaState)["KEY_F8"] = Events::KEY_F8;
			luabind::globals(LuaState::pLuaState)["KEY_F9"] = Events::KEY_F9;
			luabind::globals(LuaState::pLuaState)["KEY_F10"] = Events::KEY_F10;
			luabind::globals(LuaState::pLuaState)["KEY_F11"] = Events::KEY_F11;
			luabind::globals(LuaState::pLuaState)["KEY_F12"] = Events::KEY_F12;
			luabind::globals(LuaState::pLuaState)["KEY_LMENU"] = Events::KEY_LMENU;
			luabind::globals(LuaState::pLuaState)["KEY_RMENU"] = Events::KEY_RMENU;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_1"] = Events::KEY_OEM_1;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_PLUS"] = Events::KEY_OEM_PLUS;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_COMMA"] = Events::KEY_OEM_COMMA;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_MINUS"] = Events::KEY_OEM_MINUS;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_PERIOD"] = Events::KEY_OEM_PERIOD;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_2"] = Events::KEY_OEM_2;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_3"] = Events::KEY_OEM_3;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_4"] = Events::KEY_OEM_4;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_5"] = Events::KEY_OEM_5;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_6"] = Events::KEY_OEM_6;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_7"] = Events::KEY_OEM_7;
			luabind::globals(LuaState::pLuaState)["KEY_OEM_8"] = Events::KEY_OEM_8;

			luabind::globals(LuaState::pLuaState)["HOOK_KEYBOARD"] = LuaHooks::HookType::HOOK_KEYBOARD;
			luabind::globals(LuaState::pLuaState)["HOOK_TEST"] = LuaHooks::HookType::HOOK_TEST;
			luabind::globals(LuaState::pLuaState)["HOOK_PREGAME_RENDER"] = LuaHooks::HookType::HOOK_PREGAME_RENDER;
			luabind::globals(LuaState::pLuaState)["HOOK_CL_DRAWSTRETCHPIC"] = LuaHooks::HookType::HOOK_CL_DRAWSTRETCHPIC;
			luabind::globals(LuaState::pLuaState)["HOOK_BULLETHITEVENT"] = LuaHooks::HookType::HOOK_BULLETHITEVENT;
			luabind::globals(LuaState::pLuaState)["HOOK_CG_OBITUARY"] = LuaHooks::HookType::HOOK_CG_OBITUARY;
			luabind::globals(LuaState::pLuaState)["HOOK_CL_DRAWTEXTINTERNAL"] = LuaHooks::HookType::HOOK_CL_DrawText;




			luabind::globals(LuaState::pLuaState)["EVENT_UNKNOWN"] = Events::EVENT_UNKNOWN;
			luabind::globals(LuaState::pLuaState)["EVENT_KEYDOWN"] = Events::EVENT_KEYDOWN;
			luabind::globals(LuaState::pLuaState)["EVENT_KEYUP"] = Events::EVENT_KEYUP;
			luabind::globals(LuaState::pLuaState)["EVENT_MOUSEDOWN"] = Events::EVENT_MOUSEDOWN;
			luabind::globals(LuaState::pLuaState)["EVENT_MOUSEUP"] = Events::EVENT_MOUSEUP;
			luabind::globals(LuaState::pLuaState)["EVENT_MOUSEMOVE"] = Events::EVENT_MOUSEMOVE;

			luabind::globals(LuaState::pLuaState)["Utils"] = &utils;
			luabind::globals(LuaState::pLuaState)["Drawing"] = &drawing;
			luabind::globals(LuaState::pLuaState)["Structs"] = &structWrapper;
			luabind::globals(LuaState::pLuaState)["Hud"] = &hudWrap;

			luabind::globals(LuaState::pLuaState)["Debug"] = &logger;
			luabind::globals(LuaState::pLuaState)["Hooks"] = &LuaState::gHooks;


			Logger::append(Logger::kLogType::SUCCESS, "Loading script...\n");
			Logger::debugPrint("[+] Loading script..");

			if (luaL_dofile(LuaState::pLuaState, SCRIPT_DIR) != 0)
			{
				Logger::append(Logger::kLogType::ERROR, "Error: %s\n", lua_tostring(LuaState::pLuaState, -1));

				char buf[255];
				snprintf(buf, sizeof(buf), "Error: %s\n", lua_tostring(LuaState::pLuaState, -1));
				Logger::debugPrint(buf);

				return;
			}
			

			Logger::append(Logger::kLogType::SUCCESS, "Done loading script\n");
			Logger::debugPrint("[+] Script has been Loaded.");
			
		}
		catch (const std::exception& TheError)
		{
			Logger::append(Logger::kLogType::ERROR, "[CATCH] Error: %s\n", TheError.what());

			char buf[255];
			snprintf(buf, sizeof(buf), "[CATCH] Error: %s\n", TheError.what());
			Logger::debugPrint(buf);

		}
	}
}