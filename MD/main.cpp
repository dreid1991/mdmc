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
	AtomGrid g(atoms, b, 5, 5, 5);
	cout << g.ns[0] << endl;
	bool loops[3] = {true, true, true};
//	Atom **elem = &g(1, 0, 0);
//	cout << g.posElem(elem).asStr() << endl;
//	cout << "HAAA" << endl;cout.flush();
	g.buildNeighborLists(2.5, loops);
	//for (Atom *a : atoms) {
	//	cout << a->neighbors.size() << endl;
	//};
	for (int i=0; i<3; i++) {
		cout << g.ns[i] << endl;
	}	
	cout << "a" << endl;
	for (Atom *a : g.raw) {
		int numItems = 0;
		for (Atom *current = a; current != (Atom *) NULL; current = current->next) {
			cout << current->pos.asStr() << endl;
			numItems++;
		}
		cout<< numItems << endl;
	}
	/*
	vector<Atom *> lala;
	for (int i=0; i<10; i++) {
		lala.push_back(new Atom(Vector((float) i, (float) 1, (float) 1)));
	}
	AtomGrid g(lala, b, 1, 1, 1);
	Atom **gelem = &g(0, 0, 0);
	for (int i=0; i<(int) lala.size(); i++) {
		Atom *cur = lala[i];
		cur->next = *gelem;
		*gelem = cur;
	}
	for (Atom *current=*gelem; current!=(Atom*)NULL; current=current->next) {
		cout << current->pos[0] << endl;
	}
	*/
}
