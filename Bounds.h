#ifndef BOUNDS_H
#define BOUNDS_H
#include "Vector.h"
#include <string>
#include <stdio.h>
#include "Atom.h"
#include <assert.h>
using namespace std;
class Bounds {
	public:
		Vector lo;
		Vector hi;
		Vector trace;
		Bounds() {

		}
		Bounds(Vector &lo_, Vector &hi_) : lo(lo_), hi(hi_), trace(hi - lo) {
		}
		Bounds(Vector lo_, Vector hi_) : lo(lo_), hi(hi_), trace(hi - lo) {
		}
		
		string asStr() {
			
			string loStr = "Lower bounds " + lo.asStr();
			string hiStr = "upper bounds " + hi.asStr();
			return loStr + ", " + hiStr ;
		}
		bool atomInBounds(Atom *);
		void resize(int dim, NT mult, NT around);
		bool operator == (Bounds &b) {
			for (int i=0; i<NDIM; i++) {
				if (not (fabs(b.lo[i] - lo[i])<EPSILON and fabs(b.hi[i] - hi[i])<EPSILON)) {
					return false;
				}
			}
			return true;
		}
		void populateOnGrid(vector<Atom *> &atoms, unsigned int n);
	

};

extern Bounds nullBounds;

#endif
