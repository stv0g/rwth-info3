#ifndef WEG_H_
#define WEG_H_

#include <list>
#include <string>

#include "AktivesVO.h"

using namespace std;

class Fahrzeug; /* Forward Deklaration */

typedef enum {
	Innerorts,		/* 50 km/h */
	Landstrasse,	/* 100 km/h */
	Autobahn		/* unbegrenzt */
} Begrenzung;

class Weg : public AktivesVO {
public:
	Weg();
	Weg(string sName, double dLaenge, Begrenzung eLimit = Autobahn);
	virtual ~Weg();

	void vAbfertigung();
	void vAnnahme(Fahrzeug *pFz);

	double getLaenge() const;

	ostream& ostreamAusgabe(ostream &stream) const;

private:
	double p_dLaenge;
	Begrenzung p_eLimit;
	list<Fahrzeug *> p_pFahrzeuge;
};

#endif /* WEG_H_ */