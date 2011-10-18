#ifndef FZGVERHALTEN_H_
#define FZGVERHALTEN_H_

#include "Weg.h"

class FzgVerhalten {
public:
	FzgVerhalten(Weg *pWeg);
	virtual ~FzgVerhalten();

	double dStrecke(Fahrzeug *pFz, double dZeit);

private:
	Weg * p_pWeg;

};

#endif /* FZGVERHALTEN_H_ */
