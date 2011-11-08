#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "FahrAusnahme.h"

class Streckenende: public FahrAusnahme {
public:
	Streckenende(Fahrzeug *pFahrzeug, Weg *pWeg);
	virtual ~Streckenende();

	void vBearbeiten();
};

#endif /* STRECKENENDE_H_ */
