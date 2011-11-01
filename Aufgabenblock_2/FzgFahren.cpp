#include <stdlib.h>

#include "FzgFahren.h"
#include "Fahrzeug.h"
#include "Streckenende.h"

FzgFahren::FzgFahren(Weg *pWeg) : FzgVerhalten(pWeg)
{ }

FzgFahren::~FzgFahren()
{ }

double FzgFahren::dStrecke(Fahrzeug *pFz, double dDelta) {
	double dStrecke = pFz->dGeschwindigkeit() * dDelta;

	if (pFz->getAbschnittStrecke() >= p_pWeg->getLaenge()) { /* bereits zuweit gefahren */
		throw Streckenende(pFz, p_pWeg);
	}
	else if (pFz->getAbschnittStrecke() + dStrecke > p_pWeg->getLaenge()) { /* fahre nur bis zum Streckenende */
		return p_pWeg->getLaenge() - pFz->getAbschnittStrecke();
	}
	else { /* fahre maximal mögliche Strecke */
		return dStrecke;
	}
}

