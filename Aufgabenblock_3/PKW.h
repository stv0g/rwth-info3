/*
 * PKW.h
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#ifndef PKW_H_
#define PKW_H_

#include <string>

#include "Fahrzeug.h"

using namespace std;

class PKW: public Fahrzeug {
public:
	PKW();
	PKW(string sName, double dMaxGeschwindigkeit);
	PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);
	virtual ~PKW();

	void vAbfertigung();
	double dVerbrauch() const;
	double dTanken(double dMenge = 0.0);
	void vZeichnen() const;
	double getTankinhalt() const;

	ostream& ostreamAusgabe(ostream &stream) const;
	istream& istreamEingabe(istream &stream);

private:
	double p_dVerbrauch;
	double p_dTankinhalt;
	double p_dTankvolumen;
};

#endif /* PKW_H_ */
