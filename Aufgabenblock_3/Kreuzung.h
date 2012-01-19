#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "SimuClient.h"
#include "AktivesVO.h"
#include "Weg.h"

class Kreuzung: public AktivesVO {
public:
	Kreuzung();
	Kreuzung(string sName, double dTankvolumen = 0);
	virtual ~Kreuzung();

	void vVerbinde(Kreuzung *pZielKreuzung, string sHinweg, string sRueckweg, double dLaenge, Weg::Begrenzung eLimit, bool bUeberholverbot);
	void vTanken(Fahrzeug *pFz);
	void vAnnahme(Fahrzeug *pFz, double dStartZeit = 0, Weg *pAlterWeg = NULL);
	void vAbfertigung();
	void vZeichnen() const;
	void vZeichnen(Koordinaten iKoordinaten) const;
	Weg * pZufaelligerWeg(Weg *pAlterWeg = NULL);

	double getTankinhalt();

	ostream& ostreamAusgabe(ostream &stream) const;
	istream& istreamEingabe(istream &stream);

private:
	list<Weg *> p_lWege;
	double p_dTankstelle;
};

#endif /* KREUZUNG_H_ */
