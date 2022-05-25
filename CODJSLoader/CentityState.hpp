#pragma once

class CEntityState_s
{
public:
	__int32 victimWeapon;
	__int32 killerWeapon;
	char _padding[116];
	__int32 victimEntNum;
	__int32 killerEntNum;
	char _padding2[32];
	__int32 killType;
};

typedef class CEntityState_s* CEntityState_t;
extern CEntityState_t CEntityState;
