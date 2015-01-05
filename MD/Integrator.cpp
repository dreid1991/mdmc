#include "Integrator.h"

void Integrator::verletPreForce(vector<Atom *> &atoms, float dt) {
	float dtSqr = dt*dt;
	float halfDtSqr = dtSqr/2;
	for (Atom *a : atoms) {
		a->pos += a->vel * dt + a->force * halfDtSqr; 
		a->forceLast = a->force;
	}
}


void Integrator::verletPostForce(vector<Atom *> &atoms, float dt) {
	float halfDt = .5 * dt;
	for (Atom *a : atoms) {
		a->vel += (a->forceLast + a->force) * halfDt;
	}
}
