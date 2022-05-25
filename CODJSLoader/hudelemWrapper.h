#pragma once


#include "hudelem.hpp"
#include "Utils.hpp"
#include "logger.hpp"

#define byte unsigned char

class hudelemWrapper {



public:
	typedef game_hudelem*(*HudElem_Alloc_t)(int clientNum, int teamNum);
	HudElem_Alloc_t HudElem_Alloc = (HudElem_Alloc_t)0x004EB130;
	typedef int(*G_LocalizedStringIndex_t)(const char* string);
	G_LocalizedStringIndex_t G_LocalizedStringIndex = G_LocalizedStringIndex_t(0x004582F0);
	typedef int(*G_MaterialIndex_t)(const char* shader);
	G_MaterialIndex_t G_MaterialIndex = G_MaterialIndex_t(0x004A93A0);

	game_hudelem* setText(int client, const char* text, int font, float fontScale, float x, float y, int alignOrg, float sort, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		game_hudelem* elem = HudElem_Alloc(client, 0);
		elem->clientNum = client;
		elem->elem.type = 0x01;
		elem->elem.alignOrg = alignOrg;
		elem->elem.alignScreen = 0x01;
		elem->elem.font = font;
		elem->elem.fontScale = fontScale;
		elem->elem.x = x;
		elem->elem.y = y;
		elem->elem.color.r = r;
		elem->elem.color.g = g;
		elem->elem.color.b = b;
		elem->elem.color.a = a;
		elem->elem.sort = sort;
		elem->elem.text = G_LocalizedStringIndex(text);
		printf("hud pointer %p\n", elem);
		return elem;
	}

	game_hudelem* setShader(int client, const char* shader, float x, float y, int width, int height, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		game_hudelem* elem = HudElem_Alloc(client, 0);
		elem->clientNum = client;
		elem->elem.type = 4;
		elem->elem.materialIndex = G_MaterialIndex(shader);
		elem->elem.width = width;
		elem->elem.height = height;
		elem->elem.x = x;
		elem->elem.y = y;
		elem->elem.alignOrg = 0;
		elem->elem.color.r = r;
		elem->elem.color.g = g;
		elem->elem.color.b = b;
		elem->elem.color.a = a;
		printf("hud pointer %p\n", elem);
		return elem;
	}

	void testSpawn() {
		setText(0, "HELLO WORLD", 1, 1.0, 50, 50, 0, 0, 255,0,0,255);
		setShader(0, "white", 150, 150, 500, 500, 255, 0, 0, 255);
	}
	


};