#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Weg.h"
#include "Fahrzeug.h"
#include "FahrAusnahme.h"

extern double dGlobaleZeit;

/* Standardkonstruktor */
Weg::Weg() : AktivesVO()
{ }

Weg::Weg(string sName, double dLaenge, Begrenzung eLimit) : AktivesVO(sName) {
	p_dLaenge = dLaenge;
	p_eLimit = eLimit;
}

/* Destruktor */
Weg::~Weg()
{ }

/* fertige alle Fahrzeuge auf Weg ab */
void Weg::vAbfertigung() {
	list<Fahrzeug *>::iterator it;

    p_pFahrzeuge.vAktualisieren();
	for (it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
        try {
			(*it)->vAbfertigung();
		} catch (FahrAusnahme &ausnahme) {
			ausnahme.vBearbeiten();
		}
	}

    p_pFahrzeuge.vAktualisieren();
	p_dZeit = dGlobaleZeit;
}

void Weg::vAnnahme(Fahrzeug *pFz, double dStartZeit) {
	pFz->vNeueStrecke(this, dStartZeit);
	
    if (dStartZeit > 0) { /* parkende Fahrzeuge werden vorne eingefügt */
        p_pFahrzeuge.push_front(pFz);
    }
    else { /* fahrende hinten */
        p_pFahrzeuge.push_back(pFz);
    }
}

void Weg::vAbgabe(Fahrzeug *pFz) {
	list<Fahrzeug *>::iterator result;

	result = find(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), pFz);

	if (result != p_pFahrzeuge.end()) { /* gefunden */
		p_pFahrzeuge.erase(result);
	}
}

double Weg::getLaenge() const {
	return p_dLaenge;
}

Weg::Begrenzung Weg::getLimit() const {
	return p_eLimit;
}

ostream& Weg::ostreamAusgabe(ostream &stream) const {
	AktivesVO::ostreamAusgabe(stream) << setprecision(2)
			<< resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(24) << p_dLaenge << " ( ";

	list<Fahrzeug *>::const_iterator it;
	for (it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		stream << (*it)->getName() << " ";
	}

	stream << ")";

	return stream;
}
