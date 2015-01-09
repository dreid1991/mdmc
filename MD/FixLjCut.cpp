#include "FixLjCut.h"


FixLjCut::applyForces() {
	float rCutSqrLoc = rCutSqr;
	for (Atom *a : atoms) {
		int idA = a->id;
		for (Neighbor &n : a->neighbors) {
			Atom *b = n.obj;
			int idB = b->id;
			Vector distance = a->pos - (b->pos + n.offset);
			float drSqr = distance->lenSqr();
			if (drSqr < rCutSqrLoc) {
				float r2inv = 1/drSqr;
				float r6inv = r2inv*r2inv*r2inv;
				float ljparam1 = params.getParam1(idA, idB);
				float ljparam2 = params.getParam2(idA, idB);
				float force = r6inv * (ljparam1 * r6inv - ljparam2);

			}
		}
	}
}
