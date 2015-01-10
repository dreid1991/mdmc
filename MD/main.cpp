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
	const float rCut = 2.5;	
	AtomParamWrapper params(rCut);
	params.push_back(AtomParams(1, 1, 3));
	params.push_back(AtomParams(1.2, 1.2, 4));
	InteractionParams interactionParams(params);
	cout << interactionParams.param1.size() << endl;
	Bounds region1(Vector((float) 0, (float) 0, (float) 0), Vector((float) 7.5, (float) 15.0, (float) 15.0));
	Bounds region2(Vector((float) 8.0, (float) 0.1, (float) 0.1), Vector((float) 14.9, (float) 14.9, (float) 14.9));

	int gridSize = 5;
	Bounds b(Vector(0, 0, 0), Vector(15, 15, 15));
	Run run(b, interactionParams, gridSize, .005, 5, 50);
	run.rCut = params.rCut;
	InitializeAtoms::populateOnGrid(run.atoms, region1, params[0], 700);
	InitializeAtoms::populateOnGrid(run.atoms, region2, params[1], 700);
	float temp = 1.1;
	InitializeAtoms::initTemp(run.atoms, temp);
	
	run.periodic[0] = true; 
	run.periodic[1] = true; 
	run.periodic[2] = true; 
	
	//declaring fixes.  Make some cleaner way of doing this
	
	FixLjCut ljForce(run.atoms, run.atoms, run.data, run.params, run.rCut);
	run.fixes.push_back(&ljForce);

	FixNVT constTemp(run.atoms, run.atoms, run.data, temp, 30);
	run.fixes.push_back(&constTemp);
	
	//end fixes

	const int numTurns = 60000;
	run.padding = 0.5;
	Integrate::run(run, 0, numTurns);

}
