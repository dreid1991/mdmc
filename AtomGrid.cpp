#include "AtomGrid.h"


void AtomGrid::appendNeighborList(Atom *a, OffsetObj<Atom **> &gridSqr, float threshSqr) {
	if (*gridSqr.obj != (Atom *) NULL) {
		Vector offset = gridSqr.offset;
		Atom *current;
		for (current = *gridSqr.obj; current != (Atom *)NULL; current = current->next) {
			if (a->pos.distSqr(current->pos + offset) <= threshSqr) {
				a->neighbors.push_back(Neighbor(current, offset));	
			}
		}
	}
}

void AtomGrid::buildNeighborLists(float thresh, bool loops[3]) { //grid size must be >= 2*thresh
	float threshSqr = thresh*thresh;
	for (Atom *a : atoms) {
		a->neighbors = vector<Neighbor>(a->neighbors.size()); //try to keep if from having to move resize the vectors all the time
		a->posAtNeighborListing = a->pos;
	}
	reset();
	/*
	*using looping values, make list of squares that corresponds to the neighbors for each square.
	 Then for each atom, add atoms by following each linked list and appening those within rcut
	*/ 
	vector<vector<OffsetObj<Atom **> > > neighborSquaress;
	neighborSquaress.reserve(raw.size());
	cout << ns[0] << " " << ns[1] << " " << ns[2] << endl;
	for (int i=0; i<ns[0]; i++) {
		for (int j=0; j<ns[1]; j++) {
			for (int k=0; k<ns[2]; k++) {
				int coord[3];
				coord[0] = i; coord[1] = j; coord[2] = k;
				neighborSquaress.push_back(getNeighbors(coord, loops, bounds.trace));
			}
		}
	}
	for (Atom *a : atoms) {
		int idx = idxFromPos(a->pos);		
		Atom **neighborSquare = &(*this)(a->pos);
		OffsetObj<Atom **> selfSquare = OffsetObj<Atom **>(neighborSquare, Vector(0, 0, 0));
		appendNeighborList(a, selfSquare, threshSqr);
		a->next = *selfSquare.obj;
		*selfSquare.obj = a;
		vector<OffsetObj<Atom **> > &neighborSquares = neighborSquaress[idx];
		for (OffsetObj<Atom **> &neighborSquare : neighborSquares) {
			appendNeighborList(a, neighborSquare, threshSqr);	
		}
	}
}


/*

void AtomGrid::sliceBounds(double *testlo, double *testhi, double *boxlo, double *boxhi, double *newBndlo, double *newBndhi) {
	if (*testlo < *boxlo) {
		double dx = *boxlo - *testlo;
		*newBndlo = *boxhi - dx;
		*newBndhi = *boxhi;
		*testlo = *boxlo;
	} else if (*testhi > *boxhi) {
		double dx = *testhi - *boxhi;
		*newBndlo = *boxlo;
		*newBndhi = *boxlo + dx;
		*testhi = *boxhi;
	}
}


vector<Atom *> AtomGrid::atomsInNonLoopingBounds(Bounds b) {
	vector<Atom *> inBounds;
	int idxs[6];

	for (int i=0; i<3; i++) {
		idxs[2*i] = (*b[2*i] - *oPtrs[i]) / *dPtrs[i];
		double upper = (*b[2*i+1] - *oPtrs[i]) / *dPtrs[i];
		if ((int) upper == upper) {
			idxs[2*i+1] = upper-1; //making it so if just on boundary, doesn't select box that is one higher than it needs to be.  Leads to segaults and stuff if on endge of box.
		} else {
			idxs[2*i+1] = upper;
		}
	}
	vector<atomlist *> blocks;
	for (int x=idxs[0]; x<=idxs[1]; x++) {
		for (int y=idxs[2]; y<=idxs[3]; y++) {
			for (int z=idxs[4]; z<=idxs[5]; z++) {
				blocks.push_back(&(*this)(x, y, z));
			}
		}
	}
	for (atomlist *alist : blocks) {
		for (Atom *a : *alist) {
			if (b.atomInBounds(a)) {
				inBounds.push_back(a);
			}
		}
	}
	return inBounds;
}

vector<Atom *> AtomGrid::selectFromBounds(Bounds b) { //assuming span of dims is less than bounds of box
	vector<Atom *> inBounds;
	vector<Bounds> toCheck;
	toCheck.push_back(b);
	for (int valIdx=0; valIdx<6; valIdx+=2) { //dealing with bounds wrapping around
		for (int i=toCheck.size()-1; i>=0; i--) {
			Bounds &b = toCheck[i];
			double *lo = b[valIdx];
			double *hi = b[valIdx+1];
			double *boxlo = bounds[valIdx];
			double *boxhi = bounds[valIdx+1];
			Bounds sliceProd = b;
			sliceBounds(lo, hi, boxlo, boxhi, sliceProd[valIdx], sliceProd[valIdx+1]);
			if (!(sliceProd == b)) {
				toCheck.push_back(sliceProd);
			}
		}
	}
	for (Bounds &b : toCheck) {
		vector<Atom *> res = atomsInNonLoopingBounds(b);
		inBounds.insert(inBounds.end(), res.begin(), res.end());
	}
	return inBounds;
}
*/
