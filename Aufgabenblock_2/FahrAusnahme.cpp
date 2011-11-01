#include "FahrAusnahme.h"

FahrAusnahme::FahrAusnahme(Fahrzeug *pFahrzeug, Weg *pWeg) :
	p_pFahrzeug(pFahrzeug),
	p_pWeg(pWeg)
{ }

FahrAusnahme::~FahrAusnahme()
{ }

Weg * FahrAusnahme::getWeg() {
	return p_pWeg;
}

Fahrzeug * FahrAusnahme::getFahrzeug() {
	return p_pFahrzeug;
}

