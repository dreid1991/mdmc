#ifndef RUN_H
#define RUN_H
#include "Run.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
namespace Intergate {
	setEnergies(vector<Atom *> &atoms, InteractionParams &params, double rCut);
	singleDisplacement(Atom *a, double rMax, double temp);
	run(Run &params, int numTurns);
}

#endif
