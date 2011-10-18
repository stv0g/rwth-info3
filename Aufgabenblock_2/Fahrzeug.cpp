#include <iostream>
#include <iomanip>
#include <cmath>

#include "Fahrzeug.h"
#include "Weg.h"
#include "AktivesVO.h"

extern double dGlobaleZeit;

/* Standardkonstruktor */
Fahrzeug::Fahrzeug() : AktivesVO()
{
	vInitialisierung();
}

Fahrzeug::Fahrzeug(string sName) : AktivesVO(sName)
{
	vInitialisierung();
}

Fahrzeug::Fahrzeug(string sName, double dMaxGeschwindkeit) : AktivesVO(sName)
{
	vInitialisierung();
	p_dMaxGeschwindigkeit = dMaxGeschwindkeit;
}

/* Kopierkonstruktor */
Fahrzeug::Fahrzeug(Fahrzeug &fz) : AktivesVO(fz)
{
	vInitialisierung();
	p_dMaxGeschwindigkeit = fz.p_dMaxGeschwindigkeit;
}

/* Destruktor */
Fahrzeug::~Fahrzeug()
{ }

void Fahrzeug::vInitialisierung() {
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dAbschnittStrecke = 0;
	p_dGesamtZeit = 0;
	p_pVerhalten = NULL;
}

void Fahrzeug::vAusgabeHeader() {
	cout << "ID  Name   :  MaxKmh   GesamtStrecke   Verbrauch   Tankinhalt" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

ostream& Fahrzeug::ostreamAusgabe(ostream &stream) const {
	AktivesVO::ostreamAusgabe(stream) << resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(8) << dGeschwindigkeit()
		<< setw(7) << p_dGesamtStrecke
		<< " (" << setw(6) << p_dAbschnittStrecke << ")";

	return stream;
}

void Fahrzeug::vAbfertigung() {
	/* nicht doppelt abfertigen (Gleitkommavgl.) */
	if (fabs(p_dZeit - dGlobaleZeit) < 1e-10) return;

	double dDelta = dGlobaleZeit - p_dZeit;
	double dStrecke = p_pVerhalten->dStrecke(this, dDelta);

	p_dGesamtZeit += dDelta;
	p_dGesamtStrecke += dStrecke;
	p_dAbschnittStrecke += dStrecke;
	p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dTanken(double dMenge) {
	return 0;
}

void Fahrzeug::vNeueStrecke(Weg *pWeg) {
	if (p_pVerhalten != NULL) { /* alter Weg vorhanden? */
		delete p_pVerhalten; /* Speicherleck vermeiden! */
	}
	else {
		p_pVerhalten = new FzgVerhalten(pWeg);
	}
}

double Fahrzeug::getAbschnittStrecke() const {
	return p_dAbschnittStrecke;
}

bool Fahrzeug::operator<(Fahrzeug &fz) const {
	return (this->p_dGesamtStrecke < fz.p_dGesamtStrecke);
}
