#include <float.h>

#include "FzgVerhalten.h"

extern double dGlobaleZeit;

FzgVerhalten::FzgVerhalten(Weg *pWeg) {
	p_pWeg = pWeg;
}

/* Destruktor */
FzgVerhalten::~FzgVerhalten()
{ }

double FzgVerhalten::getMaxgeschwindigkeit() {
	switch (p_pWeg->getLimit()) {
		case Innerorts:		return 50;
		case Landstrasse:	return 100;
		case Autobahn:		return DBL_MAX; /* unbegrenzt */
		default:			return 0;
	}
}
