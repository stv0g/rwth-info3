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
private:
	double p_dVerbrauch;
	double p_dTankinhalt;
	double p_dTankvolumen;

public:
	PKW(string sName, double dTankvolumen);
	PKW(double dTankvolumen);
	virtual ~PKW();

	void vAbfertigung();
	void vAusgabe();
	double dVerbrauch();
	double dTanken(double dMenge);
};

#endif /* PKW_H_ */
