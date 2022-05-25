#pragma once

class hudelem_color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

class hudelem {

public:
	int type;                    // 0x00-0x04
	float y;                      // 0x04-0x08
	float x;                      // 0x08-0x0C
	float z;                      // 0x0C-0x10
	int targetEntNum;            // 0x10-0x14
	float fontScale;              // 0x14-0x18
	float fromFontScale;          // 0x18-0x1C
	int fontScaleStartTime;      // 0x1C-0x20
	int fontScaleTime;            // 0x20-0x24
	int label;                    // 0x24-0x28
	int font;                    // 0x28-0x2C
	int alignOrg;                // 0x2C-0x30
	int alignScreen;              // 0x30-0x34
	hudelem_color color;        // 0x34-0x38
	hudelem_color fromColor;    // 0x38-0x3C
	int fadeStartTime;            // 0x3C-0x40
	int fadeTime;                // 0x40-0x44
	int height;                  // 0x44-0x48
	int width;                    // 0x48-0x4C
	int materialIndex;            // 0x4C-0x50
	int fromHeight;              // 0x50-0x54
	int fromWidth;                // 0x54-0x58
	int scaleStartTime;          // 0x58-0x5C
	int scaleTime;                // 0x5C-0x60
	float fromY;                  // 0x60-0x64
	float fromX;                  // 0x64-0x68
	int fromAlignOrg;            // 0x68-0x6C
	int fromAlignScreen;          // 0x6C-0x70
	int moveStartTime;            // 0x70-0x74
	int moveTime;                // 0x74-0x78
	float value;                  // 0x78-0x7C
	int time;                    // 0x7C-0x80
	int duration;                // 0x80-0x84
	int text;                    // 0x84-0x88
	float sort;                  // 0x88-0x8C
	hudelem_color glowColor;    // 0x8C-0x90
	int fxBirthTime;              // 0x90-0x94
	int fxLetterTime;            // 0x94-0x98
	int fxDecayStartTime;        // 0x98-0x9C
	int fxDecayDuration;          // 0x9C-0xA0
	int soundID;                  // 0xA0-0xA4
	int flags;                    // 0xA4-0xA8

};

class game_hudelem {
public:
	hudelem elem;               // 0x00-0xA8
	int clientNum;                // 0xA8-0xAC
	int teamNum;                  // 0xAC-0xB0
	int archived;                 // 0xB0-0xB4
};