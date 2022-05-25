#pragma once
#include "CentityWrapper.hpp"
#include "CClientWrapper.hpp"

class StructWrapper {

public:

	CentityWrapper GetCentity() {
		CentityWrapper centity(Structs::centity);
	//	printf("CentityWrapper pointer: %p\n", centity);
		return centity;
	}

	CentityWrapper GetCentityIndex(int client) {
		CentityWrapper centity(&Structs::centity[client]);
	//	printf("CentityWrapper pointer and client: %p %i\n", centity, client);
		return centity;
	}

	CClientWrapper GetCClientIndex(int client) {
		CClientWrapper cclient(&Structs::cclient[client]);
	//	printf("CClientWrapper pointer and client: %p %i\n", cclient, client);
		return cclient;
	}



};