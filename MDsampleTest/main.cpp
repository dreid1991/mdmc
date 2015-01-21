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


int main(int argc, const char *argv[]) {
	/*currently this code is set up with two species populating a 15*15*15 box.  Each species is being initialized to occupy about half the box.  
	 *
	 *
	 */

	const int dataInt = atoi(argv[1]);
	const int turnsEquil = 50000;
	const int turnsRun = 500000;
	cout << "NEW RUN" << endl;
	cout << turnsEquil << " " << turnsRun << " " << dataInt << endl;
	const double rCut = 2.5;	
	const double padding = 0.5;
	AtomParamWrapper params(rCut);
	params.push_back(AtomParams(1, 1, 3));
	//params.push_back(AtomParams(1.2, 1.2, 4));
	InteractionParams interactionParams(params);
//	Bounds region1(Vector(0, 0, 0), Vector(7.5, 15.0, 15.0));
//	Bounds region2(Vector(8.0, 0.1, 0.1), Vector(14.9, 14.9, 14.9));

	int gridSize = 4;
	Bounds b(Vector(0, 0, 0), Vector(20, 20, 20));
	Run run(b, interactionParams, gridSize, .005, 15, dataInt);
	run.padding = padding;
	run.rCut = params.rCut;
	InitializeAtoms::populateOnGrid(run.atoms, b, params[0], 1600);
//	InitializeAtoms::populateOnGrid(run.atoms, region2, params[1], 700);
	
	double temp = 1.5;
	InitializeAtoms::initTemp(run.atoms, temp);
	
	//declaring fixes.  A fix is just an arbitrary operation that applies forces to atoms
	
	FixLjCut ljForce(run.atoms, run.atoms, run.data, run.params, run.rCut);
	run.fixes.push_back(&ljForce);

	FixNVT constTemp(run.atoms, run.atoms, run.data, temp, 30);
	run.fixes.push_back(&constTemp);
	
	//end fixes

	const int numTurns = turnsEquil + turnsRun;
	Integrate::run(run, 0, numTurns);

//	cout << run.dangerousRebuilds << " dangerous rebuilds " << endl;
}
