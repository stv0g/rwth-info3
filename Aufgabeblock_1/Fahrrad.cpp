/*
 * Fahrrad.cpp
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#include "Fahrrad.h"

Fahrrad::Fahrrad() {
	// TODO Auto-generated constructor stub
}

Fahrrad::~Fahrrad() {
	// TODO Auto-generated destructor stub
}

double Fahrrad::dGeschwindigkeit() {
	double dFahrradGeschwindigkeit = p_dMaxGeschwindigkeit;
	int iReduzierung = (int) p_dGesamtStrecke / 20;

	for (int i = 0; i < iReduzierung; i++) {
		dFahrradGeschwindigkeit *= 0.9;
	}

	if (dFahrradGeschwindigkeit < 12) {
		dFahrradGeschwindigkeit = 12;
	}

	return dFahrradGeschwindigkeit;
}

static Fahrrad * Fahrrad::erzeuge(string sName, double dMaxGeschwindigkeit) {
	Fahrrad *rad = new Fahrrad(sName);

	rad->p_dMaxGeschwindigkeit = dMaxGeschwindigkeit;

	return rad;
}

