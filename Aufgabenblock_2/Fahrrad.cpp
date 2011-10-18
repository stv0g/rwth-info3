#include <math.h>

#include "Fahrrad.h"

/* Standardkonstruktor */
Fahrrad::Fahrrad() : Fahrzeug()
{ }

Fahrrad::Fahrrad(string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit)
{ }

/* Destruktor */
Fahrrad::~Fahrrad()
{ }

double Fahrrad::dGeschwindigkeit() const {
	double dGeschwindigkeit;
	int iReduzierung = p_dGesamtStrecke / 20;

	dGeschwindigkeit = p_dMaxGeschwindigkeit * powl(0.9, iReduzierung);

	if (dGeschwindigkeit < 12) {
		dGeschwindigkeit = 12;
	}

	return dGeschwindigkeit;
}

