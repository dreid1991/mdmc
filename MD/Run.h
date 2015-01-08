#ifndef RUNPARAMS_H
#define RUNPARAMS_H

#include "Atom.h"
#include "AtomGrid.h"
#include "Fix.h"
#include <vector>
#include "Data.h"
using namespace std;
/*
 * run owns atoms, data, and fixes -  All that it sees.
 * AtomGrid has a reference to atoms, operates on those.  Shouldn't slow things down much b/c using iterators
 * Fixes have a reference to the list of all atoms along with a list of atoms that they are operating on
 * Fixes also have a reference to data
*/
class Run {
	public:
		Run(Bounds b, float gridSize, float timestep_, int reNeighborListCheck_) : atoms(vector<Atom *>()), grid(atoms, b, gridSize, gridSize, gridSize), timestep(timestep_), reNeighborListCheck(reNeighborListCheck_) {};
		vector<Atom *> atoms;
		vector<Fix *> fixes;
		AtomGrid grid;
		float rCut;
		float padding;
		float timestep;
		bool periodic[3];
		int reNeighborListCheck; //check for re-neighborlisting every # turns
		Data data;

};

#endif
