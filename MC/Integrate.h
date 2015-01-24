#ifndef RUN_H
#define RUN_H
#include "Run.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
namespace Integrate {
	double singleEnergy(Atom *a);
	void setEnergies(vector<Atom *> &atoms, InteractionParams &params, double rCut);
	bool singleDisplacement(Atom *a, double rMax, double temp);
	void run(Run &params, int numTurns);
}

#endif
