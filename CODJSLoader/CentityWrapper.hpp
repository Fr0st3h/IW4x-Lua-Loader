#include "centity.hpp"

#include "Structs.hpp"


class CentityWrapper {

public:
	CentityWrapper(Centity* pCent) {
		cent = pCent;
	}

	Centity* test() {
		return cent;
	}

	Vector getOrigin() {
		return cent->vOrigin;
	}

private:
	Centity* cent;


};
