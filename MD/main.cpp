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
	AtomGrid g(b, 3, 3, 3);
	cout << atoms.size() << endl;
	for (Atom *a : atoms) {
		cout << a->pos.asStr() << endl;
	}

}
