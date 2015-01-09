#ifndef INTERACTION_PARAMS_H
#define INTERACTION_PARAMS_H
#include <math.h>
#include "AtomParams.h"
//class for getting atom interaction parameters for force computation.  
//Implemented completely in header so that can be inlined
using namespace std;
class InteractionParams {
	public:
		InteractionParams(AtomParamWrapper &wrapper) {
			populate(wrapper);
		};
		vector<float> sigmas; //mapping 2d array into 1d list
		vector<float> epsilons;
		int numTypes;
		//not many types, so n^2 size list isn't so bad, and makes it so getting params is faster than list that's not redundant 
		void populate(AtomParamWrapper &wrapper) {
			vector<AtomParams> params = wrapper.params;
			for (int i=0; i<numTypes; i++) {
				for (int j=0; j<numTypes; j++) {
					AtomParams &a = params[i];
					AtomParams &b = params[j];
					sigmas.push_back((a.sig * b.sig) / 2);
					epsilons.push_back(sqrt(a.eps * b.eps));
				}
			}
		}
		float getEpsilon(int i, int j) { //order doesn't matter, array is symmetric around diagonal
			return epsilons[i * numTypes + j];
		}
		float getSigma(int i, int j) {
			return sigmas[i * numTypes + j];
		}
};

#endif
