
#ifndef ATOM_PARAMS_H
#define ATOM_PARAMS_H
#include <vector>
using namespace std;


class AtomParams {
	public:
		AtomParams(float sig_, float eps_, float m_) : sig(sig_), eps(eps_), m(m_) {};
		float sig;
		float eps;
		float m;
		int type;
};
//want a little class to make sure params get assigned types nicely
class AtomParamWrapper {
	public:
		vector<AtomParams> params;
		AtomParamWrapper(float rCut_) : rCut(rCut_) {}
		const float rCut;
		AtomParamWrapper &push_back(AtomParams params_) {
			params_.type = params.size();
			params.push_back(params_);
			return *this;
		}
		AtomParams operator [] (int n) {
			return params[n];
		}
};


#endif

