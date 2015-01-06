#include "Integrate.h"

void Integrate::verletPreForce(vector<Atom *> &atoms, float dt) {
	float dtSqr = dt*dt;
	float halfDtSqr = dtSqr/2;
	for (Atom *a : atoms) {
		a->pos += a->vel * dt + a->force * halfDtSqr; 
		a->forceLast = a->force;
	}
}


void Integrate::verletPostForce(vector<Atom *> &atoms, float dt) {
	float halfDt = .5 * dt;
	for (Atom *a : atoms) {
		a->vel += (a->forceLast + a->force) * halfDt;
	}
}


void Integrate::applyForces() {};

void Integrate::firstTurn(RunParams &params) {
	
}

void Integrate::run(RunParams &params, int turn, int numTurns) { //current turn should be 0 on first turn
	vector<Atom *> &atoms = params.atoms;
	AtomGrid &grid = params.grid;
	float rCut = params.rCut;
	float padding = params.padding;
	bool periodic[3];
	for (int i=0; i<3; i++) {
		periodic[i] = params.periodic[i];
	}
	int reNeighborListCheck = params.reNeighborListCheck;
	float dt = params.timestep;
	if (turn==0) {
		firstTurn(params);
		turn++;
	}
	for (; turn<numTurns; turn++) {
		if (! turn%reNeighborListCheck && checkReNeighbor(atoms, padding)) {
			grid.buildNeighborLists(rCut, periodic);
		}
		verletPreForce(atoms, dt);
		applyForces();
		verletPostForce(atoms, dt);
	}
}


bool Integrate::checkReNeighbor(vector<Atom *> &atoms, float movementThresh) {
	float threshSqr = movementThresh*movementThresh;
	for (Atom *a : atoms) {
		if (a->pos.distSqr(a->posAtNeighborListing) > threshSqr) { //HEY - this is dangerous because we're only rebuiding once at least one atom has moved too far, so we could be integrating for non-checking turns with relevant forces not being calculated
			return true;
		}
	}
	return false;
}
