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
	Weg *pNeuerWeg = pZielKreuzung->pZufaelligerWeg(p_pWeg); /* wähle zufälligen Weg */

	p_pWeg->vAbgabe(p_pFahrzeug);
	pZielKreuzung->vTanken(p_pFahrzeug);
	pZielKreuzung->vAnnahme(p_pFahrzeug, 0, pNeuerWeg);

	cerr << "Fahrausnahme: Fahrzeug wird umgesetzt ("
			<< "Fzg: " << p_pFahrzeug->getName()
			<< ", Weg: " << p_pWeg->getName() << " => " << pNeuerWeg->getName()
			<< ", Kreuz.: " << pZielKreuzung->getName() << " (Tank: " << pZielKreuzung->getTankinhalt() << ")"
			<< ")" << endl;
}
