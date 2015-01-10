#include "FixLjCut.h"


void FixLjCut::compute() {
	float sumEngs = 0;
	Vector virialComps;
	float rCutSqrLoc = rCutSqr;
	for (Atom *a : atoms) {
		int typeA = a->type;
		for (Neighbor &n : a->neighbors) {
			Atom *b = n.obj;
			int typeB = b->type;
			Vector distance = a->pos - (b->pos + n.offset);
			float drSqr = distance.lenSqr();
			if (drSqr < rCutSqrLoc) {
				float ljparam1 = params.getParam1(typeA, typeB); 
				float ljparam2 = params.getParam2(typeA, typeB); 
				float r2inv = 1 / drSqr;
				float r6inv = r2inv*r2inv*r2inv;
				float ljparam3 = params.getParam3(typeA, typeB);
				float ljparam4 = params.getParam4(typeA, typeB);
				float offset = params.getOffset(typeA, typeB);
				float forceScalar = r6inv / drSqr * (ljparam1 * r6inv - ljparam2);
				Vector forceVec = distance * forceScalar;
				a->force += forceVec;
				b->force -= forceVec;
				float eng = r6inv * (ljparam3 * r6inv - ljparam4) - offset;
				sumEngs += eng;
				virialComps += forceVec * distance;

			}
		}
	}
	simData.eng.potential += sumEngs;
	simData.virialTotal += virialComps.sum() / 3;
}
