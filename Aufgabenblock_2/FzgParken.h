#ifndef FZGPARKEN_H_
#define FZGPARKEN_H_

#include "FzgVerhalten.h"

class FzgParken: public FzgVerhalten {
public:
	FzgParken(Weg *pWeg, double dStartZeit);
	virtual ~FzgParken();

	double dStrecke(Fahrzeug *pFz, double dDelta);

private:
	double p_dStartZeit;
};

#endif /* FZGPARKEN_H_ */
