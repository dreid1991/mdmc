#ifndef DATA_H
#define DATA_H

#include "Energy.h"
#include "DataThermo.h"
class Data {
	public:
		Data() : virialTotal(0) {};
		DataThermo thermo;
		Energy eng;
		float virialTotal;
};
#endif
