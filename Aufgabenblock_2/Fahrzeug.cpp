#include <iostream>
#include <iomanip>
#include <cmath>

#include "Fahrzeug.h"
#include "Weg.h"
#include "FzgFahren.h"
#include "FzgParken.h"
#include "AktivesVO.h"

extern double dGlobaleZeit;

/* Standardkonstruktor */
Fahrzeug::Fahrzeug() :
	AktivesVO() {
	vInitialisierung();
}

Fahrzeug::Fahrzeug(string sName) :
	AktivesVO(sName) {
	vInitialisierung();
}

Fahrzeug::Fahrzeug(string sName, double dMaxGeschwindkeit) :
	AktivesVO(sName) {
	vInitialisierung();
	p_dMaxGeschwindigkeit = dMaxGeschwindkeit;
}

/* Kopierkonstruktor */
Fahrzeug::Fahrzeug(Fahrzeug &fz) :
	AktivesVO(fz) {
	vInitialisierung();
	p_dMaxGeschwindigkeit = fz.p_dMaxGeschwindigkeit;
}

/* Destruktor */
Fahrzeug::~Fahrzeug() {
}

void Fahrzeug::vInitialisierung() {
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dAbschnittStrecke = 0;
	p_dGesamtZeit = 0;
	p_pVerhalten = NULL;
}

ostream& Fahrzeug::ostreamAusgabe(ostream &stream) const {
	AktivesVO::ostreamAusgabe(stream) << setprecision(2)
			<< resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(8) << dGeschwindigkeit()
			<< setw(7) << p_dGesamtStrecke << " ("
			<< setw(6) << p_dAbschnittStrecke << ")";

	return stream;
}

void Fahrzeug::vAbfertigung() {
	/* nicht doppelt abfertigen (Gleitkommavgl.) */
	if (fabs(p_dZeit - dGlobaleZeit) < 1e-10)
		return;

	double dDelta = dGlobaleZeit - p_dZeit;
	double dStrecke = p_pVerhalten->dStrecke(this, dDelta);

	p_dGesamtZeit += dDelta;
	p_dGesamtStrecke += dStrecke;
	p_dAbschnittStrecke += dStrecke;
	p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dGeschwindigkeit() const {
	double dBegrenzung = p_pVerhalten->getMaxgeschwindigkeit();

	if (p_dMaxGeschwindigkeit > dBegrenzung) {
		return dBegrenzung;
	}
	else {
		return p_dMaxGeschwindigkeit;
	}
}

double Fahrzeug::dTanken(double dMenge) {
	return 0;
}

void Fahrzeug::vNeueStrecke(Weg *pWeg, double dStartZeit) {
	if (p_pVerhalten != NULL) { /* alter Weg vorhanden? */
		delete p_pVerhalten; /* Speicherleck vermeiden! */
	}
	else if (dStartZeit > 0) {
		p_pVerhalten = new FzgParken(pWeg, dStartZeit);
	}
	else {
		p_pVerhalten = new FzgFahren(pWeg);
	}

	p_dAbschnittStrecke = 0;
}

double Fahrzeug::getAbschnittStrecke() const {
	return p_dAbschnittStrecke;
}

bool Fahrzeug::operator<(Fahrzeug &fz) const {
	return (this->p_dGesamtStrecke < fz.p_dGesamtStrecke);
}
