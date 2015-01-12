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
	//Bounds region1(Vector(0, 0, 0), Vector(7.5, 15.0, 15.0));
	//Bounds region2(Vector(8.0, 0.1, 0.1), Vector(14.9, 14.9, 14.9));

	int gridSize = 4;
	Bounds b(Vector(0, 0, 0), Vector(16, 16, 16));
	Run run(b, interactionParams, gridSize, .005, 1, 1);
	run.moreData.push_back(vector<double>());
	run.moreData.push_back(vector<double>());
	run.moreData.push_back(vector<double>());
	run.moreData.push_back(vector<double>());
	run.moreData.push_back(vector<double>());
	run.padding = padding;
	run.rCut = params.rCut;
//	InitializeAtoms::populateOnGrid(run.atoms, region1, params[0], 700);
//	InitializeAtoms::populateOnGrid(run.atoms, region2, params[1], 700);
	/*run.atoms.push_back(new Atom(Vector(2.5, 3, 3), 1, 0, 1));
	run.atoms.push_back(new Atom(Vector(15, 3, 3), 1, 0, 1));
	
	run.atoms[1]->vel = Vector(.1, 0, 0);*/
	run.atoms.push_back(new Atom(Vector(13, 3, 3), 1, 0, 1));
	run.atoms.push_back(new Atom(Vector(2.0, 3, 3), 1, 0, 1));
	
	run.atoms[0]->vel = Vector(.1, 0, 0);
//run.atoms.push_back(new Atom(Vector(5.5, 3, 3), 1, 0, 1));
//	run.atoms.push_back(new Atom(Vector(5.5, 4.5, 3), 1, 0, 1));
//	double temp = 0.1;
//	InitializeAtoms::initTemp(run.atoms, temp);
	
	//declaring fixes.  A fix is just an arbitrary operation that applies forces to atoms
	
	FixLjCut ljForce(run.atoms, run.atoms, run.data, run.params, run.rCut);
	run.fixes.push_back(&ljForce);

//	FixNVT constTemp(run.atoms, run.atoms, run.data, temp, 30);
//	run.fixes.push_back(&constTemp);
	
	//end fixes

	const int numTurns = 80000;
	Integrate::run(run, 0, numTurns);
 	FILE *fptr = fopen("out.dat", "w");

	for (vector<double> &dat : run.moreData) {
		for (double x : dat) {
			fprintf(fptr, "%f ", x);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}
