#include <iostream>
#include <string>

#include "Welt.h"
#include "PKW.h"
#include "Weg.h"
#include "Fahrrad.h"

Welt::Welt()
{ }

Welt::~Welt()
{ }

void Welt::vAbfertigung() {
	list<Kreuzung *>::iterator it;
	for (it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); it++) {
		(*it)->vAbfertigung();
	}
}

void Welt::vZeichnen() {
	list<Kreuzung *>::iterator it;
	for (it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); it++) {
		(*it)->vZeichnen();
	}
}

ostream& Welt::ostreamAusgabe(ostream &stream) const {
	list<Kreuzung *>::const_iterator it;
	for (it = p_pKreuzungen.begin(); it != p_pKreuzungen.end(); it++) {
		stream << **it << endl;
	}

	return stream;
}

ostream& operator<<(ostream &stream, const Welt &w) {
	return w.ostreamAusgabe(stream);
}

void Welt::vEinlesen(istream &in) {
	while (!in.eof()) {
		string sTyp;
		in >> sTyp;

		if (sTyp == "KREUZUNG") {
			Kreuzung *pKr = new Kreuzung;
			in >> *pKr;

			p_pKreuzungen.push_back(pKr);
		}
		else if (sTyp == "STRASSE") {
			string sQuellKreuzung, sZielKreuzung;
			string sHinweg, sRueckweg;
			double dLaenge;
			int eLimit;
			bool bUeberholverbot;

			/* Daten einlesen */
			in >> sQuellKreuzung
				>> sZielKreuzung
				>> sHinweg
				>> sRueckweg
				>> dLaenge
				>> eLimit
				>> bUeberholverbot;

			/* Kreuzungen suchen */
			Kreuzung *pQuellKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sQuellKreuzung));
			Kreuzung *pZielKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sZielKreuzung));

			eLimit--;
			if (eLimit > 2 || eLimit < 0) {
				throw string("Ungültige Geschwindikeitsbegrenzung (0-2)");
			}

			/* Kreuzungen verbinden & Wege erstellen */
			pQuellKreuzung->vVerbinde(pZielKreuzung, sHinweg, sRueckweg, dLaenge, static_cast<Weg::Begrenzung >(eLimit), bUeberholverbot);
		}
		else if (sTyp == "PKW") {
			PKW *pPkw = new PKW();
			string sStartKreuzung;
			double dStartZeit;

			/* Daten einlesen */
			in >> *pPkw >> sStartKreuzung >> dStartZeit;

			/* PKW einsetzen */
			Kreuzung *pStartKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sStartKreuzung));
			pStartKreuzung->vAnnahme(pPkw, dStartZeit);
		}
		else if (sTyp == "FAHRRAD") {
			Fahrrad *pRad = new Fahrrad();
			string sStartKreuzung;
			double dStartZeit;

			/* Daten einlesen */
			in >> *pRad >> sStartKreuzung >> dStartZeit;

			/* PKW einsetzen */
			Kreuzung *pStartKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sStartKreuzung));
			pStartKreuzung->vAnnahme(pRad, dStartZeit);
		}
		else if (sTyp != "") {
			throw string("Unbekannter Typ!");
		}
	}
}

void Welt::vEinlesenMitGrafik(istream &in) {
	while (!in.eof()) {
		string sTyp;
		in >> sTyp;

		if (sTyp == "KREUZUNG") {
			Kreuzung *pKr = new Kreuzung;
			Koordinaten iPos;
			in >> *pKr >> iPos.x >> iPos.y;

			pKr->vZeichnen(iPos);
			p_pKreuzungen.push_back(pKr);
		}
		else if (sTyp == "STRASSE") {
			string sQuellKreuzung, sZielKreuzung;
			string sHinweg, sRueckweg;
			double dLaenge;
			int eLimit, iAnzahlKoordinaten;
			bool bUeberholverbot;

			/* Daten einlesen */
			in >> sQuellKreuzung
				>> sZielKreuzung
				>> sHinweg
				>> sRueckweg
				>> dLaenge
				>> eLimit
				>> bUeberholverbot
				>> iAnzahlKoordinaten;

			Koordinaten *iPoly = new Koordinaten[iAnzahlKoordinaten];
			for (int i = 0; i < iAnzahlKoordinaten; i++) {
				in >> iPoly[i].x >> iPoly[i].y;
			}

			/* Kreuzungen suchen */
			Kreuzung *pQuellKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sQuellKreuzung));
			Kreuzung *pZielKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sZielKreuzung));

			/* Kreuzungen verbinden & Wege erstellen */
			pQuellKreuzung->vVerbinde(pZielKreuzung, sHinweg, sRueckweg, dLaenge, static_cast<Weg::Begrenzung >(eLimit), bUeberholverbot);

			/* Wege Zeichnen */
			Weg *pHinweg = static_cast<Weg *>(AktivesVO::pObjekt(sHinweg));
			pHinweg->vZeichnen(iAnzahlKoordinaten, iPoly);
		}
		else if (sTyp == "PKW") {
			PKW *pPkw = new PKW();
			string sStartKreuzung;
			double dStartZeit;

			/* Daten einlesen */
			in >> *pPkw >> sStartKreuzung >> dStartZeit;

			/* PKW einsetzen */
			Kreuzung *pStartKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sStartKreuzung));
			pStartKreuzung->vAnnahme(pPkw, dStartZeit);
		}
		else if (sTyp == "FAHRRAD") {
			Fahrrad *pRad = new Fahrrad();
			string sStartKreuzung;
			double dStartZeit;

			/* Daten einlesen */
			in >> *pRad >> sStartKreuzung >> dStartZeit;

			/* PKW einsetzen */
			Kreuzung *pStartKreuzung = static_cast<Kreuzung *>(AktivesVO::pObjekt(sStartKreuzung));
			pStartKreuzung->vAnnahme(pRad, dStartZeit);
		}
		else if (sTyp != "") {
			throw string("Unbekannter Typ!");
		}
	}
}
