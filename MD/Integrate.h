#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include "Atom.h"
#include <vector>
#include "RunParams.h"
using namespace std;
namespace Integrate {
	void verletPreForce(vector<Atom *> &atoms, float timestep);
	void verletPostForce(vector<Atom *> &atoms, float timestep);
	void applyForces();
	void firstTurn(RunParams &params);
	void run(RunParams &params, int currentTurn, int numTurns);
	//void 
	bool checkReNeighbor(vector<Atom *> &atoms, float);
}

#endif
