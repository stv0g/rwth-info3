#include <iostream>
#include <iomanip>

#include "AktivesVO.h"

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

ostream& AktivesVO::ostreamAusgabe(ostream &stream) const {
	stream << setprecision(2) << setiosflags(ios::fixed)
		<< resetiosflags(ios::right) << setiosflags(ios::left)
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
