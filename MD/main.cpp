#include "Atom.h"
#include "Bounds.h"
#include "AtomGrid.h"
#include "Grid.h"
#include "Vector.h"
#include "Bounds.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Run.h"
#include "Integrate.h"
#include "Data.h"
#include "includefixes.h"
#include "AtomParams.h"
#include "InteractionParams.h"
#include "InitializeAtoms.h"
using namespace std;


//have do turn first, do turn functions in Integrate.  Have turn first be all same but w/ aLast = aCur.  Hopefully don't have to copy everything

int main() {
	const float rCut = 1.75;	
	AtomParamWrapper params(rCut);
	params.push_back(AtomParams(1, 1.2, 1));
	params.push_back(AtomParams(1.2, 1.2, 1));
	InteractionParams interactionParams(params);
	//need new way of populating to base it on params
	int gridSize = 4;
	Bounds b(Vector(0, 0, 0), Vector(10, 10, 10));
	Run run(b, interactionParams, gridSize, .005, 50);
	InitializeAtoms::populateOnGrid(run.atoms, run.grid.bounds, params[1], 1000);
	
	run.grid.updateAtoms(run.atoms);
	run.periodic[0] = true; 
	run.periodic[1] = true; 
	run.periodic[2] = true; 
	
	//declaring fixes.  Make some cleaner way of doing this
	FixLjCut ljForce(run.atoms, run.atoms, run.data, run.params, run.rCut);
	run.fixes.push_back(&ljForce);


	//end fixed

	for (Atom *a : run.atoms) {
		cout << a->id << endl;
	}

	const int numTurns = 10000;
	run.rCut = params.rCut;
	run.padding = 0.5;
	
	Integrate::run(run, 0, numTurns);
	//g.buildNeighborLists(thresh, loops);

}
