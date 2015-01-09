
#ifndef ATOM_PARAMS_H
#define ATOM_PARAMS_H


class AtomParams {
	public:
		AtomParams(float sig_, float eps_, float m_) : sig(sig_), eps(eps_), m(m_) {};
		float sig;
		float eps;
		float m;
		int id;
};
//want a little class to make sure params get assigned ids nicely
class AtomParamWrapper {
	public:
		vector<AtomParams> params;
		AtomParamWrapper() {}
		AtomParamWrapper &push_back(AtomParams params_) {
			params_.id = params.size();
			params.push_back(params_);
			return *this;
		}
		AtomParams operator [] (int n) {
			return params[n];
		}
};


#endif

