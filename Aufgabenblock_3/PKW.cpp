#include <iostream>
#include <iomanip>

#include "PKW.h"
#include "SimuClient.h"

using namespace std;

extern double dGlobaleZeit;

/* Standardkonstruktor */
PKW::PKW() :
	Fahrzeug(),
	p_dVerbrauch(0),
	p_dTankinhalt(0),
	p_dTankvolumen(0)
{ }

PKW::PKW(string sName, double dMaxGeschwindigkeit) :
	Fahrzeug(sName, dMaxGeschwindigkeit),
	p_dVerbrauch(0),
	p_dTankinhalt(0),
	p_dTankvolumen(0)
{ }

PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
	Fahrzeug(sName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankinhalt(dTankvolumen / 2),
	p_dTankvolumen(dTankvolumen)
{ }

/* Destruktor */
PKW::~PKW()
{ }

double PKW::dTanken(double dMenge) {
	double dAlterInhalt = p_dTankinhalt;

	if (dMenge == 0) {
		p_dTankinhalt = p_dTankvolumen;
	} else {
		p_dTankinhalt += dMenge;
		if (p_dTankinhalt > p_dTankvolumen) {
			p_dTankinhalt = p_dTankvolumen; /* Verhindere Überfüllung */
		}
	}

	return p_dTankinhalt - dAlterInhalt;
}

void PKW::vZeichnen() const {
	Weg *pWeg = p_pVerhalten->getWeg();
	bZeichnePKW(getName(), pWeg->getName(), getAbschnittStrecke() / pWeg->getLaenge(), dGeschwindigkeit(), getTankinhalt());
}

void PKW::vAbfertigung() {
	if (p_dTankinhalt > 0) { /* prüfen, ob etwas im Tank ist */
		double dDelta = dGlobaleZeit - p_dZeit;
		double dStrecke = p_pVerhalten->dStrecke(this, dDelta);

		p_dTankinhalt -= dStrecke * p_dVerbrauch / 100;

		if (p_dTankinhalt < 0) { /* falls Tankinhalt negativ ist */
			p_dTankinhalt = 0;
		}

		Fahrzeug::vAbfertigung();
	}
	else {
		p_dZeit = dGlobaleZeit;
	}
}

ostream& PKW::ostreamAusgabe(ostream &stream) const {
	Fahrzeug::ostreamAusgabe(stream) << setprecision(2) << setiosflags(ios::fixed)
		<< resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(11) << dVerbrauch()
		<< setw(12) << p_dTankinhalt;

	return stream;
}

istream& PKW::istreamEingabe(istream &stream) {
	Fahrzeug::istreamEingabe(stream) >> p_dVerbrauch >> p_dTankvolumen;
	p_dTankinhalt = p_dTankvolumen/2;

	return stream;
}

double PKW::dVerbrauch() const {
	return p_dGesamtStrecke * p_dVerbrauch / 100;
}

double PKW::getTankinhalt() const {
	return p_dTankinhalt;
}
