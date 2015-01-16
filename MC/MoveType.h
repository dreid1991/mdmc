#ifndef MOVETYPE_H
#define MOVETYPE_H
#include "Atom.h"
//displace different dists, swap
//
//Check if moved too far for each atom move, since swap can go big dists
class MoveType {
	double relativeFreq;
	virtual double proposeMove(Atom *);
}

#endif
