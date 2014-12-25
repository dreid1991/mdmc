#include "Atom.h"
#include "Bounds.h"
#include "AtomGrid.h"
#include "Grid.h"
#include "Vector.h"
#include "Bounds.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
	Vector ds(1, 1, 1);
	Vector os(0, 0, 0);
	Grid <double> g(5, 5, 5, ds, os, 1);
	vector<double> vals;
	for (int i=0; i<125; i++) {
		vals.push_back(i);
	}
	g.setRaw(vals);
	/*
	Bounds b(Vector(0, 0, 0), Vector(10, 10, 10));
	vector<Atom *> atoms;
	b.populateOnGrid(atoms, 100);
	AtomGrid g(atoms, b, 3, 3, 3);
	bool loops[3] = {true, true, true};
	g.buildNeighborLists(1.2, loops);
	*/
	/*for (Atom *a : atoms) {
		cout << a->pos.asStr() << endl;
	}*/

}
