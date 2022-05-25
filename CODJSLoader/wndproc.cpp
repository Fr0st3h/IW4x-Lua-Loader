#include "hooks.hpp"

namespace Hooks
{
	WNDPROC gWindowProc = NULL;

	HRESULT __stdcall NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		try
		{
			bool result = false;
			switch (uMsg)
			{
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			{
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

				Events::ButtonCodes btn = Events::ButtonCodes::BUTTON_NONE;
				Events::Events eventType = Events::Events::EVENT_UNKNOWN;

				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);

				WORD xbutton;

				switch (uMsg)
				{
				case WM_MOUSEMOVE:
					eventType = Events::EVENT_MOUSEMOVE;
					break;
				case WM_LBUTTONDOWN:
					eventType = Events::EVENT_MOUSEDOWN;
					btn = Events::BUTTON_LEFT;
					break;
				case WM_LBUTTONUP:
					eventType = Events::EVENT_MOUSEUP;
					btn = Events::BUTTON_LEFT;
					break;
				case WM_MBUTTONDOWN:
					eventType = Events::EVENT_MOUSEDOWN;
					btn = Events::BUTTON_MIDDLE;
					break;
				case WM_MBUTTONUP:
					eventType = Events::EVENT_MOUSEUP;
					btn = Events::BUTTON_MIDDLE;
					break;
				case WM_RBUTTONDOWN:
					eventType = Events::EVENT_MOUSEDOWN;
					btn = Events::BUTTON_RIGHT;
					break;
				case WM_RBUTTONUP:
					eventType = Events::EVENT_MOUSEUP;
					btn = Events::BUTTON_RIGHT;
					break;
				case WM_XBUTTONDOWN:
					eventType = Events::EVENT_MOUSEDOWN;
					xbutton = GET_XBUTTON_WPARAM(wParam);
					if (xbutton == 1)
						btn = Events::BUTTON_MOUSE4;
					else
						btn = Events::BUTTON_MOUSE5;
				case WM_XBUTTONUP:
					eventType = Events::EVENT_MOUSEUP;
					xbutton = GET_XBUTTON_WPARAM(wParam);
					if (xbutton == 1)
						btn = Events::BUTTON_MOUSE4;
					else
						btn = Events::BUTTON_MOUSE5;
				}
				
			}
			break;

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				Events::Events eventType = Events::EVENT_UNKNOWN;
				Events::KeyCodes key = Events::KEY_NONE;

				switch (uMsg)
				{
				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
					eventType = Events::EVENT_KEYDOWN;
					break;
				case WM_KEYUP:
				case WM_SYSKEYUP:
					eventType = Events::EVENT_KEYUP;
					break;
				}
				if (LuaState::gHooks.HasHook(LuaHooks::HookType::HOOK_KEYBOARD))
				{
					auto v = LuaState::gHooks.GetCallbacks(LuaHooks::HookType::HOOK_KEYBOARD);
					result = luabind::call_function<bool>(v.front(), Events::EventKeyboard(eventType, wParam));
				}
			}
			break;
			default:
				break;
			}

			if (result)
				return TRUE;
			else
				return CallWindowProc(gWindowProc, hwnd, uMsg, wParam, lParam);
		}
		catch (const std::exception&)
		{
			return CallWindowProc(gWindowProc, hwnd, uMsg, wParam, lParam);
		}
	}
}