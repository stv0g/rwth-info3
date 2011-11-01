#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "AktivesVO.h"
#include "FzgVerhalten.h"

using namespace std;

class Weg;

class Fahrzeug : public AktivesVO {
public:
	Fahrzeug();
	Fahrzeug(Fahrzeug &fz); /* Kopier Konstruktor */
	Fahrzeug(string sName);
	Fahrzeug(string sName, double dMaxGeschwindkeit);

	virtual ~Fahrzeug(); /* Destruktor */

	virtual void vAbfertigung();
	virtual double dTanken(double dMenge = 0.0);
	virtual double dGeschwindigkeit() const;
	void vNeueStrecke(Weg *pWeg, double dStartZeit = 0.0);

	double getAbschnittStrecke() const;

	bool operator<(Fahrzeug &fz) const;
	//Fahrzeug & operator=(Fahrzeug &fz); /* benutze Standardzuweisungs Operator */

	virtual ostream& ostreamAusgabe(ostream &stream) const;

protected:
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dAbschnittStrecke;
	FzgVerhalten * p_pVerhalten;

private:
	void vInitialisierung();
};

#endif /* FAHRZEUG_H_ */
