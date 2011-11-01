#include <stdlib.h>

#include "FzgParken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

extern double dGlobaleZeit;

FzgParken::FzgParken(Weg *pWeg, double dStartZeit) : FzgVerhalten(pWeg) {
	p_dStartZeit = dStartZeit;
}

FzgParken::~FzgParken()
{ }

double FzgParken::dStrecke(Fahrzeug *pFz, double dDelta) {
	if (p_dStartZeit > dGlobaleZeit) {
		return 0.0;
	}
	else {
		throw Losfahren(pFz, p_pWeg);
	}
}
