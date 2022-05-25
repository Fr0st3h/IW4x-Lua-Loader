#pragma once
namespace Events
{
	enum Events
	{
		EVENT_UNKNOWN,
		EVENT_KEYDOWN,
		EVENT_KEYUP,
		EVENT_MOUSEDOWN,
		EVENT_MOUSEUP,
		EVENT_MOUSEMOVE
	};

	enum ButtonCodes
	{
		BUTTON_NONE = 0x00,
		BUTTON_LEFT = 0x01,
		BUTTON_RIGHT = 0x02,
		BUTTON_MIDDLE = 0x03,
		BUTTON_MOUSE4 = 0x04,
		BUTTON_MOUSE5 = 0x05
	};

	enum KeyCodes
	{
		KEY_NONE = 0x00,
		KEY_BACK = 0x08,
		KEY_TAB = 0x09,
		KEY_CLEAR = 0x0C,
		KEY_RETURN = 0x0D,
		KEY_SHIFT = 0x10,
		KEY_CONTROL = 0x11,
		KEY_ALT = 0x12,
		KEY_PAUSE = 0x13,
		KEY_CAPITAL = 0x14,
		KEY_ESCAPE = 0x1B,
		KEY_SPACE = 0x20,
		KEY_PRIOR = 0x21,
		KEY_NEXT = 0x22,
		KEY_END = 0x23,
		KEY_HOME = 0x24,
		KEY_LEFT = 0x25,
		KEY_UP = 0x26,
		KEY_RIGHT = 0x27,
		KEY_DOWN = 0x28,
		KEY_PRINT = 0x2A,
		KEY_INSERT = 0x2D,
		KEY_DELETE = 0x2E,
		KEY_0 = 0x30,
		KEY_1 = 0x31,
		KEY_2 = 0x32,
		KEY_3 = 0x33,
		KEY_4 = 0x34,
		KEY_5 = 0x35,
		KEY_6 = 0x36,
		KEY_7 = 0x37,
		KEY_8 = 0x38,
		KEY_9 = 0x39,
		KEY_A = 0x41,
		KEY_B = 0x42,
		KEY_C = 0x43,
		KEY_D = 0x44,
		KEY_E = 0x45,
		KEY_F = 0x46,
		KEY_G = 0x47,
		KEY_H = 0x48,
		KEY_I = 0x49,
		KEY_J = 0x4A,
		KEY_K = 0x4B,
		KEY_L = 0x4C,
		KEY_M = 0x4D,
		KEY_N = 0x4E,
		KEY_O = 0x4F,
		KEY_P = 0x50,
		KEY_Q = 0x51,
		KEY_R = 0x52,
		KEY_S = 0x53,
		KEY_T = 0x54,
		KEY_U = 0x55,
		KEY_V = 0x56,
		KEY_W = 0x57,
		KEY_X = 0x58,
		KEY_Y = 0x59,
		KEY_Z = 0x5A,
		KEY_LWIN = 0x5B,
		KEY_RWIN = 0x5C,
		KEY_APPS = 0x5D,
		KEY_SLEEP = 0x5F,
		KEY_NUMPAD0 = 0x60,
		KEY_NUMPAD1 = 0x61,
		KEY_NUMPAD2 = 0x62,
		KEY_NUMPAD3 = 0x63,
		KEY_NUMPAD4 = 0x64,
		KEY_NUMPAD5 = 0x65,
		KEY_NUMPAD6 = 0x66,
		KEY_NUMPAD7 = 0x67,
		KEY_NUMPAD8 = 0x68,
		KEY_NUMPAD9 = 0x69,
		KEY_MULTIPLY = 0x6A,
		KEY_ADD = 0x6B,
		KEY_SEPARATOR = 0x6C,
		KEY_SUBTRACT = 0x6D,
		KEY_DECIMAL = 0x6E,
		KEY_DIVIDE = 0x6F,
		KEY_F1 = 0x70,
		KEY_F2 = 0x71,
		KEY_F3 = 0x72,
		KEY_F4 = 0x73,
		KEY_F5 = 0x74,
		KEY_F6 = 0x75,
		KEY_F7 = 0x76,
		KEY_F8 = 0x77,
		KEY_F9 = 0x78,
		KEY_F10 = 0x79,
		KEY_F11 = 0x7A,
		KEY_F12 = 0x7B,
		KEY_F13 = 0x7C,
		KEY_F14 = 0x7D,
		KEY_F15 = 0x7E,
		KEY_F16 = 0x7F,
		KEY_F17 = 0x80,
		KEY_F18 = 0x81,
		KEY_F19 = 0x82,
		KEY_F20 = 0x83,
		KEY_F21 = 0x84,
		KEY_F22 = 0x85,
		KEY_F23 = 0x86,
		KEY_F24 = 0x87,
		KEY_LSHIFT = 0xA0,
		KEY_RSHIFT = 0xA1,
		KEY_LCONTROL = 0xA2,
		KEY_RCONTROL = 0xA3,
		KEY_LMENU = 0xA4,
		KEY_RMENU = 0xA5,
		KEY_OEM_1 = 0xBA,
		KEY_OEM_PLUS = 0xBB,
		KEY_OEM_COMMA = 0xBC,
		KEY_OEM_MINUS = 0xBD,
		KEY_OEM_PERIOD = 0xBE,
		KEY_OEM_2 = 0xBF,
		KEY_OEM_3 = 0xC0,
		KEY_OEM_4 = 0xDB,
		KEY_OEM_5 = 0xDC,
		KEY_OEM_6 = 0xDD,
		KEY_OEM_7 = 0xDE,
		KEY_OEM_8 = 0xDF
	};

	class EventKeyboard
	{
	public:
		EventKeyboard()
		{
			m_eEventType = EVENT_UNKNOWN;
			m_iKey = KEY_NONE;
		}
		EventKeyboard(Events type, int key)
		{
			m_eEventType = type;
			m_iKey = key;
		}

		Events GetType() { return m_eEventType; }
		int GetKeyCode() { return m_iKey; }

	private:
		Events m_eEventType;
		int m_iKey;
	};

	class EventMouse
	{
	public:
		EventMouse()
		{
			m_eEventType = Events::EVENT_UNKNOWN;
			m_eButtonType = ButtonCodes::BUTTON_NONE;
			m_iMouseX = 0;
			m_iMouseY = 0;
		}
		EventMouse(Events type, ButtonCodes button, int x, int y)
		{
			m_eEventType = type;
			m_eButtonType = button;
			m_iMouseX = x;
			m_iMouseY = y;
		}

		Events GetType() { return m_eEventType; }
		ButtonCodes GetButton() { return m_eButtonType; }
		int GetX() { return m_iMouseX; }
		int GetY() { return m_iMouseY; }

	private:
		Events m_eEventType;
		ButtonCodes m_eButtonType;
		int m_iMouseX;
		int m_iMouseY;
	};
}