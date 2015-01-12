#include "Integrate.h"

void Integrate::verletPreForce(vector<Atom *> &atoms, double dt) {
	double dtSqr = dt*dt;
	double halfDtSqr = dtSqr/2;
	for (Atom *a : atoms) {
		a->pos += a->vel * dt + a->force * (halfDtSqr / a->m); 
		a->forceLast = a->force;
		a->force.zero();
	}
}


void Integrate::verletPostForce(vector<Atom *> &atoms, double dt) {
	double halfDt = .5 * dt;
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
	double rCut = params.rCut;
	double padding = params.padding;
	bool periodic[3];
	for (int i=0; i<3; i++) {
		periodic[i] = params.periodic[i];
	}
	int reNeighborListCheck = params.reNeighborListCheck;
	double dt = params.timestep;
	if (turn==0) {
		firstTurn(params);
		turn++;
	}
	for (; turn<numTurns; turn++) {
		if (! (turn%reNeighborListCheck) && checkReNeighbor(atoms, padding)) {
			bool enforce = grid.enforcePeriodic();
			if (enforce) {
				cout << turn << endl;
			}

			grid.buildNeighborLists(rCut, periodic);
		}
		addKineticEnergy(atoms, simData);
		verletPreForce(atoms, dt);
		compute(fixes, turn);
		verletPostForce(atoms, dt);

		if (! (turn % dataInterval)) {
			setThermoValues(params);
		}
	//	cout << atoms[0]->pos[0] << " ";
	}
}

void Integrate::setThermoValues(Run &params) {
	Data &simData = params.data;
	vector<Atom *> &atoms = params.atoms;
	int dataInterval = params.dataInterval;
	double avgKinetic = simData.eng.kinetic / dataInterval;
	double avgPotential = simData.eng.potential / dataInterval;
	double temp = avgKinetic * (2.0 / 3) / (double) atoms.size();
	double volume = params.grid.bounds.volume();
	double density = atoms.size() / volume;
	double pressure = density * temp + simData.virialTotal / volume / atoms.size();
	simData.avgs.engKinetic = avgKinetic;
	simData.avgs.engPotential = avgPotential;
	simData.avgs.engTotal = avgPotential + avgKinetic;
	simData.avgs.temp = temp;
	simData.avgs.press = pressure;

	simData.eng.kinetic = 0;
	simData.eng.potential = 0;
	simData.virialTotal = 0;
	//IF YOU WOULD LIKE TO OUTPUT DATA, THIS WOULD BE A GODO PLACE TO DO IT.  Example below
//	cout << simData.avgs.engTotal << " ";
	//cout << simData.avgs.engKinetic << " ";
	

//	params.moreData[0].push_back(params.atoms[1]->pos[0] - params.atoms[0]->pos[0]);
//	params.moreData[1].push_back(simData.avgs.engPotential);
	params.moreData[2].push_back(simData.avgs.engTotal);
	params.moreData[0].push_back(params.atoms[0]->pos[0]);
	params.moreData[1].push_back(params.atoms[1]->pos[0]);
	params.moreData[3].push_back(params.atoms[1]->neighbors.size());
	double x1 = params.atoms[0]->pos[0];
	double x2 = params.atoms[1]->pos[0];
	double dx = fabs(x1 - x2);
	double trace = params.grid.bounds.trace[0];
	if (dx > trace/2) {
		if (x2 > x1) {
			x2 -= trace;
		} else {
			x1 -= trace;
		}
	}

	if (dx > params.grid.bounds.trace[0]/2) {
		dx -= params.grid.bounds.trace[0]/2;
	}
	params.moreData[4].push_back(fabs(x1 - x2));
}

bool Integrate::checkReNeighbor(vector<Atom *> &atoms, double movementThresh) {
	double threshSqr = movementThresh*movementThresh;
	for (Atom *a : atoms) {
		if (a->pos.distSqr(a->posAtNeighborListing) > threshSqr) { //HEY - this is dangerous because we're only rebuiding once at least one atom has moved too far, so we could be integrating for non-checking turns with relevant forces not being calculated
			return true;
		}
	}
	return false;
}
