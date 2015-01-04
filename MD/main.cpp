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
	Bounds b(Vector(0, 0, 0), Vector(10, 10, 10));
	vector<Atom *> atoms;
	b.populateOnGrid(atoms, 100);
	AtomGrid g(atoms, b, 1, 1, 1);
	cout << g.ns[0] << endl;
	bool loops[3] = {true, true, true};
	Atom **elem = &g(1, 0, 0);
	cout << g.posElem(elem).asStr() << endl;
	g.buildNeighborLists(1.2, loops);

}
