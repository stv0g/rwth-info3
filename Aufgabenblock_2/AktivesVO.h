#ifndef AKTIVESVO_H_
#define AKTIVESVO_H_

#include <string>

using namespace std;

class AktivesVO {
public:
	AktivesVO();
	AktivesVO(AktivesVO &vo);
	AktivesVO(string sName);
	virtual ~AktivesVO();

	virtual ostream& ostreamAusgabe(ostream &stream) const;
	virtual void vAbfertigung() = 0; /* AktivesVO ist eine abstrakte Klasse */

	string getName() const;

protected:
	double p_dZeit;

	 /* nicht virtuell, da virtuelle Funktionen nicht
	  * in Konstruktoren aufgerufen werden dürfen!!! */
	void vInitialisierung();

private:
	static int p_iMaxID;
	int p_iID;
	string p_sName;
};

ostream& operator<<(ostream &out, const AktivesVO &vo);

#endif /* AKTIVESVO_H_ */
