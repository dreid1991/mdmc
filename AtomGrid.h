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
	void setGridRaws();
	public:
		Bounds bounds;
		atomlist atoms;
		AtomGrid(Bounds b_, double dx_, double dy_, double dz_) : Grid(ceil(b_.trace[0]/dx_), ceil(b_.trace[1]/dy_), ceil(b_.trace[2]/dz_), Vector(dx_, dy_, dz_), b_.lo), bounds(b_) {
			setGridRaws();
		};
		//void assignNeighbors(const double rad, bool loopX, bool loopY, bool loopZ);
		//vector<Neighbor> getNeighborSquares(const int x, const int y, const int z, const bool loopX, const bool loopY, const bool loopZ);
		//atomlist selectFromBounds(Bounds);
};

#endif
