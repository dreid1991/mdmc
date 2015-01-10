#ifndef ATOMGRID_H
#define ATOMGRID_H
#include "Grid.h"
#include "Bounds.h"
#include "Atom.h"
#include <math.h>
#include "OffsetObj.h"
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;
class AtomGrid : public Grid<Atom *> {
	void populateGrid() {
	}
	void appendNeighborList(Atom *, OffsetObj<Atom **> &, float);
	//void sliceBounds(double *, double *, double *, double *, double *, double *);
	//atomlist atomsInNonLoopingBounds(Bounds b);
	//void buildGridLinkedList();
	public:
		void enforcePeriodic();
		void updateAtoms(vector<Atom *> &);
		Bounds bounds;
		atomlist &atoms;
		AtomGrid(vector<Atom *> &atoms_, Bounds b_, float dx_, float dy_, float dz_) : Grid(VectorInt((int) ceil(b_.trace[0]/dx_), (int) ceil(b_.trace[1]/dy_), (int) ceil(b_.trace[2]/dz_)), Vector(dx_, dy_, dz_), b_.lo, (Atom *) NULL ), bounds(b_), atoms(atoms_) {
			saveRaw();
		};
		void buildNeighborLists(float thresh, bool loops[3]);
		//atomlist selectFromBounds(Bounds);
};

#endif
