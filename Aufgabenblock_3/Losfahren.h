#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "FahrAusnahme.h"

class Losfahren: public FahrAusnahme {
public:
	Losfahren(Fahrzeug *pFahrzeug, Weg *pWeg);
	virtual ~Losfahren();

	void vBearbeiten();
};

#endif /* LOSFAHREN_H_ */
