
#ifndef FIXLJCUT_H
#define FIXLJCUT_H

class FixLjCut : public Fix {
	FixLjCut(vector<Atom *> &allAtoms_, Data &simData_) : Fix(allAtoms_, simData_) {};
	void applyForces() {
	}
};


#endif
