#include <stdlib.h>

#include "FzgVerhalten.h"
#include "Fahrzeug.h"

extern double dGlobaleZeit;

FzgVerhalten::FzgVerhalten(Weg *pWeg) {
	p_pWeg = pWeg;
}

/* Destruktor */
FzgVerhalten::~FzgVerhalten()
{ }

double FzgVerhalten::dStrecke(Fahrzeug *pFz, double dDelta) {
	double dStrecke = pFz->dGeschwindigkeit() * dDelta;

	if (pFz->getAbschnittStrecke() >= p_pWeg->getLaenge()) { /* bereits zuweit gefahren */
		exit(0);
	}
	else if (pFz->getAbschnittStrecke() + dStrecke > p_pWeg->getLaenge()) { /* fahre nur bis zum Streckenende */
		return p_pWeg->getLaenge() - pFz->getAbschnittStrecke();
	}
	else { /* fahre maximal mögliche Strecke */
		return dStrecke;
	}
}
