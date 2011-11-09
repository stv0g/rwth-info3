#include <iostream>

#include "Losfahren.h"

using namespace std;

Losfahren::Losfahren(Fahrzeug *pFahrzeug, Weg *pWeg) : FahrAusnahme(pFahrzeug, pWeg)
{ }

Losfahren::~Losfahren()
{ }

void Losfahren::vBearbeiten() {
	cerr << "Fahrausnahme: Losfahren (Fzg: " << p_pFahrzeug->getName() << ", Weg: " << p_pWeg->getName() << ")" << endl;

	p_pWeg->vAbgabe(p_pFahrzeug);
	p_pWeg->vAnnahme(p_pFahrzeug);
}
