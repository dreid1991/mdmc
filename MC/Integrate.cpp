#include "Integrate.h"



Integrate::setEnergies(vector<Atom *> &atoms, InteractionParams &params, double rCut) {
	
	double rCutSqr = rCut * rCut;
	for (Atom *a : atoms) {
		Vector virialComps;
		double atomEng = 0;
		int typeA = a->type;
		for (Neighbor &n : a->neighbors) {
			Atom *b = n.obj;
			Vector distance = a->pos - (b->pos + n.offset);
			double drSqr = distance.lenSqr();
			if (drSqr < rCutSqrLoc) {
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

Integrate::singleDisplacement(Atom *, double dispMax, double temp) {
	double r = sqrt(rand() / (double) RAND_MAX);
}

Integrate::run(Run &params, int numTurns) {
	assert(numTurns >= 0);
	vector<Atom *> &atoms = params.atoms;
	AtomGrid &grid = params.grid;
	InteractionParams intParams = params.params; //eugh
	double temp = params.temp;
	double dispMax = 1;
	double rCut = params.rCut;
	setInitEnergies(atoms, intParams, rCut);
	for (int i=0; i<numTurns; i++) {
		run.currentTurn = i;
		//do displacement
		//after ddisplacement, only need to update energies of my neighbors
		Atom *toMove = atoms[rand() % atoms.size()];
		singleDisplacement(toMove, dispMax, temp);
	}

}
