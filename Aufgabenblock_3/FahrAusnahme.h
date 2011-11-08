#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include "Fahrzeug.h"
#include "Weg.h"

class FahrAusnahme {
public:
	FahrAusnahme(Fahrzeug *pFahrzeug, Weg *pWeg);
	virtual ~FahrAusnahme();

	Weg * getWeg();
	Fahrzeug * getFahrzeug();

	virtual void vBearbeiten() = 0;

protected:
	Fahrzeug *p_pFahrzeug;
	Weg *p_pWeg;
};

#endif /* FAHRAUSNAHME_H_ */
