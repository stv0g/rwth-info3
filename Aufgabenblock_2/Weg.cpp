#include <iostream>
#include <iomanip>

#include "Weg.h"
#include "Fahrzeug.h"

/* Standardkonstruktor */
Weg::Weg() : AktivesVO()
{ }

Weg::Weg(string sName, double dLaenge, Begrenzung eLimit) : AktivesVO(sName)
{
	p_dLaenge = dLaenge;
	p_eLimit = eLimit;
}

/* Destruktor */
Weg::~Weg()
{ }

/* fertige alle Fahrzeuge auf Weg ab */
void Weg::vAbfertigung() {
	list<Fahrzeug *>::const_iterator iterator;
	for (iterator = p_pFahrzeuge.begin(); iterator != p_pFahrzeuge.end(); ++iterator) {
		(*iterator)->vAbfertigung();
	}
}

void Weg::vAnnahme(Fahrzeug *pFz) {
	pFz->vNeueStrecke(this);
	p_pFahrzeuge.push_back(pFz);
}

double Weg::getLaenge() const {
	return p_dLaenge;
}

ostream& Weg::ostreamAusgabe(ostream &stream) const {
	AktivesVO::ostreamAusgabe(stream) << resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(24) << p_dLaenge << " ( ";

	list<Fahrzeug *>::const_iterator iterator;
	for (iterator = p_pFahrzeuge.begin(); iterator != p_pFahrzeuge.end(); ++iterator) {
		stream << (*iterator)->getName() << " ";
	}

	stream << ")";

	return stream;
}
