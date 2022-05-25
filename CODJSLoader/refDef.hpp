#pragma once

#include "vector.h"

class RefDef {

public:
	__int32 x; //0x0000 
	__int32 y; //0x0004 
	__int32 iWidth; //0x0008 
	__int32 iHeight; //0x000C 
	float fovX; //0x0010 
	float fovY; //0x0014 
	Vector vOrigin; //0x0018 
	Vector vViewAxis[3]; //0x0024 
	char _0x0048[4];
	Vector vViewAngles; //0x004C 
	__int32 iTime; //0x0058 
	__int32 iMenu; //0x005C 
	char _0x0060[16128];
	Vector refdefViewAngles; //0x3F60 
	char _0x3F6C[276];
};