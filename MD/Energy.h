#ifndef ENERGY_H
#define ENERGY_H
class Energy {
	public:
		Energy() : total(0), potential(0), kinetic(0) {};
		float total;
		float potential;
		float kinetic;
};
#endif
