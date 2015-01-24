#include "Integrate.h"

double Integrate::singleEnergy(Atom *a) {
	double eng = 0;
	for (Neighbor &n : a->neighbors) {
		Atom *b = n.obj;
		Vector distance = a->pos - (b->pos + n.offset);
		double drSqr = distance.lenSqr();
		if (drSqr < rCutSqr) {
			int typeB = b->type;
			double r2inv = 1 / drSqr;
			double r6inv = r2inv*r2inv*r2inv;
			double ljparam3 = params.getParam3(typeA, typeB);
			double ljparam4 = params.getParam4(typeA, typeB);
			double offset = params.getOffset(typeA, typeB);
			eng += r6inv * (ljparam3 * r6inv - ljparam4) - offset;
			
		}
	}
	return eng;

}


void Integrate::setEnergies(vector<Atom *> &atoms, InteractionParams &params, double rCut) {
	
	double rCutSqr = rCut * rCut;
	for (Atom *a : atoms) {
		Vector virialComps;
		double atomEng = 0;
		int typeA = a->type;
		for (Neighbor &n : a->neighbors) {
			Atom *b = n.obj;
			Vector distance = a->pos - (b->pos + n.offset);
			double drSqr = distance.lenSqr();
			if (drSqr < rCutSqr) {
				int typeB = b->type;
				double ljparam1 = params.getParam1(typeA, typeB); 
				double ljparam2 = params.getParam2(typeA, typeB); 
				double r2inv = 1 / drSqr;
				double r6inv = r2inv*r2inv*r2inv;
				double ljparam3 = params.getParam3(typeA, typeB);
				double ljparam4 = params.getParam4(typeA, typeB);
				double offset = params.getOffset(typeA, typeB);
				double forceScalar = r6inv / drSqr * (ljparam1 * r6inv - ljparam2);
				Vector forceVec = distance * forceScalar;
				double interactionEng= r6inv * (ljparam3 * r6inv - ljparam4) - offset;

				atomEng += interactionEng;
				virialComps += forceVec * distance;

			}
		}
		a->energy = atomEng;
		a->virial = virialComps;
	}
}

bool Integrate::singleDisplacement(Atom *a, double dispMax, double temp) {
	double r = disp * sqrt(rand() / (double) RAND_MAX);
	double u = 2 * (rand() / (double) RAND_MAX) - 1;
	double theta = 2 * M_PI * rand() / (double) RAND_MAX;
	double x = sqrt(1 - u*u) * cos(theta);
	double y = sqrt(1 - u*u) * sin(theta);
	Vector disp (x, y, u);
	Vector old = a->pos;
	a->pos += disp;
	double trialEng = singleEng(a);
	if (rand() / (double) RAND_MAX < exp((trialEng - a->energy) / temp)) {
		return true;	
	} else {
		a->pos = old;
		return false;
	}


}

void Integrate::run(Run &params, int numTurns) {
	assert(numTurns >= 0);
	vector<Atom *> &atoms = params.atoms;
	AtomGrid &grid = params.grid;
	InteractionParams intParams = params.params; //eugh
	double temp = params.temp;
	double dispMax = 1;
	double rCut = params.rCut;
	setEnergies(atoms, intParams, rCut);
	for (int i=0; i<numTurns; i++) {
		params.currentTurn = i;
		//do displacement
		//after ddisplacement, only need to update energies of my neighbors
		Atom *toMove = atoms[rand() % atoms.size()];
		bool didMove = singleDisplacement(toMove, dispMax, temp);
		if (didMove) {

		}
	}

}
