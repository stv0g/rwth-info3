/*
 * Fahrzeug.cpp
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Fahrzeug.h"

extern double dGlobaleZeit;

int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug() {
	vInitialisierung();
	//cout << this->p_sName << ":" << this->p_iID << " wurde initialisiert" << endl;
}

Fahrzeug::Fahrzeug(string sName) {
	vInitialisierung();
	p_sName = sName;

	//cout << this->p_sName << ":" << this->p_iID << " wurde initialisiert" << endl;
}

Fahrzeug::~Fahrzeug() {
	//cout << this->p_sName << ":" << this->p_iID << " wurde gelöscht" << endl;
}

void Fahrzeug::vInitialisierung() {
	p_iID = ++p_iMaxID;

	p_sName = " ";
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dGesamtZeit = 0;
	p_dZeit = 0;
}

void Fahrzeug::vAusgabe() {
	cout << setprecision(2) << setiosflags(ios::fixed)
			<< resetiosflags(ios::right) << setiosflags(ios::left)
			<< setw(4) << this->p_iID
			<< setw(7) << this->p_sName << ":  "
			<< resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(7) << p_dMaxGeschwindigkeit
			<< setw(12) << p_dGesamtStrecke
			<< endl;
}

void Fahrzeug::vAbfertigung() {
	if (fabs(p_dZeit - dGlobaleZeit) < 1e-10) return;

	double dDelta = dGlobaleZeit - p_dZeit;

	p_dGesamtZeit += dDelta;
	p_dGesamtStrecke += dGeschwindigkeit() * dDelta;
	p_dZeit = dGlobaleZeit;
}
