#pragma once

#include "vector.h"

class CClient {

public:
	__int32 IsValid; //0x0000 
	__int32 IsValid2; //0x0004 
	__int32 clientNum; //0x0008 
	char szName[16]; //0x000C 
	__int32 iTeam; //0x001C 
	__int32 iTeam2; //0x0020 
	__int32 iRank; //0x0024 rank+1 
	char _0x0028[4];
	__int32 iPerk; //0x002C 
	__int32 iKills; //0x0030
	__int32 iScore; //0x0034 
	char _0x0038[968];
	Vector vAngles; //0x0400 
	char _0x040C[136];
	__int32 IsShooting; //0x0494 
	char _0x0498[4];
	__int32 IsZoomed; //0x049C 
	char _0x04A0[68];
	__int32 weaponID; //0x04E4 
	char _0x04E8[24];
	__int32 weaponID2; //0x0500 
	char _0x0504[40];
};