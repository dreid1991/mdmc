#include "Atom.h"
#include "Bounds.h"
#include "AtomGrid.h"
#include "Grid.h"
#include "Vector.h"
#include "Bounds.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include "RunParams.h"
#include "Integrate.h"
using namespace std;


//have do turn first, do turn functions in Integrate.  Have turn first be all same but w/ aLast = aCur.  Hopefully don't have to copy everything

int main() {
	vector<Atom *> atoms;
	int gridSize = 4;
	Bounds b(Vector(0, 0, 0), Vector(10, 10, 10));
	RunParams run(atoms, b, gridSize, .005, 50);
	run.grid.bounds.populateOnGrid(run.atoms, 1000);

	run.periodic[0] = true; 
	run.periodic[1] = true; 
	run.periodic[2] = true; 

	const int numTurns = 10000;
	run.rCut= 1.75;
	run.padding = 0.5;
	
	for (int turn=0; turn<numTurns; turn++) {
		
	}
	//g.buildNeighborLists(thresh, loops);

}
