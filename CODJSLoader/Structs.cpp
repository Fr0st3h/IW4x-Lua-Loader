#include "Structs.hpp"

namespace Structs {

	Centity* centity;
	CClient* cclient;
	RefDef* refdef;

	void initialize(void) {
		centity = reinterpret_cast<Centity*>(0x8F3CA8);
		cclient = reinterpret_cast<CClient*>(0x8E77B0);
		refdef = reinterpret_cast<RefDef*>(0x85B6F0);
	}

}