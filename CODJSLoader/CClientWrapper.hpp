#pragma once
#include "cclient.hpp"

#include "Structs.hpp"


class CClientWrapper {

public:
	CClientWrapper(CClient* client) {
		cclient = client;
	}

	const char* getName() {
		return cclient->szName;
	}

	int isShooting() {
		return cclient->IsShooting;
	}

	int getTeam() {
		return cclient->iTeam;
	}

private:
	CClient* cclient;


};