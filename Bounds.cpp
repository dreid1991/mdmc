#include <string>
#include <iostream>
#include "Bounds.h"
using namespace std;


void Bounds::resize(int dim, NT mult, NT around) {
	NT hiDim = hi[dim];
	NT loDim = lo[dim];
	double origin = loDim + around * (hiDim - loDim);
	hi[dim] = mult * (hiDim - origin) + origin;
	lo[dim] = mult * (loDim - origin) + origin;
	trace[dim] *= mult;
}

bool Bounds::atomInBounds(Atom *a) {
	for (int i=0; i<NDIM; i++) {
		if (not (a->pos[i] >= lo[i] and a->pos[i] <= hi[i])) {
			return false;
		}
	}
	return true;
}
void Bounds::populateOnGrid(vector<Atom *> &atoms, unsigned int n) {
	assert(n>=0);
	int nPerSide = ceil(pow(n, 1.0/NDIM));
	Vector deltaPerSide = trace / nPerSide;
	if (NDIM == 3) {
		for (int i=0; i<nPerSide; i++) {
			for (int j=0; j<nPerSide; j++) {
				for (int k=0; k<nPerSide; k++) {
					if (atoms.size() == n) {
						return;
					}
					Vector pos = lo + Vector(i, j, k) * deltaPerSide;
					Atom *a = new Atom(pos);
					atoms.push_back(a);

				}
			}
		}
	} else if (NDIM == 2) {
		for (int i=0; i<nPerSide; i++) {
			for (int j=0; j<nPerSide; j++) {
				if (atoms.size() == n) {
					return;
				}
				Vector pos = lo + Vector(i, j, 0) * deltaPerSide;
				Atom *a = new Atom(pos);
				atoms.push_back(a);
			}
		}

	}
}
Bounds nullBounds = Bounds(Vector(0,0,0), Vector(0,0,0));
