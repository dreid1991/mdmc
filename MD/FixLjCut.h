
#ifndef FIXLJCUT_H
#define FIXLJCUT_H
#include "InteractionParams.h"

class FixLjCut : public Fix {
	FixLjCut(vector<Atom *> &allAtoms_, Data &simData_, InteractionParams &params_, float rCut) : Fix(allAtoms_, simData_), params(params_), rCutSqr(rCur*rCut) {};
	InteractionParams params;
	void applyForces();
	float rCutSqr;
};


#endif
