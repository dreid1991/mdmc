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
//If using windows, need visual studio 2012 or newer


int main() {
	const float rCut = 1.75;	
	AtomParamWrapper params(rCut);
	params.push_back(AtomParams(1, 1.2, 2));
	params.push_back(AtomParams(1.2, 1.2, 1));
	InteractionParams interactionParams(params);
	
	int gridSize = 4;
	Bounds b(Vector(0, 0, 0), Vector(10, 10, 10));
	Run run(b, interactionParams, gridSize, 1, 1);
	InitializeAtoms::populateOnGrid(run.atoms, run.grid.bounds, params[1], 200);
	InitializeAtoms::initTemp(run.atoms, 2.2);
	
	float sumKe = 0;
	for (Atom *a : run.atoms) {
		sumKe += a->kinetic();
		cout << sumKe << endl;
	}
	cout << "temp " << sumKe / 3.0 / (float) run.atoms.size() << endl;

	for (Atom *a : run.atoms) {
	//	cout << a->pos.asStr() << endl;
	}
	run.periodic[0] = true; 
	run.periodic[1] = true; 
	run.periodic[2] = true; 
	
	//declaring fixes.  Make some cleaner way of doing this
	//FixLjCut ljForce(run.atoms, run.atoms, run.data, run.params, run.rCut);
	//run.fixes.push_back(&ljForce);
	FixTest fTest(run.atoms, run.atoms, run.data, 1);
	run.fixes.push_back(&fTest);
	//end fixed

	//for (Atom *a : run.atoms) {
	//	cout << a->id << endl;
	//}

	const int numTurns = 21;
	run.rCut = params.rCut;
	run.padding = 0.5;
	run.atoms[0]->vel = Vector(1, 0, 0);
	//Integrate::run(run, 0, numTurns);

}
