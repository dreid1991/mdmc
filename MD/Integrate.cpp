#include "Integrate.h"

void Integrate::verletPreForce(vector<Atom *> &atoms, float dt) {
	float dtSqr = dt*dt;
	float halfDtSqr = dtSqr/2;
	for (Atom *a : atoms) {
		a->pos += a->vel * dt + a->force * (halfDtSqr / a->m); 
		a->forceLast = a->force;
		a->force.zero();
	}
}


void Integrate::verletPostForce(vector<Atom *> &atoms, float dt) {
	float halfDt = .5 * dt;
	for (Atom *a : atoms) {
		a->vel += (a->forceLast + a->force) * (halfDt / a->m);
	}
}


void Integrate::applyForces(vector<Fix *> &fixes, int turn) {
	for (Fix *fix : fixes) {
		if (! (turn % fix->applyEvery)) {
			fix->applyForces();
		}
	}
};

void Integrate::firstTurn(Run &params) {
	params.grid.buildNeighborLists(params.rCut, params.periodic);
	verletPreForce(params.atoms, params.timestep);
	applyForces(params.fixes, 0);
	for (Atom *a : params.atoms) {
		a->forceLast = a->force;
	}
	verletPostForce(params.atoms, params.timestep);
}

void Integrate::run(Run &params, int turn, int numTurns) { //current turn should be 0 on first turn
	vector<Atom *> &atoms = params.atoms;
	vector<Fix *> &fixes = params.fixes;
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
			grid.enforcePeriodic();
			grid.buildNeighborLists(rCut, periodic);
		}
		verletPreForce(atoms, dt);
		applyForces(fixes, turn);
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
