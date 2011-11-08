#ifndef FZGVERHALTEN_H_
#define FZGVERHALTEN_H_

#include "Weg.h"

class FzgVerhalten {
public:
	FzgVerhalten(Weg *pWeg);
	virtual ~FzgVerhalten();

	virtual double dStrecke(Fahrzeug *pFz, double dDelta) = 0;
	Weg * getWeg();

protected:
	Weg *p_pWeg;

};

#endif /* FZGVERHALTEN_H_ */
