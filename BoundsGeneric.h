#ifndef BOUNDS_GENERIC_H
#define BOUNDS_GENERIC_H

#include "Vector"

class BoundsGeneric {
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
		void resize(int dim, float mult, float around) {
			float hiDim = hi[dim];
			float loDim = lo[dim];
			float origin = loDim + around * (hiDim - loDim);
			hi[dim] = mult * (hiDim - origin) + origin;
			lo[dim] = mult * (loDim - origin) + origin;
			trace[dim] *= mult;
		}
		bool operator == (BoundsGeneric &b) {
			for (int i=0; i<NDIM; i++) {
				if (not (fabs(b.lo[i] - lo[i])<EPSILON and fabs(b.hi[i] - hi[i])<EPSILON)) {
					return false;
				}
			}
			return true;
		}
}
#endif
