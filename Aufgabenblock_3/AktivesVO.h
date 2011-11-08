#ifndef AKTIVESVO_H_
#define AKTIVESVO_H_

#include <string>
#include <map>

using namespace std;

class AktivesVO {
public:
	AktivesVO();
	AktivesVO(AktivesVO &vo);
	AktivesVO(string sName);
	virtual ~AktivesVO();

	static void vAusgabeHeader();
	static AktivesVO * pObjekt(string sName);

	virtual ostream& ostreamAusgabe(ostream &stream) const;
	virtual istream& istreamEingabe(istream &stream);

	virtual void vAbfertigung() = 0; /* AktivesVO ist eine abstrakte Klasse */
	virtual void vZeichnen() const = 0;

	string getName() const;

protected:
	double p_dZeit;

	 /* nicht virtuell, da virtuelle Funktionen nicht
	  * in Konstruktoren aufgerufen werden dürfen!!! */
	void vInitialisierung();
	void vRegister();

private:
	static int p_iMaxID;
	static map<string, AktivesVO*> p_pObjekte;

	int p_iID;
	string p_sName;
};

ostream& operator<<(ostream &out, const AktivesVO &vo);
istream& operator>>(istream &in, AktivesVO &vo);

#endif /* AKTIVESVO_H_ */
