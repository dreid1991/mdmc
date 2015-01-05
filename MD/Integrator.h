#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include "Atom.h"
#include <vector>
using namespace std;
namespace Integrator {
	void verletPreForce(vector<Atom *> &atoms, float timestep);
	void verletPostForce(vector<Atom *> &atoms, float timestep);
}

#endif
