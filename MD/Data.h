#ifndef DATA_H
#define DATA_H

#include "Energy.h"
#include "Virial.h"
#include "DataThermo.h"
class Data {
	public:
		Data(){};
		DataThermo thermo;
		Energy eng;
		Virial vir;
};
#endif
