#ifndef BOUNDS_H
#define BOUNDS_H
#include "Vector.h"
#include <string>
#include <stdio.h>
#include "Atom.h"
#include "BoundsGeneric.h"
#include <assert.h>
using namespace std;
class Bounds : public BoundsGeneric {
	public:
		Bounds() {

		}
		Bounds(Vector &lo_, Vector &hi_) : BoundsGeneric(lo, hi) {
		}
		Bounds(Vector lo_, Vector hi_) : BoundsGeneric(lo, hi) {
		}
		
		string asStr() {
			
			string loStr = "Lower bounds " + lo.asStr();
			string hiStr = "upper bounds " + hi.asStr();
			return loStr + ", " + hiStr ;
		}
		bool atomInBounds(Atom *);
		void populateOnGrid(vector<Atom *> &atoms, unsigned int n);
	

};

extern Bounds nullBounds;

#endif
