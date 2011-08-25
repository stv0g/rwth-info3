/*
 * Fahrrad.h
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

using namespace std;

class Fahrrad: public Fahrzeug {
public:
	Fahrrad();
	virtual ~Fahrrad();

	double dGeschwindigkeit();
	void vAusgabe();

	static Fahrrad * erzeuge(string sName, double dMaxGeschwindigkeit);
};

#endif /* FAHRRAD_H_ */
