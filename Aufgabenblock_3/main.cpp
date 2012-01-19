#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "../TinyXml/tinyxml.h"

#ifdef _WIN32 /* _Win32 is usually defined by compilers targeting 32 or 64 bit Windows systems */
#include <windows.h>
#endif

#include "SimuClient.h"
#include "Welt.h"
#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Weg.h"
#include "LazyListe.h"

using namespace std;

double dGlobaleZeit;

void vAufgabe1(int argc, char *argv[]) {
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
void vAufgabe1_deb(int argc, char *argv[]) {
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

void vAufgabe2(int argc, char *argv[]) {
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

	for (dGlobaleZeit = 0; dGlobaleZeit < 6; dGlobaleZeit += dAbfertigungsIntervall) {
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

void vAufgabe3(int argc, char *argv[]) {
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

void vAufgabe4(int argc, char *argv[]) {
	Weg weg("Allee", 150.0, Weg::Landstrasse);
	PKW vw("Golf", 55, 6.7, 88);
	Fahrrad velo("Haibike", 22);

    weg.vAnnahme(&vw, 1.2);
    weg.vAnnahme(&velo);

	Fahrzeug::vAusgabeHeader();
	for (dGlobaleZeit = 0; dGlobaleZeit < 3; dGlobaleZeit += 0.1) {
		weg.vAbfertigung();
		cout << vw << endl << velo << endl << weg << endl;
	}
}

void vAufgabe5(int argc, char *argv[]) {
	Weg hin("Hinweg", 500.0, Weg::Landstrasse);
	Weg rueck("Rueckweg", 500.0, Weg::Landstrasse);

	hin.setRueckweg(&rueck);
	rueck.setRueckweg(&hin);

	PKW vw("Golf", 55, 10, 20);
	Fahrrad velo("Haibike", 22);

	bool bStarted = bInitialisiereGrafik(800, 600);
	if (!bStarted) {
		cerr << "Konnte Simulationsserver nicht starten!" << endl;
	}

	Koordinaten iPoly[] = {{100, 100}, {700, 500} };
	hin.vZeichnen(2, iPoly);

    hin.vAnnahme(&vw, 1.2);
    rueck.vAnnahme(&velo);

	Fahrzeug::vAusgabeHeader();
	for (dGlobaleZeit = 0; dGlobaleZeit < 15; dGlobaleZeit += 0.3) {
		hin.vAbfertigung();
		rueck.vAbfertigung();

		vSetzeZeit(dGlobaleZeit);

		hin.vZeichnen();
		rueck.vZeichnen();

		cout << vw << endl << velo << endl << hin << endl << rueck << endl;

		Sleep(500);
	}

	vBeendeGrafik();
}

void vAufgabe6(int argc, char *argv[]) {
	Weg weg("Allee", 300.0, Weg::Landstrasse);
	PKW vw("Golf", 55, 6.7, 88);

	weg.vAnnahme(&vw);

	Fahrzeug::vAusgabeHeader();
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += 0.5) {
		weg.vAbfertigung();
		cout << vw << endl << weg << endl;
	}
}

void vListeAusgeben(LazyListe<int> &tListe) {
		LazyListe<int>::iterator it;
		for (it = tListe.begin(); it != tListe.end(); it++) {
			cout << *it << ", ";
		}
		cout << endl;
}

void vAufgabe6a(int argc, char *argv[]) {
	LazyListe<int> tListe;
	LazyListe<int>::iterator it;

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

void vAufgabe7(int argc, char *argv[]) {
	PKW vw("Golf", 120, 10, 90);
	PKW vw2("Auto", 55, 12, 80);
	Fahrrad velo("Haibike", 42);

	Weg hin("Hinweg", 200.0, Weg::Landstrasse);
	Weg rueck("Rueckweg", 200.0, Weg::Landstrasse);

	hin.setRueckweg(&rueck);
	rueck.setRueckweg(&hin);

	bool bAngenommen = false;
	bool bStarted = bInitialisiereGrafik(800, 600);
	if (!bStarted) {
		cerr << "Konnte Simulationsserver nicht starten!" << endl;
	}

	Koordinaten iPoly[] = {{100, 100}, {700, 500} };
	hin.vZeichnen(2, iPoly);

	hin.vAnnahme(&vw, 4);
	hin.vAnnahme(&velo, 1);

	Fahrzeug::vAusgabeHeader();
	for (dGlobaleZeit = 0; dGlobaleZeit < 9.4; dGlobaleZeit += 0.1) {
		hin.vAbfertigung();

		hin.vZeichnen();
		rueck.vZeichnen();

		if (dGlobaleZeit > 4 && !bAngenommen) {
			hin.vAnnahme(&vw2, dGlobaleZeit + 1);
			bAngenommen = true;
		}

		Fahrzeug::vAusgabeHeader();
		cout << hin << endl << "--" << endl;

		vSetzeZeit(dGlobaleZeit);
		Sleep(100);
	}

	vBeendeGrafik();
}

void vAufgabe8(int argc, char *argv[]) {
	bInitialisiereGrafik(1000, 700);

	PKW vw("Golf", 120, 10, 90);
	PKW ferrari("Ferrari", 120, 15, 210);
	Fahrrad velo("Haibike", 42);

	Kreuzung kr1("K1");
	Kreuzung kr2("K2", 1000);
	Kreuzung kr3("K3");
	Kreuzung kr4("K4");

	kr1.vVerbinde(&kr2, "W12", "W21", 40, Weg::Innerorts, true);
	kr2.vVerbinde(&kr3, "W23a", "W32a", 115, Weg::Autobahn, false);
	kr2.vVerbinde(&kr3, "W23b", "W32b", 40, Weg::Innerorts, true);
	kr2.vVerbinde(&kr4, "W24", "W42", 55, Weg::Innerorts, true);
	kr3.vVerbinde(&kr4, "W34", "W43", 85, Weg::Autobahn, false);
	kr4.vVerbinde(&kr4, "W44a", "W44b", 130, Weg::Landstrasse, false);

	Koordinaten iK1 = {680, 40};
	Koordinaten iK2 = {680, 300};
	Koordinaten iK3 = {680, 570};
	Koordinaten iK4 = {320, 300};

	Koordinaten iW12[]	= {{680, 40}, {680, 300}};
	Koordinaten iW23a[]	= {{680, 300}, {850, 300}, {970, 390}, {970, 500}, {850, 570}, {680, 570}};
	Koordinaten iW23b[]	= {{680, 300}, {680, 570}};
	Koordinaten iW24[]	= {{680, 300}, {320, 300}};
	Koordinaten iW34[]	= {{680, 570}, {500, 570}, {350, 510}, {320, 420}, {320, 300}};
	Koordinaten iW44[]	= {{320, 300}, {320, 150}, {200, 60}, {80, 90}, {70, 250}, {170, 300}, {320, 300}};

	kr1.vZeichnen(iK1);
	kr2.vZeichnen(iK2);
	kr3.vZeichnen(iK3);
	kr4.vZeichnen(iK4);

	bZeichneStrasse("W12", "W21", 40, 2, (int *) iW12);
	bZeichneStrasse("W23a", "W32a", 115, 6, (int *) iW23a);
	bZeichneStrasse("W23b", "W32b", 40, 2, (int *) iW23b);
	bZeichneStrasse("W24", "W42", 55, 2, (int *) iW24);
	bZeichneStrasse("W34", "W43", 85, 5, (int *) iW34);
	bZeichneStrasse("W44a", "W44b", 130, 7, (int *) iW44);

	kr1.vAnnahme(&vw, 1);
	kr1.vAnnahme(&velo, 2);
	kr2.vAnnahme(&ferrari, 3);

	for (dGlobaleZeit = 0.3; dGlobaleZeit <= 24; dGlobaleZeit += 0.01) {
		kr1.vAbfertigung();
		kr2.vAbfertigung();
		kr3.vAbfertigung();
		kr4.vAbfertigung();

		kr1.vZeichnen();
		kr2.vZeichnen();
		kr3.vZeichnen();
		kr4.vZeichnen();

		Fahrzeug::vAusgabeHeader();
		cout
			<< vw << endl
			<< velo << endl
			<< ferrari << endl
			<< kr1 << endl
			<< kr2 << endl
			<< kr3 << endl
			<< kr4 << endl
			<< "--" << endl;

		vSetzeZeit(dGlobaleZeit);
		Sleep(40);
	}

	vBeendeGrafik();
}

void vAufgabe9(int argc, char *argv[]) {
	ifstream File;

	if (argc <= 1) {
		throw string("Geben sie eine Datei als 1. Parameter an!");
	}

	File.open(argv[1]);
	if(!File.good()) {
		throw string("Datei existiert nicht!");
	}

	PKW pkw;
	Fahrrad rad;
	Kreuzung krz;

	File >> pkw >> rad >> krz;

	Fahrzeug::vAusgabeHeader();
	cout << pkw << endl << rad << endl << krz << endl;

	/* Teste map */
	string sName;
	cout << "Geben Sie einen Namen zum Suchen ein: ";
	cin >> sName;
	cout << *AktivesVO::pObjekt(sName) << endl;

	cout << endl;
	cout << "Geben Sie einen Namen zum Erstellen ein: ";
	cin >> sName;
	PKW pkw2(sName, 99);
}

void vAufgabe9a(int argc, char *argv[]) {
	ifstream File;

	if (argc <= 1) {
		throw string("Geben sie eine Datei als 1. Parameter an!");
	}

	File.open(argv[1]);
	if(!File.good()) {
		throw string("Datei existiert nicht!");
	}

	bInitialisiereGrafik(1000, 1000);

	Welt tErde;
	tErde.vEinlesenMitGrafik(File);

	double dInterval = 5.0/60; /* in Stunden */
	double dRatio = 500;

	for (dGlobaleZeit = 0; dGlobaleZeit < 24; dGlobaleZeit += dInterval) {
		tErde.vAbfertigung();
		tErde.vZeichnen();

		//Fahrzeug::vAusgabeHeader();
		//cout << tErde << "--" << endl;

		vSetzeZeit(dGlobaleZeit);
		Sleep(60*60 * dInterval * 1000 / dRatio); /* in ms */
	}

	vBeendeGrafik();
}

typedef void (*aufgabe_t)(int argc, char *argv[]);
#define NUM_AUFGABEN 11

int main(int argc, char *argv[]) {
	/* PRNG mit konstantem seed initialisieren */
	srand(55);

	vAufgabe9a(argc, argv);
	return 0; /* skip the rest */

	int iWahl;

	aufgabe_t pAufgaben[] = {
			&vAufgabe1_deb, &vAufgabe1, &vAufgabe2, &vAufgabe3, &vAufgabe4,
			&vAufgabe5, &vAufgabe6, &vAufgabe6a, &vAufgabe7, &vAufgabe8,
			&vAufgabe9, &vAufgabe9a
	};

	retry:

	cout
		<< "0: vAufgabe1_deb()" << endl
		<< "1: vAufgabe1()" << endl
		<< "2: vAufgabe2()" << endl
		<< "3: vAufgabe3()" << endl
		<< "4: vAufgabe4()" << endl
		<< "5: vAufgabe5()" << endl
		<< "6: vAufgabe6()" << endl
		<< "7: vAufgabe6a()" << endl
		<< "8: vAufgabe7()" << endl
		<< "9: vAufgabe8()" << endl
		<< "10: vAufgabe9()" << endl
		<< "11: vAufgabe9a()" << endl
		<< "Bitte wähen Sie eine Aufgabe: ";
	cin >> iWahl;
	cout << endl;

	if (iWahl > NUM_AUFGABEN || iWahl < 0) {
		cerr << "Ungültige Eingabe! Bitte versuchen Sie es erneut" << endl;
		goto retry;
	}

    dGlobaleZeit = 0; /* resette globale Uhr */

    try {
    	pAufgaben[iWahl](argc, argv); /* Funktionspointer aufrufen */
    }
    catch (string &exception) {
    	cerr << "EXCEPTION: " << exception << endl;
    	exit(-1);
    }

	cout << endl << endl << "Nochmal? (0/1): ";
	cin >> iWahl;
	cout << endl;

	if (iWahl) {
		goto retry;
	}

	return 0;
}
