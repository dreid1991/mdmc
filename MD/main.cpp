#include "Atom.h"
#include "Bounds.h"
#include "AtomGrid.h"
#include "Grid.h"
#include "Vector.h"
#include "Bounds.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	Bounds b(Vector(0, 0, 0), Vector(10, 10, 10));
	vector<Atom *> atoms;
	b.populateOnGrid(atoms, 1000);
	/*
	for (int i=9; i<1 || i>=9; i++) {
		atoms.push_back(new Atom(Vector(5, i, 5)));
		atoms.push_back(new Atom(Vector(6, i, 5)));
		if (i==9) {
			i=-1;
		}
	}
	*/
	for (Atom *a : atoms) {
		cout << a->pos.asStr() << endl;
	}
	/*
	atoms.push_back(new Atom(Vector((float) 5.5, (float) 9.5, (float) 5)));
	cout << "poses" << endl;
	for (Atom *a : atoms) {
		cout << a->pos.asStr() << endl;
	}
	cout << "poses" << endl;
	*/
	AtomGrid g(atoms, b, 4, 4, 4);
	bool loops[3] = {true, true, true};
//	Atom **elem = &g(1, 0, 0);
//	cout << g.posElem(elem).asStr() << endl;
//	cout << "HAAA" << endl;cout.flush();
	float thresh = 1.74;
	g.buildNeighborLists(thresh, loops);
	cout << "neighbors" << endl;
	int numNeighs = 0;
	vector<int> counts = vector<int>(atoms.size());
	for (Atom *a : atoms) {
	//	cout << a->neighbors.size() << endl;
		counts.push_back(a->neighbors.size());
		numNeighs += a->neighbors.size();
	}
	cout << *max_element(counts.begin(), counts.end()) << endl;
	cout << "num neighs " << numNeighs << endl;
	/*
	int numNeigh = 0;
	for (Atom *a : g.raw) {
		int numItems = 0;
		cout << "new" << endl;
		for (Atom *current = a; current != (Atom *) NULL; current = current->next) {
			cout << current->neighbors.size() << endl;
			numNeigh += current->neighbors.size();
			numItems++;
		}
		//cout<< numItems << endl;
	}
	cout << numNeigh << endl;
	*/

//	cout << it==foo.end() << endl;
/*
	int numWin = 0;
	int numLose = 0;
	Vector halfTrace = b.trace / 2;
	for (Atom *a : atoms) {
		vector<Atom *> aneighs;
		for (OffsetObj<Atom *> &obj : a->neighbors) {
			aneighs.push_back(obj.obj);
		}
		for (Atom *b : atoms) {
			Vector dist = (a->pos - b->pos).abs();
			for (int i=0; i<3; i++) {
				if (dist[i] > halfTrace[i]) {
					dist[i] -= halfTrace[i];
				}
			}
			float len = dist.len();
			if (len <= thresh) {
				vector<Atom *> bneighs;
				for (OffsetObj<Atom *> &obj : b->neighbors) {
					bneighs.push_back(obj.obj);
				}
				auto aIt = find(aneighs.begin(), aneighs.end(), b);
				auto bIt = find(bneighs.begin(), bneighs.end(), a);
				if (aIt != aneighs.end() or bIt != bneighs.end()) {
					cout << "win!" << endl;
					numWin++;
				} else {
					cout << "UH OH" << endl;
					numLose++;
				}
			}

		}
	}
	cout << numWin << " " << numLose << endl;
	*/
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
