#include <iostream>
#include <string>
#include <iomanip>

#include "AktivesVO.h"

extern double dGlobaleZeit;

int AktivesVO::p_iMaxID = 0;
map<string, AktivesVO*> AktivesVO::p_pObjekte;

AktivesVO::AktivesVO() {
	vInitialisierung();
}

AktivesVO::AktivesVO(string sName) {
	vInitialisierung();
	p_sName = sName;
	vRegister();
}

AktivesVO::AktivesVO(AktivesVO &vo) {
	vInitialisierung();
	p_sName = vo.p_sName;
	vRegister();
}

AktivesVO::~AktivesVO() {
	p_pObjekte.erase(p_sName);
}

void AktivesVO::vRegister() {
	map<string, AktivesVO*>::iterator result = p_pObjekte.find(p_sName);
	if (result != p_pObjekte.end()) {
		throw string("Ein Objekt mit dem Namen existiert bereits!");
	}

	p_pObjekte[p_sName] = this;
}

AktivesVO * AktivesVO::pObjekt(string sName) {
	map<string, AktivesVO*>::iterator result = p_pObjekte.find(sName);
	if (result == p_pObjekte.end()) {
		throw string("Ein Objekt mit dem Namen existiert nicht!");
	}

	return result->second;
}

void AktivesVO::vInitialisierung() {
	p_iID = ++p_iMaxID;

	p_sName = "";
	p_dZeit = 0;
}

void AktivesVO::vAusgabeHeader() {
	cout << "ID Zeit  Name     :       Kmh  Strecke  Abschnitt  Verbrauch  Tankinhalt" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
			<< endl;
}

ostream& AktivesVO::ostreamAusgabe(ostream &stream) const {
	stream << setprecision(1) << setiosflags(ios::fixed)
		<< resetiosflags(ios::right) << setiosflags(ios::left)
		<< setw(3) << p_iID
		<< setw(6) << p_dZeit
		<< setw(9) << p_sName << ":";

	return stream;
}

istream& AktivesVO::istreamEingabe(istream &stream) {
	if (p_sName != "") {
		throw string("Verkehrsobjekt ist bereits initialisiert!");
	}

	stream >> p_sName;

	vRegister();

	return stream;
}

string AktivesVO::getName() const {
	return p_sName;
}

ostream& operator<<(ostream &stream, const AktivesVO &vo) {
	return vo.ostreamAusgabe(stream);
}

istream& operator>>(istream &in, AktivesVO &vo) {
	return vo.istreamEingabe(in);
}
