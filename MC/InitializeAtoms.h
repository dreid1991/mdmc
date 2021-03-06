#ifndef INITIALIZE_H
#define INTIIALIZE_H
#include "Bounds.h"
#include "Atom.h"
#include "AtomParams.h"
#include <math.h>
#include <vector>
#include <random>
#include <map>
using namespace std;

namespace InitializeAtoms {
	void populateOnGrid(vector<Atom *> &atoms, Bounds &b, AtomParams params, int n) {
		assert(n>=0);
		int nPerSide = ceil(pow(n, 1.0/3.0));
		Vector deltaPerSide = b.trace / nPerSide;
		for (int i=0; i<nPerSide; i++) {
			for (int j=0; j<nPerSide; j++) {
				for (int k=0; k<nPerSide; k++) {
					if ((int) atoms.size() == n) {
						return;
					}
					int id = 0;
					if (atoms.size()) {
						id = atoms[atoms.size()-1]->id + 1;
					}
					Vector pos = b.lo + Vector(i, j, k) * deltaPerSide;
					Atom *a = new Atom(pos, params.m, params.type, id);
					atoms.push_back(a);

				}
			}
		}
	}

}

#endif
