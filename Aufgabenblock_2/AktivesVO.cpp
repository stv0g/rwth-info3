#include <iostream>
#include <iomanip>

#include "AktivesVO.h"

extern double dGlobaleZeit;

int AktivesVO::p_iMaxID = 0;

AktivesVO::AktivesVO() {
	vInitialisierung();
}

AktivesVO::AktivesVO(string sName) {
	vInitialisierung();

	p_sName = sName;
}

AktivesVO::AktivesVO(AktivesVO &vo) {
	vInitialisierung();

	p_sName = vo.p_sName;
}

AktivesVO::~AktivesVO() {
}

void AktivesVO::vInitialisierung() {
	p_iID = ++p_iMaxID;

	p_sName = "";
	p_dZeit = 0;
}

void AktivesVO::vAusgabeHeader() {
	cout << "Zeit ID  Name   :     Kmh   GesamtStrecke   Verbrauch   Tankinhalt" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
			<< endl;
}

ostream& AktivesVO::ostreamAusgabe(ostream &stream) const {
	stream << setprecision(1) << setiosflags(ios::fixed)
		<< resetiosflags(ios::right) << setiosflags(ios::left)
		<< setw(5) << dGlobaleZeit
		//<< " (" << setw(3) << p_dZeit << ") "
		<< setw(4) << p_iID
		<< setw(7) << p_sName << ":";

	return stream;
}

string AktivesVO::getName() const {
	return p_sName;
}

ostream& operator<<(ostream &stream, const AktivesVO &vo) {
	return vo.ostreamAusgabe(stream);
}
