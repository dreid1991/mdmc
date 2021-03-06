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
#include "AtomParams.h"
#include "InteractionParams.h"
#include "InitializeAtoms.h"
using namespace std;
//If using windows, need visual studio 2012 or newer


int main() {
	/*currently this code is set up with two species populating a 15*15*15 box.  Each species is being initialized to occupy about half the box.  
	 *
	 *
	 */
	const double rCut = 2.5;	
	const double padding = 0.5;
	AtomParamWrapper params(rCut);
	params.push_back(AtomParams(1, 1, 3));
	params.push_back(AtomParams(1.2, 1.2, 4));
	InteractionParams interactionParams(params);
	Bounds region1(Vector(0, 0, 0), Vector(7.5, 15.0, 15.0));

	int gridSize = 4;
	Bounds b(Vector(0, 0, 0), Vector(16, 16, 16));
	double temp = 1.5;
	Run run(b, interactionParams, gridSize, 1000, temp);
	run.padding = padding;
	run.rCut = params.rCut;
	InitializeAtoms::populateOnGrid(run.atoms, region1, params[0], 700);
	//InitializeAtoms::populateOnGrid(run.atoms, region2, params[1], 700);
	
	
	//declaring fixes.  A fix is just an arbitrary operation that applies forces to atoms
	
	
	//end fixes

	const int numTurns = 30000;
	Integrate::run(run, numTurns);

//	cout << run.dangerousRebuilds << " dangerous rebuilds " << endl;
}
