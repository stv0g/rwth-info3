#ifndef WEG_H_
#define WEG_H_

#include <list>
#include <string>

#include "AktivesVO.h"
#include "LazyListe.h"

using namespace std;

class Fahrzeug; /* Forward Deklaration */

class Weg : public AktivesVO {
public:
	typedef enum {
		Innerorts,		/* 50 km/h */
		Landstrasse,	/* 100 km/h */
		Autobahn		/* unbegrenzt */
	} Begrenzung;

	Weg();
	Weg(string sName, double dLaenge, Begrenzung eLimit = Autobahn);
	virtual ~Weg();

	void vAbfertigung();
	void vAnnahme(Fahrzeug *pFz, double dStartZeit = 0);
	void vAbgabe(Fahrzeug *pFz);

	double getLaenge() const;
	Begrenzung getLimit() const;

	ostream& ostreamAusgabe(ostream &stream) const;

private:
	double p_dLaenge;
	Begrenzung p_eLimit;
	LazyListe<Fahrzeug *> p_pFahrzeuge;
};

#endif /* WEG_H_ */
