/*
 * PKW.cpp
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#include <iostream>
#include <iomanip>

#include "PKW.h"

using namespace std;

extern double dGlobaleZeit;

PKW::PKW(string sName, double dVerbrauch, double dTankvolumen = 55) :
	Fahrzeug(sName),
	p_dVerbrauch(dVerbrauch),
	p_dTankvolumen(dTankvolumen),
	p_dTankinhalt(dTankvolumen/2) { }

PKW::PKW(double dVerbrauch, double dTankvolumen = 55) :
	Fahrzeug(),
	p_dVerbrauch(dVerbrauch),
	p_dTankvolumen(dTankvolumen),
	p_dTankinhalt(dTankvolumen/2) { }

PKW::~PKW() {
	// TODO Auto-generated destructor stub
}

double PKW::dTanken(double dMenge = 0) {
	double dAlterInhalt = p_dTankinhalt;

	if (dMenge == 0) {
		p_dTankinhalt = p_dTankvolumen;
	}
	else {
		p_dTankinhalt += dMenge;
		if (p_dTankinhalt > p_dTankvolumen) {
			p_dTankinhalt = p_dTankvolumen; /* Verhindere Überfüllung */
		}
	}

	return p_dTankinhalt - dAlterInhalt;
}

void PKW::vAbfertigung() {
	if (p_dTankinhalt > 0) { /* prüfen, ob etwas im Tank ist */
		p_dTankinhalt -= (dGlobaleZeit - p_dZeit) * p_dMaxGeschwindigkeit * p_dVerbrauch / 100;
			if (p_dTankinhalt < 0) { /* falls Tankinhalt negativ ist */
					p_dTankinhalt = 0;
			}
			Fahrzeug::vAbfertigung();
	}
	else {
		p_dTankinhalt = 0;
	}
}

void PKW::vAusgabe() {
	Fahrzeug::vAusgabe();

	cout << setprecision(2) << setiosflags(ios::fixed)
		<< resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(7) << dVerbrauch()
		<< setw(7) << p_dTankinhalt << endl;
}

double PKW::dVerbrauch() {
	return p_dGesamtStrecke * p_dVerbrauch / 100;
}

static PKW * PKW::erzeuge(string sName, double dMaxGeschwindigkeit) {
	Fahrrad *rad = new Fahrrad(sName);

	rad->p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;

	return rad;
}
