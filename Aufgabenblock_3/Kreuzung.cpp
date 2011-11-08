#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "Kreuzung.h"
#include "Fahrzeug.h"

using namespace std;

extern double dGlobaleZeit;

Kreuzung::Kreuzung() :
		AktivesVO()
{}

Kreuzung::Kreuzung(string sName, double dTankvolumen) :
	AktivesVO(sName),
	p_dTankstelle(dTankvolumen)
{ }

void Kreuzung::vVerbinde(Kreuzung *pZielKreuzung, string sHinweg, string sRueckweg, double dLaenge, Weg::Begrenzung eLimit, bool bUeberholverbot) {
	Weg *pHinweg =  new Weg(sHinweg, dLaenge, eLimit, bUeberholverbot);
	Weg *pRueckweg =  new Weg(sRueckweg, dLaenge, eLimit, bUeberholverbot);

	pHinweg->setZielKreuzung(pZielKreuzung);
	pRueckweg->setZielKreuzung(this);

	pHinweg->setRueckweg(pRueckweg);
	pRueckweg->setRueckweg(pHinweg);

	p_lWege.push_back(pHinweg);
	pZielKreuzung->p_lWege.push_back(pRueckweg);
}

void Kreuzung::vTanken(Fahrzeug *pFz) {
	if (p_dTankstelle > 0) {
		p_dTankstelle -= pFz->dTanken(); /* immmer volltanken */
	}
	else {
		p_dTankstelle = 0;
	}
}

void Kreuzung::vAnnahme(Fahrzeug *pFz, double dStartZeit, Weg *pNeuerWeg) {
	if (pNeuerWeg != NULL) {
		pNeuerWeg->vAnnahme(pFz, dStartZeit);
	}
	else {
		p_lWege.front()->vAnnahme(pFz, dStartZeit);
	}
}

double Kreuzung::getTankinhalt() {
	return p_dTankstelle;
}

void Kreuzung::vAbfertigung() {
	if (p_dZeit >= dGlobaleZeit - 1e-10) return;

	list<Weg *>::iterator it;
	for (it = p_lWege.begin(); it != p_lWege.end(); it++) {
		(*it)->vAbfertigung();
	}

	p_dZeit = dGlobaleZeit;
}

void Kreuzung::vZeichnen() const {
	list<Weg *>::const_iterator it;
	for (it = p_lWege.begin(); it != p_lWege.end(); it++) {
			(*it)->vZeichnen();
	}
}

void Kreuzung::vZeichnen(Koordinaten iKoordinaten) const {
	bZeichneKreuzung(iKoordinaten.x, iKoordinaten.y);
}

ostream& Kreuzung::ostreamAusgabe(ostream &stream) const {
	AktivesVO::ostreamAusgabe(stream) << setprecision(2)
		<< resetiosflags(ios::left) << setiosflags(ios::right)
		<< setw(8) << p_dTankstelle << "                 ( ";

	list<Weg *>::const_iterator it;
	for (it = p_lWege.begin(); it != p_lWege.end(); it++) {
		stream << (*it)->getName() << " ";
	}
	stream << ")";


	for (it = p_lWege.begin(); it != p_lWege.end(); it++) {
		stream << endl << **it;
	}

	return stream;
}

istream& Kreuzung::istreamEingabe(istream &stream) {
	AktivesVO::istreamEingabe(stream) >> p_dTankstelle;

	return stream;
}

Weg * Kreuzung::pZufaelligerWeg(Weg *pAlterWeg) {
	Weg *pZufallWeg = NULL;

	do {
		list<Weg *>::iterator it;
		int iZufall = rand() % p_lWege.size();
		int i = 0;

		for (it = p_lWege.begin(); it != p_lWege.end(); it++) {
			pZufallWeg = *it;

			if (i++ >= iZufall) break;
		}
	} while (pZufallWeg == pAlterWeg->getRueckweg() && p_lWege.size() > 1);

	return pZufallWeg;
}

Kreuzung::~Kreuzung()
{ }
