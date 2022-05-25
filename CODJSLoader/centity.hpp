#pragma once

#include "vector.h"

class Centity {

public:
	__int16 unk0; //0x000
	__int8 Valid; //0x0002
	char  Unk4[21]; //0x0003
	Vector vOrigin; //0x0018 
	char _0x0024[72];
	__int32 IsZooming; //0x006C 
	char _0x0070[12];
	Vector vOldOrigin; //0x007C 
	char _0x0088[84];
	__int32 clientNum; //0x00DC 
	__int32 eType; //0x00E0 
	__int32 eFlags; //0x00E4 
	char _0x00E8[12];
	Vector vNewOrigin; //0x00F4 
	char _0x0100[108];
	__int32 pickupItemID; //0x016C
	__int32 clientNum2; //0x0170 
	char _0x0174[52];
	unsigned char weaponID; //0x01A8 
	char _0x01A9[51];
	__int32 iAlive; //0x01DC 
	char _0x01E0[32];
	__int32 clientNum3; //0x0200

};