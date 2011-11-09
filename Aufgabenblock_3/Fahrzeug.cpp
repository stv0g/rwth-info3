#include <iostream>
#include <iomanip>
#include <cmath>

#include "Fahrzeug.h"
#include "Weg.h"
#include "FzgFahren.h"
#include "FzgParken.h"
#include "SimuClient.h"

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
Fahrzeug::Fahrzeug(Fahrzeug &fz) : AktivesVO(fz) {
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
			<< setw(10) << dGeschwindigkeit()
			<< setw(9) << p_dGesamtStrecke
			<< setw(11) << p_dAbschnittStrecke;

	return stream;
}

istream& Fahrzeug::istreamEingabe(istream &stream) {
	AktivesVO::istreamEingabe(stream) >> p_dMaxGeschwindigkeit;

	return stream;
}

void Fahrzeug::vAbfertigung() {
	/* nicht doppelt abfertigen (Gleitkommavgl.) */
	if (p_dZeit >= dGlobaleZeit - 1e-5) return;

	double dDelta = dGlobaleZeit - p_dZeit;;
	double dStrecke = p_pVerhalten->dStrecke(this, dDelta);

	p_dGesamtZeit += dDelta;
	p_dGesamtStrecke += dStrecke;
	p_dAbschnittStrecke += dStrecke;

	p_dZeit = dGlobaleZeit; /* wird nur aktualisiert, falls keine Ausnahme aufgetreten ist */
}

double Fahrzeug::dGeschwindigkeit() const {
	if (p_pVerhalten != NULL) {
		Weg *pWeg = p_pVerhalten->getWeg();

		if (pWeg != NULL) {
			double dBeschraenkung = pWeg->getMaxGeschwindigkeit();

			if (p_dMaxGeschwindigkeit > dBeschraenkung) {
				return dBeschraenkung;
			}
		}
	}

	return p_dMaxGeschwindigkeit;

}

double Fahrzeug::dTanken(double dMenge) {
	return 0;
}

void Fahrzeug::vNeueStrecke(Weg *pWeg, double dStartZeit) {
	if (p_pVerhalten != NULL) { /* alter Weg vorhanden? */
		delete p_pVerhalten; /* Speicherleck vermeiden! */
	}
	
    if (dStartZeit > 0) {
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

void Fahrzeug::vZeichnen() const {
	Weg *pWeg = p_pVerhalten->getWeg();
	bZeichneFahrrad(getName(), pWeg->getName(), getAbschnittStrecke() / pWeg->getLaenge(), dGeschwindigkeit());
}
