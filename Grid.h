#ifndef GRID_H
#define	GRID_H
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include "Vector.h"
using namespace std;
template <class T>
class Grid {
	public:
		vector<T> saved;
		vector<T> raw;
		int ns[3]; //make const
		const Vector ds;
		const Vector os;
		
		Grid(){};
			
		Grid(int nx_, int ny_, int nz_, Vector ds_, Vector os_) : ds(ds_), os(os_) {
			ns[0] = nx_;
			ns[1] = ny_;
			ns[2] = nz_;
			assert(ns[0] > 0 and ns[1] > 0 and ns[2] > 0);
			int n = ns[0]*ns[1]*ns[2];
			raw.reserve(n);
			for (int i=0; i<n; i++) {
				T t();
				raw.push_back(t);
			}
		};
/*
		int loopDim(const int x, const int nd, int *loop) { //only works if one of fewer grids offset.  Could do some flooring, but meh.  Not a relevant case.
			if (x < 0) {
				*loop = -1;
				return nd + x;
			} else if (x >= nd) {
				*loop = 1;
				return x - nd;
			} 
			*loop = 0;
			return x;

		};*/
		T &operator()(const int x, const int y, const int z) {
		//	int idx = x*ny*nz + y*nz + z;
		//	if (idx >= raw.size()) {
		//		cout << "GETTING OUT OF BOUNDS GRID SQUARE" << endl;cout.flush();
		//	}
			return raw[x*ns[1]*ns[2] + y*ns[2] + z];
		};
		T &operator()(Vector &v) {
			Vector coord = (v - os) / ds;
			/*const int x = (v.x - ox) / dx;
			const int y = (v.y - oy) / dy;
			const int z = (v.z - oz) / dz;*/
			return raw[coord[0]*ns[1]*ns[2] + coord[1]*ns[1] + coord[2]];
		};
		/*
		T &operator()(int x, int y, int z, int *loopX, int *loopY, int *loopZ) {
			x = loopDim(x, nx, loopX);
			y = loopDim(y, ny, loopY);
			z = loopDim(z, nz, loopZ);
			return (*this)(x, y, z);
		};*/
		Vector pos(const int x, const int y, const int z) {
			return os + Vector(ds[0]*x, ds[1]*y, ds[2]*z);
		};
		void setRaw(vector<T> vals) {
			raw = vals;
		};
		void setSaved(vector<T> vals) {
			saved = vals;
		}
		void reset() {
			raw = saved;
		}
	
};
#endif
