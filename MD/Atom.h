#ifndef ATOM_H
#define ATOM_H
#include "globals.h"
#include "Vector.h"
#include <vector>
#include "OffsetObj.h"


class Atom;
typedef OffsetObj<Atom *> Neighbor;
typedef vector<Atom *> atomlist;
class Atom {
	public:
		Vector pos;
		Vector vel;
		Vector force;
		Vector forceLast;
		Vector posAtNeighborListing;
		Atom *next;
		float m;
		vector<Neighbor> neighbors;
		Atom (Vector pos_) : pos(pos_), next((Atom *) NULL), m(0) {};
		Atom () {};


};

#endif


