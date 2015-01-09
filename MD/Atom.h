#ifndef ATOM_H
#define ATOM_H
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
		int id;
		vector<Neighbor> neighbors;
		Atom (Vector pos_, float m_, int id_) : pos(pos_), next((Atom *) NULL), m(m_), id(id_) {};
		Atom () {};
		float kinetic() {
			return 0.5 * m * vel.lenSqr();
		}


};

#endif


