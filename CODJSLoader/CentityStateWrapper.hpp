#pragma once

#include "CentityState.hpp"




class CentityStateWrapper {

public:

	CentityStateWrapper(CEntityState_t centityState) {
		centity = centityState;
	}
	int getKillerClientNum() {
		return centity->killerEntNum;
	}
	int getKillerWeaponNum() {
		return centity->killerWeapon;
	}
	int getVictimClientNum() {
		return centity->victimEntNum;
	}
	int getVictimWeaponNum() {
		return centity->victimWeapon;
	}
	int getKillType() {
		return centity->killType;
	}
private:
	CEntityState_t centity;

};

