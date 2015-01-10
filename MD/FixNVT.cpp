#include "FixNVT.h"

void FixNVT::compute() {
	float sumKe = 0;
	float tempTargetLoc = tempTarget;
	for (Atom *a : atoms) {
		sumKe += a->kinetic();
	}
	sumKe /= atoms.size() * 3.0 / 2.0;
	for (Atom *a : atoms) {
		a->vel *= (float) sqrt(tempTargetLoc / sumKe);
	}

}
