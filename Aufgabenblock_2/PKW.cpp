#include <iostream>
#include <iomanip>

#include "PKW.h"

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

void PKW::vAbfertigung() {
	if (p_dTankinhalt > 0) { /* prüfen, ob etwas im Tank ist */
		p_dTankinhalt -= (dGlobaleZeit - p_dZeit) * p_dMaxGeschwindigkeit
				* p_dVerbrauch / 100;

		if (p_dTankinhalt < 0) { /* falls Tankinhalt negativ ist */
			p_dTankinhalt = 0;
		}

		Fahrzeug::vAbfertigung();
	}
}

ostream& PKW::ostreamAusgabe(ostream &stream) const {
	Fahrzeug::ostreamAusgabe(stream) << setprecision(2) << setiosflags(ios::fixed)
		<< resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(12) << dVerbrauch()
		<< setw(13) << p_dTankinhalt;

	return stream;
}

double PKW::dVerbrauch() const {
	return p_dGesamtStrecke * p_dVerbrauch / 100;
}
