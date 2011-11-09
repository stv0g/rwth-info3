#include <iostream>

#include "Streckenende.h"
#include "Kreuzung.h"

using namespace std;

Streckenende::Streckenende(Fahrzeug *pFahrzeug, Weg *pWeg) : FahrAusnahme(pFahrzeug, pWeg)
{ }

Streckenende::~Streckenende()
{ }

void Streckenende::vBearbeiten() {
	Kreuzung *pZielKreuzung = p_pWeg->getZielKreuzung();

	p_pWeg->vAbgabe(p_pFahrzeug);

	cerr << "Fahrausnahme: Fahrzeug wird umgesetzt ("
		<< "Fzg: " << p_pFahrzeug->getName()
		<< ", Weg: " << p_pWeg->getName();

	if (pZielKreuzung != NULL) {
		Weg *pNeuerWeg = pZielKreuzung->pZufaelligerWeg(p_pWeg); /* wähle zufälligen Weg */

		pZielKreuzung->vTanken(p_pFahrzeug);
		pZielKreuzung->vAnnahme(p_pFahrzeug, 0, pNeuerWeg);

		cerr << " => " << pNeuerWeg->getName() << ", Kreuz.: " << pZielKreuzung->getName() << " (Tank: " << pZielKreuzung->getTankinhalt() << ")";
	}

	cerr << ")" << endl;
}
