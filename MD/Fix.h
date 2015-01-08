#include "Atom.h"
#include "Data.h"
using namespace std;
class Fix {
	public:
		virtual void applyForces(){};
		vector<Atom *> atoms;
		vector<Atom *> &allAtoms;
		Data &simData;
		virtual void updateAtoms(vector<Atom *> &updatedSet) {};
		virtual void setup(){};
		int applyEvery;
		Fix(vector<Atom*> &allAtoms_, Data &simData_) : allAtoms(allAtoms_), simData(simData_), applyEvery(0) {};
	
};
