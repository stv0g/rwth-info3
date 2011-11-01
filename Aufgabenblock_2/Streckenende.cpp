#include <iostream>

#include "Streckenende.h"

using namespace std;

Streckenende::Streckenende(Fahrzeug *pFahrzeug, Weg *pWeg) : FahrAusnahme(pFahrzeug, pWeg)
{ }

Streckenende::~Streckenende()
{ }

void Streckenende::vBearbeiten() {
	cout << "Fahrausnahme: Streckenende (Fzg: " << *p_pFahrzeug << ", Weg: " << *p_pWeg << ")" << endl;
}
