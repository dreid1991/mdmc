#ifndef DATA_H
#define DATA_H

#include "DataBlockAvgs.h"
class Data {
	public:
		Data() : virialTotal(0) {};
		BlockAvgs avgs;
		double potentialEng;
		double virialTotal;
};
#endif
