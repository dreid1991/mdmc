#include "FixLjCut.h"


void FixLjCut::applyForces() {
	float sumEngs = 0;
	Vector virialComps;
	float rCutSqrLoc = rCutSqr;
	for (Atom *a : atoms) {
		int idA = a->id;
		for (Neighbor &n : a->neighbors) {
			Atom *b = n.obj;
			int idB = b->id;
			Vector distance = a->pos - (b->pos + n.offset);
			float drSqr = distance.lenSqr();
			if (drSqr < rCutSqrLoc) {
				float r2inv = 1/drSqr;
				float r6inv = r2inv*r2inv*r2inv;
				float ljparam1 = params.getParam1(idA, idB);
				float ljparam2 = params.getParam2(idA, idB);
				float ljparam3 = params.getParam3(idA, idB);
				float ljparam4 = params.getParam4(idA, idB);
				float offset = params.getOffset(idA, idB);
				float force = r2inv * r6inv * (ljparam1 * r6inv - ljparam2);
				Vector forceVec = distance * force;
				a->force += forceVec;
				b->force -= forceVec;
				float eng = r6inv * (ljparam3 * r6inv - ljparam4) - offset;
				sumEngs += eng;
				virialComps += forceVec * offset;

			}
		}
	}
	simData.eng.potential += sumEngs;
	simData.virialTotal += virialComps.sum() / 3;
}
