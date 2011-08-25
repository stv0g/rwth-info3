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
	Fahrzeug(string sName);
	virtual ~Fahrzeug();

	void vAusgabe();
	virtual void vAbfertigung();
	virtual double dTanken(double dMenge) { return 0; }; /* Kraftfahrzeuge überladen dTanken() */
	virtual double dGeschwindigkeit() { return p_dMaxGeschwindigkeit; }

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

#endif /* FAHRZEUG_H_ */
