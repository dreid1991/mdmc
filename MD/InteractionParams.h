#ifndef INTERACTION_PARAMS_H
#define INTERACTION_PARAMS_H
#include <math.h>
#include "AtomParams.h"
//class for getting atom interaction parameters for force computation.  
//Implemented completely in header so that can be inlined
using namespace std;
class InteractionParams {
	public:
		InteractionParams(){};
		InteractionParams(AtomParamWrapper &wrapper) {
			populate(wrapper);
		};
		vector<float> param1; //mapping 2d array into 1d list
		vector<float> param2; //param1 for r^12 term, param2 for r^6 term
		int numTypes;
		//not many types, so n^2 size list isn't so bad, and makes it so getting params is faster than list that's not redundant 
		void populate(AtomParamWrapper &wrapper) {
			vector<AtomParams> params = wrapper.params;
			for (int i=0; i<numTypes; i++) {
				for (int j=0; j<numTypes; j++) {
					AtomParams &a = params[i];
					AtomParams &b = params[j];
					double sig = (a.sig + b.sig) / 2;
					double eps = sqrt(a.eps * b.eps);
					double p1 = eps * pow(sig, 12);
					double p2 = 2 * eps * pow(sig, 6);
					param1.push_back(p1);
					param2.push_back(p2);
				}
			}
		}
		float getParam1(int i, int j) { //order doesn't matter, array is symmetric around diagonal
			return param1[i * numTypes + j];
		}
		float getParam2(int i, int j) {
			return param2[i * numTypes + j];
		}
};

#endif
