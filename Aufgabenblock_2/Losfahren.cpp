#include <iostream>

#include "Losfahren.h"

using namespace std;

Losfahren::Losfahren(Fahrzeug *pFahrzeug, Weg *pWeg) : FahrAusnahme(pFahrzeug, pWeg)
{ }

Losfahren::~Losfahren()
{ }

void Losfahren::vBearbeiten() {
	cout << "Fahrausnahme: Losfahren (Fzg: " << *p_pFahrzeug << ", Weg: " << *p_pWeg << ")" << endl;
}
