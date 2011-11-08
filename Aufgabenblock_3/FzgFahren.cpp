#include <stdlib.h>
#include <iostream>

#include "FzgFahren.h"
#include "Fahrzeug.h"
#include "Streckenende.h"

using namespace std;

FzgFahren::FzgFahren(Weg *pWeg) : FzgVerhalten(pWeg)
{ }

FzgFahren::~FzgFahren()
{ }

double FzgFahren::dStrecke(Fahrzeug *pFz, double dDelta) {
	double dStrecke = pFz->dGeschwindigkeit() * dDelta;

	if (pFz->getAbschnittStrecke() >= p_pWeg->getLaenge() - 1e-5) { /* bereits zuweit gefahren */
		throw Streckenende(pFz, p_pWeg);
	}
	else if (pFz->getAbschnittStrecke() + dStrecke > p_pWeg->getSchranke() - 1e-5) {
		return p_pWeg->getSchranke() - pFz->getAbschnittStrecke();
	}
	else if (pFz->getAbschnittStrecke() + dStrecke > p_pWeg->getLaenge() - 1e-5) { /* fahre nur bis zum Streckenende */
		return p_pWeg->getLaenge() - pFz->getAbschnittStrecke();
	}
	else { /* fahre maximal mögliche Strecke */
		p_pWeg->setSchranke(pFz->getAbschnittStrecke() + dStrecke);
		//cout << "Schranke gesetzt: " << p_pWeg->getSchranke() << " von: " << pFz->getName() << endl;
		return dStrecke;
	}
}

