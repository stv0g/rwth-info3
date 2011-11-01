#ifndef FZGFAHREN_H_
#define FZGFAHREN_H_

#include "FzgVerhalten.h"

class FzgFahren: public FzgVerhalten {
public:
	FzgFahren(Weg *pWeg);
	virtual ~FzgFahren();

	double dStrecke(Fahrzeug *pFz, double dDelta);
};

#endif /* FZGFAHREN_H_ */
