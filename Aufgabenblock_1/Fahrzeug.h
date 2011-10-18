/*
 * Fahrzeug.h
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <string>

using namespace std;

class Fahrzeug {
public:
	Fahrzeug();
	Fahrzeug(Fahrzeug &fz); /* Kopier Konstruktor */
	Fahrzeug(string sName);
	Fahrzeug(string sName, double dMaxGeschwindkeit);

	virtual ~Fahrzeug();

	virtual void vAusgabe() const;
	virtual ostream& ostreamAusgabe(ostream &stream) const;

	virtual void vAbfertigung();
	virtual double dTanken(double dMenge = 0.0);
	virtual double dGeschwindigkeit() const;

	bool operator<(Fahrzeug &fz) const;
	//Fahrzeug & operator=(Fahrzeug &fz); /* benutze Standardzuweisungs Operator */

	static void vAusgabeHeader();

protected:
	int p_iID;
	std::string p_sName;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dZeit;

private:
	static int p_iMaxID;

	void vInitialisierung();
};

ostream& operator<<(ostream &out, const Fahrzeug &fz);

#endif /* FAHRZEUG_H_ */
