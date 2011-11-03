#include <string>
#include <vector>
#include <iostream>

#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"

using namespace std;

double dGlobaleZeit = 0.0;

void vAufgabe1() {
	/* 3. Initialisieren */
	Fahrzeug fz1("Porsche");
	Fahrzeug *fz2 = new Fahrzeug();

	string name;
	cout << "Bitte geben Sie einen Fahrzeugnamen ein: ";
	cin >> name;

	Fahrzeug *fz3 = new Fahrzeug(name, 22.5);

	Fahrzeug::vAusgabeHeader();
	fz1.vAusgabe();
	fz2->vAusgabe();
	fz3->vAusgabe();

	/* 9. Abfertigung */
	double dAbfertigungsIntervall;
	cout << endl << "Bitte geben Sie ein Abfertigungsintervall ein: ";
	cin >> dAbfertigungsIntervall;

	Fahrzeug::vAusgabeHeader();
	for ( ; dGlobaleZeit < 24; dGlobaleZeit += dAbfertigungsIntervall) { /* simuliere für einen Tag */
		fz1.vAbfertigung();
		fz2->vAbfertigung();
		fz3->vAbfertigung();

		cout << endl << "globale Zeit: " << dGlobaleZeit;
		fz1.vAusgabe();
		fz2->vAusgabe();
		fz3->vAusgabe();
	}

	delete fz2;
	delete fz3;
}

/**
 * Testing debugger
 */
void vAufgabe1_deb() {
	Fahrzeug fz1("Opel");
	Fahrzeug fz2("Benz");
	Fahrzeug fz3("Ferrari");
	Fahrzeug fz4("Mini");

	Fahrzeug *feld_name[4] = {&fz1, &fz2, &fz3, &fz4};

	feld_name[2] = 0; // NULL pointer => Segmention Fault

	for (int i = 0; i < 4; i++) {
		feld_name[i]->vAusgabe();
	}
}

void vAufgabe2() {
	int iPKWs, iFahrraeder;
	vector<Fahrzeug *> fahrzeuge;

	/* Erzeugen */

	cout << "Wie viele PKWs möchten Sie erstellen? ";
	cin >> iPKWs;

	cout << "Wie viele Fahrräder möchten Sie erstellen? ";
	cin >> iFahrraeder;

	for (int i = 0; i < iPKWs + iFahrraeder; i++) {
		Fahrzeug *fahrzeug;
		string sName;
		double dMaxGeschwindkeit;

		cout << "Bitte geben Sie den Namen des Fahrzeugs Nr. " << i+1 << " an: ";
		cin >> sName;
		cout << "Bitte geben Sie die maximale Geschwindkeit des Fahrzeugs Nr. " << i+1 << " an: ";
		cin >> dMaxGeschwindkeit;

		if (i < iPKWs) {	/* erzeuge PKW */
			double dVerbrauch;
			cout << "Bitte geben Sie den Verbrauch des PKWs Nr. " << i+1 << " an: ";
			cin >> dVerbrauch;

			fahrzeug = new PKW(sName, dMaxGeschwindkeit, dVerbrauch);
		}
		else {				/* erzeuge Fahrrad */
			fahrzeug = new Fahrrad(sName, dMaxGeschwindkeit);
		}

		fahrzeuge.push_back(fahrzeug);
	}

	/* Abfertigen */

	double dAbfertigungsIntervall;
	size_t iNachgetankt = 0;
	cout << "Bitte geben Sie ein Abfertigungsintervall ein: ";
	cin >> dAbfertigungsIntervall;
	cout << endl;

	Fahrzeug::vAusgabeHeader();

	for ( ; dGlobaleZeit < 24; dGlobaleZeit += dAbfertigungsIntervall) {
		vector<Fahrzeug *>::iterator it;
		for (it = fahrzeuge.begin(); it != fahrzeuge.end(); it++) {
			if (dGlobaleZeit > 3 && iNachgetankt < fahrzeuge.size()) {
				(*it)->dTanken();
				iNachgetankt++;
			}

			(*it)->vAbfertigung();
			(*it)->vAusgabe();
		}

		cout << endl << "Globale Zeit: " << dGlobaleZeit;
	}
}

void vAufgabe3() {
	PKW vw("Golf", 200, 6.7, 88);
	Fahrrad velo("Haibike", 22);
	Fahrzeug boat("Schiff", 11);

	dGlobaleZeit += 1.0;
	velo.vAbfertigung();
	vw.vAbfertigung();
	boat.vAbfertigung();

	Fahrzeug::vAusgabeHeader();
	cout << vw << endl << velo << endl << boat << endl << endl;

	if (vw < velo) {
		cout << "Das Fahrrad ist bereits weiter gefahren" << endl;
	}
	else {
		cout << "Der Golf ist bereits weiter gefahren" << endl;
	}
	cout << endl;

	Fahrrad veloKopie = velo;	/* benutze Kopier Konstrukutor */
	Fahrrad veloKopie2;

	veloKopie2 = velo;			/* benutze Zuweisungsoperator */

	Fahrzeug::vAusgabeHeader();
	cout << veloKopie << endl << veloKopie2 << endl;
}

typedef void (*aufgabe_t)(void);
#define NUM_AUFGABEN 4

int main() {
	int iWahl;

	aufgabe_t pAufgaben[] = {
			&vAufgabe1_deb,
			&vAufgabe1,
			&vAufgabe2,
			&vAufgabe3
	};

	retry:

	cout << "0: vAufgabe1_deb()" << endl;
	cout << "1: vAufgabe1()" << endl;
	cout << "2: vAufgabe2()" << endl;
	cout << "3: vAufgabe3()" << endl;
	cout << "Bitte wähen Sie eine Aufgabe: ";
	cin >> iWahl;
	cout << endl;

	if (iWahl > NUM_AUFGABEN || iWahl < 0) {
		cerr << "Ungültige Eingabe! Bitte versuchen Sie es erneut" << endl;
		goto retry;
	}
 
	pAufgaben[iWahl](); /* Funktionspointer aufrufen */
	
	cout << endl << endl << "Nochmal? (0/1): ";
	cin >> iWahl;
	cout << endl;

	if (iWahl) {
		goto retry;
	}

	return 0;
}
