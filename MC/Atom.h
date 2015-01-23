#ifndef ATOM_H
#define ATOM_H
#include "Vector.h"
#include <vector>
#include "OffsetObj.h"


class MoveType;
class Atom;
typedef OffsetObj<Atom *> Neighbor;
typedef vector<Atom *> atomlist;
class Atom {
	public:
		Vector pos;
		Vector posAtNeighborListing;
		Vector virial;
		Atom *next;
		double energy;
		double m;
		int type;
		int id;
		vector<Neighbor> neighbors;
		vector<MoveType *> moveTypes;
		Atom (Vector pos_, double m_, int type_, int id_) : pos(pos_), next((Atom *) NULL), m(m_), type(type_), id(id_), energy(0) {};
		Atom () {};

};

#endif


