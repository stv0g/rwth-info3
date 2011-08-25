/*
 * main.cpp
 *
 *  Created on: 18.08.2011
 *      Author: stv0g
 */

#include <string>
#include <iostream>

#include "Fahrzeug.h"

using namespace std;

double dGlobaleZeit = 0.0;

void vAufgabe1() {
	/* 3. Initialisieren */
	Fahrzeug fz1("Porsche");
	Fahrzeug *fz2 = new Fahrzeug();

	string name;
	cout << "Bitte geben Sie einen Fahrzeugnamen ein: ";
	cin >> name;

	Fahrzeug *fz3 = new Fahrzeug(name);

	/* 5. Ausgabe */
	cout << endl << "ID  Name   :  MaxKmh   GesamtStrecke" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
	fz1.vAusgabe();
	fz2->vAusgabe();
	fz3->vAusgabe();

	/* 9. Abfertigung */
	double dAbfertigungsIntervall;
	cout << endl << "Bitte geben Sie ein Abfertigungsintervall ein: ";
	cin >> dAbfertigungsIntervall;

	cout << endl << "ID  Name   :  MaxKmh   GesamtStrecke" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
	for (; dGlobaleZeit < 24; dGlobaleZeit += dAbfertigungsIntervall) { /* simuliere für einen Tag */
		fz1.vAbfertigung();
		fz2->vAbfertigung();
		fz3->vAbfertigung();

		cout << "globale Zeit: " << dGlobaleZeit << endl;
		fz1.vAusgabe();
		fz2->vAusgabe();
		fz3->vAusgabe();
	}

	delete fz2;
	delete fz3;
}

void vAufgabe1_deb() {
	Fahrzeug fz1("Opel");
	Fahrzeug fz2("Benz");
	Fahrzeug fz3("Ferrari");
	Fahrzeug fz4("Mini");

	Fahrzeug *feld_name[4] = {&fz1, &fz2, &fz3, &fz4};

	feld_name[2] = 0;

	for (int i = 0; i < 4; i++) {
		feld_name[i]->vAusgabe();
	}
}

void vAufgabe2() {
	int iAnzahl;
	vector<Fahrzeug *> fahrzeuge;

	cout << "Wie viele Fahrzeuge möchten Sie erstellen? ";
	cin >> iAnzahl;

	for (int j = 0; j < i; j++) {
		fahrzeuge.push(Fahrrad::erzeuge());
	}
}

int main() {
	//vAufgabe1();
	//vAufgabe1_deb();
	vAugabe2();

	return 0;
}
