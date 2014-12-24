#ifndef ATOMGRID_H
#define ATOMGRID_H
#include "Grid.h"
#include "Bounds.h"
#include "Atom.h"
#include <math.h>
#include "OffsetObj.h"
#include <iostream>
#include <vector>
using namespace std;
class AtomGrid : public Grid<Atom *> {
	void populateGrid() {
	}
	//void sliceBounds(double *, double *, double *, double *, double *, double *);
	//atomlist atomsInNonLoopingBounds(Bounds b);
	public:
		Bounds bounds;
		atomlist &atoms;
		AtomGrid(vector<Atom *> &atoms, Bounds b_, float dx_, float dy_, float dz_) : Grid(ceil(b_.trace[0]/dx_), ceil(b_.trace[1]/dy_), ceil(b_.trace[2]/dz_), Vector(dx_, dy_, dz_), b_.lo, (Atom *) NULL ), bounds(b_) {
			saveRaw();
		};
		void buildNeighborLists(float thresh, bool *loops);
		//atomlist selectFromBounds(Bounds);
};

#endif
