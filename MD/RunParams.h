#ifndef RUNPARAMS_H
#define RUNPARAMS_H

#include "Atom.h"
#include "AtomGrid.h"
#include <vector>
using namespace std;

class RunParams {
	public:
		RunParams(vector<Atom *> &atoms_, Bounds b, float gridSize, float timestep_, int reNeighborListCheck_) : atoms(atoms_), grid(atoms, b, gridSize, gridSize, gridSize), timestep(timestep_), reNeighborListCheck(reNeighborListCheck_) {};
		vector<Atom *> atoms;
		AtomGrid grid;
		float rCut;
		float padding;
		float timestep;
		bool periodic[3];
		int reNeighborListCheck; //check for re-neighborlisting every # turns

};

#endif
