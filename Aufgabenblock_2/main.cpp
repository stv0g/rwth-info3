#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "SimuClient.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include "LazyListe.h"

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
	cout << fz1 << endl << *fz2 << endl << *fz3 << endl;

	/* 9. Abfertigung */
	double dAbfertigungsIntervall;
	cout << endl << "Bitte geben Sie ein Abfertigungsintervall ein: ";
	cin >> dAbfertigungsIntervall;

	Fahrzeug::vAusgabeHeader();
	for ( ; dGlobaleZeit < 24; dGlobaleZeit += dAbfertigungsIntervall) { /* simuliere für einen Tag */
		fz1.vAbfertigung();
		fz2->vAbfertigung();
		fz3->vAbfertigung();

		cout << fz1 << endl << *fz2 << endl << *fz3 << endl;
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
		cout << *feld_name[i] << endl;
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

	for ( ; dGlobaleZeit < 6; dGlobaleZeit += dAbfertigungsIntervall) {
		vector<Fahrzeug *>::iterator it;
		for (it = fahrzeuge.begin(); it != fahrzeuge.end(); it++) {
			if (dGlobaleZeit > 3 && iNachgetankt < fahrzeuge.size()) {
				(*it)->dTanken();
				iNachgetankt++;
			}

			(*it)->vAbfertigung();
			cout << **it << endl;
		}
	}
}

void vAufgabe3() {
	PKW vw("Golf", 200, 6.7, 88);
	Fahrrad velo("Haibike", 22);
	Fahrzeug boat("Schiff", 11);

	dGlobaleZeit += 1.0;
	velo.vAbfertigung();

	Fahrzeug::vAusgabeHeader();
	cout << vw << endl << velo << endl << boat << endl << endl;

	if (vw < velo) {
		cout << "Das Fahrrad ist bereits weiter gefahren";
	}
	else {
		cout << "Der Golf ist bereits weiter gefahren";
	}

	cout << endl << endl;

	Fahrrad veloKopie = velo;	/* benutze Kopier Konstrukutor */
	Fahrrad veloKopie2;

	veloKopie2 = velo;			/* benutze Zuweisungsoperator */

	Fahrzeug::vAusgabeHeader();
	cout << veloKopie << endl << veloKopie2 << endl;
}

void vAufgabe4() {
	Weg weg("Allee", 150.0, Weg::Landstrasse);
	PKW vw("Golf", 110, 6.7, 88);
	Fahrrad velo("Haibike", 22);

	weg.vAnnahme(&vw);
	weg.vAnnahme(&velo, 1.1);

	Fahrzeug::vAusgabeHeader();
	while (dGlobaleZeit < 10) {
		dGlobaleZeit += 0.1;
		weg.vAbfertigung();
		cout << vw << endl << velo << endl << weg << endl;
	}
}

void vAufgabe5() {
	Weg hin("Hinweg", 500.0, Weg::Landstrasse);
	Weg rueck("Rueckweg", 500.0, Weg::Landstrasse);

	PKW vw("Golf", 110, 6.7, 88);
	Fahrrad velo("Haibike", 22);

	bool bStarted = bInitialisiereGrafik(800, 600, true);
	if (!bStarted) {
		cerr << "Konnte Simulationsserver nicht starten!" << endl;
	}

	int iKoordinaten[] = {100, 100, 700, 500 };
	bZeichneStrasse(hin.getName(), rueck.getName(), hin.getLaenge(), 2, iKoordinaten);

	hin.vAnnahme(&vw);
	rueck.vAnnahme(&velo);

	Fahrzeug::vAusgabeHeader();
	while (dGlobaleZeit < 10) {
		dGlobaleZeit += 0.3;
		hin.vAbfertigung();
		rueck.vAbfertigung();

		vSetzeZeit(dGlobaleZeit);

		vw.vZeichnen(&hin);
		velo.vZeichnen(&rueck);

		cout << vw << endl << velo << endl << hin << endl << rueck << endl;

		Sleep(500);
	}

	vBeendeGrafik();
}

void vAufgabe6() {
	Weg weg("Allee", 300.0, Weg::Landstrasse);
	PKW vw("Golf", 110, 6.7, 88);

	weg.vAnnahme(&vw);

	Fahrzeug::vAusgabeHeader();
	while (dGlobaleZeit < 10) {
		dGlobaleZeit += 0.5;
		weg.vAbfertigung();
		cout << vw << endl << weg << endl;
	}
}

void vListeAusgeben(LazyListe<int> tListe) {
		LazyListe<int>::iterator it;
		for (it = tListe.begin(); it != tListe.end(); it++) {
			cout << *it << ", ";
		}
		cout << endl;
}

void vAufgabe6a() {
	LazyListe<int> tListe;
	LazyListe<int>::iterator it;

	/* PRNG mit konstantem seed initialisieren */
	srand(55);

	/* Mit Zufallszahlen füllen */
	cout << "Fülle mit Zufallszahlen" << endl;
	for (int i = 0; i < 10; i++) {
		tListe.push_back(rand() % 10 + 1);
	}

	cout << "Führe LazyAktionen aus" << endl;
	tListe.vAktualisieren();

	cout << "Gebe Liste aus: ";
	vListeAusgeben(tListe);

	cout << "Lösche Werte > 5..." << endl;
	for (it = tListe.begin(); it != tListe.end(); it++) {
		if (*it > 5) {
			tListe.erase(it);
		}
	}

	cout << "Gebe Liste aus: ";
	vListeAusgeben(tListe);

	cout << "Führe LazyAktionen aus" << endl;
	tListe.vAktualisieren();

	cout << "Gebe Liste aus: ";
	vListeAusgeben(tListe);

	cout << "Weitere Änderungen..." << endl;
	tListe.push_front(44);
	tListe.push_back(33);

	cout << "Führe LazyAktionen aus" << endl;
	tListe.vAktualisieren();

	cout << "Gebe Liste aus: ";
	vListeAusgeben(tListe);
}

typedef void (*aufgabe_t)(void);
#define NUM_AUFGABEN 7

int main() {
	int iWahl;

	aufgabe_t pAufgaben[] = {
			&vAufgabe1_deb,
			&vAufgabe1,
			&vAufgabe2,
			&vAufgabe3,
			&vAufgabe4,
			&vAufgabe5,
			&vAufgabe6,
			&vAufgabe6a
	};

	retry:

	cout << "0: vAufgabe1_deb()" << endl;
	cout << "1: vAufgabe1()" << endl;
	cout << "2: vAufgabe2()" << endl;
	cout << "3: vAufgabe3()" << endl;
	cout << "4: vAufgabe4()" << endl;
	cout << "5: vAufgabe5()" << endl;
	cout << "6: vAufgabe6()" << endl;
	cout << "7: vAufgabe6a()" << endl;
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
