
#ifndef FIXTEST_H
#define FIXTEST_H
#include "InteractionParams.h"
#include "Vector.h"
#include "Fix.h"
using namespace std;
class FixTest : public Fix {
	public:
		FixTest(vector<Atom *> &allAtoms_, vector<Atom *> &atoms_, Data &simData_, int applyEvery) : Fix(allAtoms_, atoms_, simData_, applyEvery) {};
		void compute() {
			for (Atom *a : atoms) {
				a->force += Vector((float) .1, (float) .1, (float) .1);
			}
		}
};


#endif
