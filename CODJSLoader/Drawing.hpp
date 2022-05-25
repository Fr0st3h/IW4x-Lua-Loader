#pragma once
#include "Colour.hpp"
#include "vector.h"
#include "Structs.hpp"

class Drawing
{

public:

	void drawShader(float x, float y, float width, float height, float r, float g, float b, float a)
	{
		Color color = Color(r, g, b, a);
		CG_DrawStretchPic(x, y, width, height, 1, 1, 1, 1, (float*)&color, R_RegisterShader("white", 0));
	}

	void drawText(const char* text, float x, float y, const char* font, float fontSize, float r, float g, float b, float a = 255)
	{
		Color color = Color(r, g, b, a);
		CG_DrawEngineText(text, 0x7FFFFFFF, R_RegisterFont(font, 0), x, y, fontSize, fontSize, 0, (float*)&color, 0);
	}

	float TextWidth(const char* text, const char* font, float scale)
	{
		return R_TextWidth(text, 0x7FFFFFFF, R_RegisterFont(font, 0)) * scale;
	}

	void drawMat(float x, float y, float width, float height, float angle, float r, float g, float b, float a, const char* shader) {
		Color color = Color(r, g, b, a);
		CG_DrawRotatedPicPhysical(0x10843F0, x, y, width, height, angle, (float*)&color, R_RegisterShader(shader, 0));
	}

	void DrawLine(float X1, float Y1, float X2, float Y2, float r, float g, float b, float a, float Width)
	{
		float X, Y, Angle, L1, L2, H1;
		H1 = Y2 - Y1;
		L1 = X2 - X1;
		L2 = sqrt(L1 * L1 + H1 * H1);
		X = X1 + ((L1 - L2) / 2);
		Y = Y1 + (H1 / 2);
		Angle = (float)atan(H1 / L1) * (180 / 3.14159265358979323846F);
		Color color = Color(r, g, b, a);
		CG_DrawRotatedPicPhysical(0x10843F0, X, Y, L2, Width, Angle, (float*)&color, R_RegisterShader("white", 0));
	}

private:

	typedef size_t(*CG_DrawStretchPic_t)(float x, float y, float w, float h, float s1, float t1, float s2, float t2, const float* color, int hShader);
	typedef int (*R_RegisterShader_t)(const char* shader, int a2);
	typedef void* (*R_RegisterFont_t)(const char* pszFontName, int idk);
	typedef int (*CG_DrawEngineText_t)(const char* Text, int a2, void* Font, float x, float y, float a6, float a7, float a8, const float* pColor, int a10);
	typedef int (*R_TextWidth_t)(const char* text, int maxChars, void* font);
	typedef bool (*CG_DrawRotatedPicPhysical_t)(int scrPlace, float x, float y, float w, float h, float angle, const float* color, int material);




	CG_DrawStretchPic_t CG_DrawStretchPic = (CG_DrawStretchPic_t)0x509770;
	R_RegisterShader_t R_RegisterShader = (R_RegisterShader_t)0x505E60;
	R_RegisterFont_t R_RegisterFont = (R_RegisterFont_t)0x4EB8B0;
	CG_DrawEngineText_t CG_DrawEngineText = (CG_DrawEngineText_t)0x509D80;
	R_TextWidth_t R_TextWidth = (R_TextWidth_t)0x005056C0;
	CG_DrawRotatedPicPhysical_t CG_DrawRotatedPicPhysical = (CG_DrawRotatedPicPhysical_t)0x004E9500;



};

