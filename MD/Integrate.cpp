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


void Integrate::addKineticEnergy(vector<Atom *> &atoms, Data &simData) {
	for (Atom *a : atoms) {
		simData.eng.kinetic += a->kinetic();
	}
}

void Integrate::compute(vector<Fix *> &fixes, int turn) {
	for (Fix *fix : fixes) {
		if (! (turn % fix->applyEvery)) {
			fix->compute();
		}
	}
};

void Integrate::firstTurn(Run &params) {
	params.grid.buildNeighborLists(params.rCut, params.periodic);
	addKineticEnergy(params.atoms, params.data);
	verletPreForce(params.atoms, params.timestep);
	compute(params.fixes, 0);
	for (Atom *a : params.atoms) {
		a->forceLast = a->force;
	}
	verletPostForce(params.atoms, params.timestep);
}

void Integrate::run(Run &params, int turn, int numTurns) { //current turn should be 0 on first turn
	const int dataInterval = params.dataInterval;
	vector<Atom *> &atoms = params.atoms;
	vector<Fix *> &fixes = params.fixes;
	AtomGrid &grid = params.grid;
	Data &simData = params.data;
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
		//cout << atoms[27]->pos.asStr() << endl;
		//cout << atoms[27]->vel.asStr() << endl<<endl;
		if (! (turn%reNeighborListCheck) && checkReNeighbor(atoms, padding)) {
			grid.enforcePeriodic();

			grid.buildNeighborLists(rCut, periodic);
		}
		addKineticEnergy(atoms, simData);
		verletPreForce(atoms, dt);
		compute(fixes, turn);
		verletPostForce(atoms, dt);

		if (! (turn % dataInterval)) {
			setThermoValues(params);
		}
	}
}

void Integrate::setThermoValues(Run &params) {
	Data &simData = params.data;
	vector<Atom *> &atoms = params.atoms;
	int dataInterval = params.dataInterval;
	float avgKinetic = simData.eng.kinetic / dataInterval;
	float avgPotential = simData.eng.potential / dataInterval;
	float temp = avgKinetic * (2.0 / 3) / (float) atoms.size();
	float volume = params.grid.bounds.volume();
	float density = atoms.size() / volume;
	float pressure = density * temp + simData.virialTotal / volume / atoms.size();
	simData.avgs.engKinetic = avgKinetic;
	simData.avgs.engPotential = avgPotential;
	simData.avgs.engTotal = avgPotential + avgKinetic;
	simData.avgs.temp = temp;
	simData.avgs.press = pressure;

	simData.eng.kinetic = 0;
	simData.eng.potential = 0;
	simData.virialTotal = 0;
	cout << pressure << endl;
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
