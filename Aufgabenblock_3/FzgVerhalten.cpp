#include "FzgVerhalten.h"

extern double dGlobaleZeit;

FzgVerhalten::FzgVerhalten(Weg *pWeg) {
	p_pWeg = pWeg;
}

/* Destruktor */
FzgVerhalten::~FzgVerhalten()
{ }

Weg * FzgVerhalten::getWeg() {
	return p_pWeg;
}
