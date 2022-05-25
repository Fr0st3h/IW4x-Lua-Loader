#pragma once

#include <Windows.h>
#include <process.h>
#include <Psapi.h>
#include <string.h>
#include <stdio.h>
#include "events.h"
#include "luastate.hpp"
#include "Colour.hpp"
#include "vector.h"
#include "CentityState.hpp"

namespace Hooks
{
	extern WNDPROC gWindowProc;
	HRESULT __stdcall NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	extern const float* Colorr;

	extern const char* teext;
	extern float xPos;
	extern float yPos;
	extern const float* textColorr;
	extern const char* textFont;
	extern float fontSize;
	extern void* textureMaterial;

	extern void CL_DrawStretchPic_Hook(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float s1, float t1, float s2, float t2, const float* color, void* material);
	extern void(*CL_DrawStretchPic_Stub)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float s1, float t1, float s2, float t2, const float* color, void* material);

	extern char CG_BulletHitEvent_Hook(int localClientNum, int sourceEntityNum, Vector* startPos, Vector* position, Vector* normal, int surfType, int event, char eventParam, int damage, int hitContents);
	extern char(*CG_BulletHitEvent_Stub)(int localClientNum, int sourceEntityNum, Vector* startPos, Vector* position, Vector* normal, int surfType, int event, char eventParam, int damage, int hitContents);

	extern void hkCG_Obituary();

	extern void initObituaryHook();
	extern void initCLDrawStretchPic_Hook();
	extern void initCGBulletHit_Hook();
	extern void InitCG_DrawEngineText_Hook();


	class DrawTextInternal {
	public:
		DrawTextInternal(const char* pText, float xpos, float ypos, const float* pColor, const char* pFont, float pSize) {
			teext = pText;
			xPos = xpos;
			yPos = ypos;
			textColorr = pColor;
			textFont = pFont;
			fontSize = pSize;
		}

		void setText(const char* pText) {
			teext = pText;
		}

		float getFontSize() {
			return fontSize;
		}

		void setFontSize(float size) {
			fontSize = size;
		}

		const char* getFont() {
			return textFont;
		}

		void setFont(const char* pFont) {
			textFont = pFont;
		}

		void setColor(float r, float g, float b, float a) {
			Color color = Color(r, g, b, a);
			printf("");
			textColorr = (float*)&color;
		}

		void setX(float val) {
			xPos = val;
		}

		void setY(float val) {
			yPos = val;
		}

		float getX() {
			return xPos;
		}

		float getY() {
			return yPos;
		}

		const char* getText() {
			return teext;
		}
	private:

	};

	class DrawStretchPic {
		void* (*Material_RegisterHandle)(const char* material, int imageTract) = (void* (*)(const char*, int))0x00505E60;

	public:
		DrawStretchPic(const char* pShader, const float* pColor, void* material) {
			shader = pShader;
			Colorr = pColor;
			textureMaterial = material;
		}

		void setColor(float r, float g, float b, float a) {
			Color test = Color(r, g, b, a);
			printf("");
			Colorr = (float*)&test;
		}
		const float* getColor() {
			return Colorr;
		}

		const char* getShader() {
			return shader;
		}

		void setMaterial(const char* material) {
			textureMaterial = Material_RegisterHandle(material, 7);
		}

	private:
		const char* shader;
	};

	class BulletHit {
	public:
		BulletHit(int event, Vector* startPos, Vector* pos) {
			m_event = event;
			m_startPos = startPos;
			m_pos = pos;

		}
		
		int getEvent() {
			return m_event;
		}

		Vector* getPos() {
			return m_pos;
		}

	private:
		int m_event;
		Vector* m_startPos;
		Vector* m_pos;
	};
}