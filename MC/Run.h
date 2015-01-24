#ifndef RUNPARAMS_H
#define RUNPARAMS_H

#include "Atom.h"
#include "AtomGrid.h"
#include <vector>
#include "Data.h"
#include "InteractionParams.h"
using namespace std;
/*
 * run owns atoms, data, and fixes -  All that it sees.
 * AtomGrid has a reference to atoms, operates on those.  Shouldn't slow things down much b/c using iterators
 * Fixes have a reference to the list of all atoms along with a list of atoms that they are operating on
 * Fixes also have a reference to data
*/
class Run {
	public:
		Run(Bounds b, InteractionParams &params_, double gridSize, int dataInterval_, double temp_) : params(params_), grid(atoms, b, gridSize, gridSize, gridSize), dataInterval(dataInterval_), temp(temp_), currentTurn(0) {
			periodic[0] = periodic[1] = periodic[2] = true;
		};

		vector<Atom *> atoms;
		InteractionParams params;
		AtomGrid grid;
		double rCut;
		double padding;
		bool periodic[3];
		int neighborListInterval; //check for re-neighborlisting every # turns
		int dataInterval;
		double temp;
		Data data;
		int dangerousRebuilds;
		int currentTurn;

};

#endif
