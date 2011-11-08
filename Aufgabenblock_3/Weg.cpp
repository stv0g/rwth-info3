#include <iostream>
#include <iomanip>
#include <algorithm>
#include <float.h>

#include "SimuClient.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "FahrAusnahme.h"

extern double dGlobaleZeit;

/* Standardkonstruktor */
Weg::Weg() : AktivesVO()
{ }

Weg::Weg(string sName, double dLaenge, Begrenzung eLimit, bool bUeberholverbot) :
	AktivesVO(sName),
	p_dLaenge(dLaenge),
	p_dUeberholverbot(bUeberholverbot),
	p_eLimit(eLimit),
	p_pZielKreuzung(NULL),
	p_pRueckweg(NULL)
{ }

/* Destruktor */
Weg::~Weg()
{ }

/* fertige alle Fahrzeuge auf Weg ab */
void Weg::vAbfertigung() {
	LazyListe<Fahrzeug *>::iterator it;
	p_dSchranke = p_dLaenge;

    p_lFahrzeuge.vAktualisieren();
	for (it = p_lFahrzeuge.begin(); it != p_lFahrzeuge.end(); it++) {
        try {
			(*it)->vAbfertigung();
		} catch (FahrAusnahme &ausnahme) {
			ausnahme.vBearbeiten();
			//(*it)->vAbfertigung();
		}
	}

    p_lFahrzeuge.vAktualisieren();
	p_dZeit = dGlobaleZeit;
}

void Weg::vAnnahme(Fahrzeug *pFz, double dStartZeit) {
	pFz->vNeueStrecke(this, dStartZeit);
	
    if (dStartZeit > 0) { /* parkende Fahrzeuge werden vorne eingef�gt */
        p_lFahrzeuge.push_front(pFz);
    }
    else { /* fahrende hinten */
        p_lFahrzeuge.push_back(pFz);
    }
}

void Weg::vAbgabe(Fahrzeug *pFz) {
	LazyListe<Fahrzeug *>::iterator result;

	result = find(p_lFahrzeuge.begin(), p_lFahrzeuge.end(), pFz);

	if (result != p_lFahrzeuge.end()) { /* gefunden */
		p_lFahrzeuge.erase(result);
	}
}

void Weg::vZeichnen(size_t iAnzahlKoordinaten, Koordinaten iKoordinaten[]) const {
	bZeichneStrasse(getName(), p_pRueckweg->getName(), getLaenge(), iAnzahlKoordinaten, (int *) iKoordinaten);
}

void Weg::vZeichnen() const {
	LazyListe<Fahrzeug *>::const_iterator it;
	for (it = p_lFahrzeuge.begin(); it != p_lFahrzeuge.end(); it++) {
		(*it)->vZeichnen();
	}
}

double Weg::getLaenge() const {
	return p_dLaenge;
}

double Weg::getSchranke() const {
	return p_dSchranke;
}

void Weg::setSchranke(double dSchranke) {
	p_dSchranke = dSchranke;
}

void Weg::setRueckweg(Weg * pRueckweg) {
	p_pRueckweg = pRueckweg;
}

Weg * Weg::getRueckweg() {
	return p_pRueckweg;
}

void Weg::setZielKreuzung(Kreuzung * pZielKreuzung) {
	p_pZielKreuzung = pZielKreuzung;
}

Kreuzung * Weg::getZielKreuzung() {
	return p_pZielKreuzung;
}

double Weg::getMaxGeschwindigkeit() const {
	switch (p_eLimit) {
		case Weg::Innerorts:		return 50;
		case Weg::Landstrasse:	return 100;
		case Weg::Autobahn:		return DBL_MAX; /* unbegrenzt */
		default:			return 0;
	}
}


ostream& Weg::ostreamAusgabe(ostream &stream) const {
	double dMaxGeschwindigkeit = getMaxGeschwindigkeit();

	AktivesVO::ostreamAusgabe(stream) << setprecision(2)
			<< resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(8);

	if (dMaxGeschwindigkeit == DBL_MAX) {
		stream << "(inf)";
	}
	else {
		stream << dMaxGeschwindigkeit;
	}

	stream << setw(16) << p_dLaenge << " ( ";

	LazyListe<Fahrzeug *>::const_iterator it;
	for (it = p_lFahrzeuge.begin(); it != p_lFahrzeuge.end(); it++) {
		stream << (*it)->getName() << " ";
	}

	stream << ")";

	for (it = p_lFahrzeuge.begin(); it != p_lFahrzeuge.end(); it++) {
		stream << endl << **it;
	}

	return stream;
}
