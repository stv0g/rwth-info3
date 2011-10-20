#include <iostream>
#include <iomanip>
#include <cmath>

#include "Fahrzeug.h"

extern double dGlobaleZeit;

int Fahrzeug::p_iMaxID = 0;

/* Standardkonstruktor */
Fahrzeug::Fahrzeug() {
	vInitialisierung();
	//cout << this->p_sName << ":" << this->p_iID << " wurde initialisiert" << endl;
}

/* Kopierkonstruktor */
Fahrzeug::Fahrzeug(Fahrzeug &fz) {
	vInitialisierung();

	p_sName = fz.p_sName;
	p_dMaxGeschwindigkeit = fz.p_dMaxGeschwindigkeit;

	/* p_dGesamtStrecke, p_dGesamtZeit, p_dZeit werden auf 0 gesetzt,
	 * da das kopierte noch keine Strecke zurückgelegt hat */
}

Fahrzeug::Fahrzeug(string sName) {
	vInitialisierung();

	p_sName = sName;
	//cout << this->p_sName << ":" << this->p_iID << " wurde initialisiert" << endl;
}

Fahrzeug::Fahrzeug(string sName, double dMaxGeschwindkeit) {
	vInitialisierung();

	p_sName = sName;
	p_dMaxGeschwindigkeit = dMaxGeschwindkeit;
}

Fahrzeug::~Fahrzeug() {
	//cout << this->p_sName << ":" << this->p_iID << " wurde gelöscht" << endl;
}

void Fahrzeug::vInitialisierung() {
	p_iID = ++p_iMaxID;

	p_sName = "";
	p_dMaxGeschwindigkeit = 0;
	p_dGesamtStrecke = 0;
	p_dGesamtZeit = 0;
	p_dZeit = 0;
}

void Fahrzeug::vAusgabeHeader() {
	cout << "ID  Name   :  MaxKmh   GesamtStrecke   Verbrauch   Tankinhalt" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void Fahrzeug::vAusgabe() const {
	cout << endl
		<< setprecision(2) << setiosflags(ios::fixed)
		<< resetiosflags(ios::right) << setiosflags(ios::left)
		<< setw(4) << p_iID
		<< setw(7) << p_sName << ":"
		<< resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(8) << dGeschwindigkeit()
		<< setw(16) << p_dGesamtStrecke;
}

ostream& Fahrzeug::ostreamAusgabe(ostream &stream) const {
	stream << setprecision(2) << setiosflags(ios::fixed)
		<< resetiosflags(ios::right) << setiosflags(ios::left)
		<< setw(4) << p_iID
		<< setw(7) << p_sName << ":"
		<< resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(8) << dGeschwindigkeit()
		<< setw(16) << p_dGesamtStrecke;

	return stream;
}

void Fahrzeug::vAbfertigung() {
	/* nicht doppelt abfertigen (Gleitkommavgl.) */
	if (fabs(p_dZeit - dGlobaleZeit) < 1e-10) return;

	double dDelta = dGlobaleZeit - p_dZeit;

	p_dGesamtZeit += dDelta;
	p_dGesamtStrecke += dGeschwindigkeit() * dDelta;
	p_dZeit = dGlobaleZeit;
}

double Fahrzeug::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dTanken(double dMenge) {
	return 0.0;
};

bool Fahrzeug::operator<(Fahrzeug &fz) const {
	return (this->p_dGesamtStrecke < fz.p_dGesamtStrecke);
}

ostream& operator<<(ostream &stream, const Fahrzeug &fz) {
	return fz.ostreamAusgabe(stream);
}
