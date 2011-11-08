#ifndef WELT_H_
#define WELT_H_

#include <list>

#include "Kreuzung.h"

class Welt {
public:
	Welt();
	virtual ~Welt();

	void vAbfertigung();
	void vZeichnen();
	void vEinlesen(istream &in);
	void vEinlesenMitGrafik(istream &in);
	virtual ostream& ostreamAusgabe(ostream &stream) const;

private:
	list<Kreuzung *> p_pKreuzungen;

};

ostream& operator<<(ostream &out, const Welt &w);

#endif /* WELT_H_ */
