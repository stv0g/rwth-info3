#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

using namespace std;

class Fahrrad: public Fahrzeug {
public:
	Fahrrad();
	Fahrrad(string sName, double dMaxGeschwindigkeit);
	virtual ~Fahrrad();

	double dGeschwindigkeit() const;
};

#endif /* FAHRRAD_H_ */
