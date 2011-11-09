#ifndef WEG_H_
#define WEG_H_

#include <list>
#include <string>

#include "AktivesVO.h"
#include "LazyListe.h"
#include "SimuClient.h"

using namespace std;

/* Forward Deklarationen */
class Fahrzeug;
class Kreuzung;

class Weg : public AktivesVO {
public:
	typedef enum {
		Innerorts = 1,	/* 50 km/h */
		Landstrasse,	/* 100 km/h */
		Autobahn		/* unbegrenzt */
	} Begrenzung;

	Weg();
	Weg(string sName, double dLaenge, Begrenzung eLimit = Autobahn, bool dUeberholverbot = true);
	virtual ~Weg();

	void vAbfertigung();
	void vAnnahme(Fahrzeug *pFz, double dStartZeit = 0);
	void vAbgabe(Fahrzeug *pFz);
	void vZeichnen(size_t iAnzahlKoordinaten, Koordinaten iKoordinaten[]) const; /* zeichnet Weg */
	void vZeichnen() const; /* zeichnet Fahrzeuge, die sich auf dem Weg befinden */

	double getMaxGeschwindigkeit() const;
	double getSchranke() const;
	void setSchranke(double dSchranke);
	double getLaenge() const;
	void setRueckweg(Weg * pRueckweg);
	Weg * getRueckweg();
	void setZielKreuzung(Kreuzung * pZielKreuzung);
	Kreuzung * getZielKreuzung();

	ostream& ostreamAusgabe(ostream &stream) const;

private:
	double p_dLaenge;
	double p_dSchranke;
	bool p_dUeberholverbot;
	Begrenzung p_eLimit;
	LazyListe<Fahrzeug *> p_lFahrzeuge;

	Kreuzung *p_pZielKreuzung;
	Weg *p_pRueckweg;
};

#endif /* WEG_H_ */
