/* 
 * SimuClient für MacOS/Linux (Praktikum Informatik 2, WS 2009/10 RWTH Aachen)
 * Version 0.5
 * von Robert Uhl, 2009 - 2010
 * Vielen Dank an den Lehrstuhl EECS, RWTH Aachen, für den Zugang zum Quellcode
 * des SimuClient für Windows.
 * Datei: SimuClient.cpp
 * Inhalt: Implementierung des SimuClient für MacOS und Linux
 */

#include "SimuClient.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <cstdlib>
#include "ClientSocket.h"

//#define DEBUG DEBUG		// Debugging an/aus(auskommentieren!)

// Variablen der Bibliothek
static ClientSocket*	p_cGrafikServerVerbindung = NULL;	// Verbindung zum Grafikserver
static string			p_sServer;							// Servername
static unsigned int		p_iPort = 0;						// Serverport
static bool				p_bInitialisiert = false;			// Simulationsdarstellung initialisiert? true = ja
static int				p_iXSize = 0;						// X Größe des Verkehrsplanes
static int				p_iYSize = 0;						// Y Größe des Verkehrsplanes
static map<string, int>	p_mWege;							// Map aller erzeugten Wege; map ermöglicht find()


/*
 *	Hilfsfunktionen
 */

// sendet eine Fehlermeldung an den Server, wenn verbunden.
// Diese wird dort als Error-MsgBox angezeigt.
static void vSendeNachricht(const string& sNachricht) {
	ostringstream ssNachricht;
	
	// noch nicht initialisiert? - muss so bleiben sonst endlose Rekursion !!!
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return;
	}
	
	// Fehlermeldung an den GrafikServer schicken
	ssNachricht << "message " << sNachricht << "#";
	if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
#ifdef DEBUG
		cerr << "Fehlermeldung gesendet: " << ssNachricht.str() << endl;
#endif
		//Sleep(100);
		return;
	} else {
		cerr << "--> Fehler: Senden der Fehlermeldung fehlgeschlagen!" << endl;
		cerr << "Die Fehlermeldung war: " << sNachricht << endl;
		return;
	}
	return;
}

// Prüft ob der Name für eine Straße den Konventionen genügt
static bool bStreetOk(const string& sName, const bool bNeu) {
	if (sName.empty()) {
		cerr << "--> Fehler: Der Wegname ist leer!" << endl;
		vSendeNachricht("Der Wegname ist leer!");
		return false;
	}
	
	if (sName.size() > 10) {
		cerr << "--> Fehler: Der Wegname darf maximal 10 Zeichen lang sein!" << endl;
		vSendeNachricht("Der Wegname darf maximal 10 Zeichen lang sein!");
		return false;
	}
	
	// Nach ungültigen Zeichen im Namen suchen
	if (sName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_-") != string::npos) {
		cerr << "--> Fehler: Der Wegname darf nur Buchstaben, Ziffern, -, _ und keine Leerzeichen enthalten!" << endl;
		vSendeNachricht("Der Wegname darf nur Buchstaben, Ziffern, -, _ und keine Leerzeichen enthalten!");
		return false;
	}
	
	if (bNeu) {		// Weg wird neu angelegt
		if (p_mWege.find(sName) != p_mWege.end()) {
			cerr << "--> Fehler: Der Wegname wurde schon verwendet!" << endl;
			vSendeNachricht("Der Wegname wurde schon verwendet!");
			return false;
		} else {
			p_mWege[sName] = 0;	// Weg in der map speichern
			return true;
		}
	} else {		// Weg wird auf Vorhandensein geprüft
		if (p_mWege.find(sName) != p_mWege.end()) {		// Weg gefunden
			return true;
		} else {
			cerr << "--> Fehler: Der Weg ist nicht vorhanden!" << endl;
			vSendeNachricht("Der Weg ist nicht vorhanden!");
			return false;
		}
	}
}

// Prüft ob der Name für ein Farzeug den Konventionen genügt
static bool bVehikelOk(const string& sName, const double rel_position, const double speed) {
	if (sName.empty()) {
		cerr << "--> Fehler: Fahrzeugname ist leer!" << endl;
		vSendeNachricht("Fahrzeugname ist leer!");
		return false;
	}
	
	if (sName.size() > 10) {
		cerr << "--> Fehler: Der Fahrzeugname darf maximal 10 Zeichen lang sein!" << endl;
		vSendeNachricht("Der Fahrzeugname darf maximal 10 Zeichen lang sein!");
		return false;
	}
	
	// Nach ungültigen Zeichen im Namen suchen
	if (sName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_-") != string::npos) {
		cerr << "--> Fehler: Der Fahrzeugname darf nur Buchstaben, Ziffern, -, _ und keine Leerzeichen enthalten!" << endl;
		vSendeNachricht("Der Fahrzeugname darf nur Buchstaben, Ziffern, -, _ und keine Leerzeichen enthalten!");
		return false;
	}
	
	if (speed < 0.0) {
		cerr << "--> Fehler: Geschwindigkeit < 0.0km/h!" << endl;
		vSendeNachricht("Geschwindigkeit < 0.0km/h!");
		return false;
	}
	
	if (speed > 300.0) {
		cerr << "--> Fehler: Fahrraeder sind keine Formel1-Fahrzeuge, Geschwindigkeit <= 300km/h!" << endl;
		vSendeNachricht("Fahrraeder sind keine Formel1-Fahrzeuge, Geschwindigkeit <= 300km/h!");
		return false;
	}
	
	if ( (rel_position < 0.0) || (rel_position > 1.0) ) {
		cerr << "--> Fehler: Relative Position ausserhalb [0, 1]!" << endl;
		vSendeNachricht("Relative Position ausserhalb [0, 1]!");
		return false;
	}
		
	return true;
}


/*
 *	nutzbare Funktionen
 */

// Grafik-Server initialisieren
// Standard: bStarteServer = true, sServer = "localhost", iPort = 7654
bool bInitialisiereGrafik(int sizeX, int sizeY, bool bStarteServer, const string& sServer, const unsigned short iPort) {
	ostringstream ssNachricht;
	
	// schon initialisiert?
	if (p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer ist schon initialisert!" << endl;
		return false;
	}
	
	// Socket für die Kommunikation zum Server anlegen
	p_cGrafikServerVerbindung = new ClientSocket(SOCK_STREAM);
	p_sServer = sServer;
	p_iPort = iPort;
	
	// Größe des Verkehrsplanes speichern
	p_iXSize = sizeX;
	p_iYSize = sizeY;
	
	// Größe des Verkehrsplanes kontrollieren
	if ( (sizeX < 100) || (sizeX > 2000) || (sizeY < 100) || (sizeY > 2000) ) {
		cerr << "--> Fehler: Groesse des Verkehrsplanes < 100 oder > 2000" << endl;
	}
	
	// Grafik-Server starten
	if (bStarteServer) {
		cout << "--> SimuServer starten ..." << endl;
		system("java -jar SimuServer.jar &");
		Sleep(3 * 1000);	// 3 Sekunden warten
	}
	
	// Verbindung zum Server aufbauen
	if (!p_cGrafikServerVerbindung->Connect(p_sServer, p_iPort)) {
		cerr << "--> Fehler: TCP/IP-Verbindung nicht moeglich!" << endl;
		return false;
	}
	
	// Init-Befehl senden
	ssNachricht << "init " << sizeX << " " << sizeY << "#";
	
	if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
		p_bInitialisiert = true;
#ifdef DEBUG
		cerr << "Init gesendet: " << ssNachricht.str() << endl;
#endif
		Sleep(500);
		return true;
	} else {
		cerr << "--> Fehler: Senden Init fehlgeschlagen!" << endl;
		return false;
	}
}

// Zeichnet eine Kreuzung
bool bZeichneKreuzung(int posX, int posY) {
	ostringstream ssNachricht;
	
	// noch nicht initialisiert?
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return false;
	}
	
	// Kreuzung innerhalb des Verkehrsplanes?
	if ( (posX > 0) && (posX < p_iXSize) && (posY > 0) && (posY < p_iYSize) ) {
		ssNachricht << "crossing " << posX << " " << posY << "#";
		if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
#ifdef DEBUG
			cerr << "Kreuzung gesendet: " << ssNachricht.str() << endl;
#endif
			//Sleep(100);
			return true;
		} else {
			cerr << "--> Fehler: Senden Kreuzung fehlgeschlagen!" << endl;
			vSendeNachricht("Senden Kreuzung fehlgeschlagen!");
			return false;
		}
	} else {
		cerr << "--> Fehler: Koordinaten ausserhalb des Verkehrsplanes!" << endl;
		vSendeNachricht("Koordinaten ausserhalb des Verkehrsplanes!");
		return false;
	}
	return false;
}

// Straße zeichnen
bool bZeichneStrasse(const string& way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy) {
	ostringstream ssNachricht;
	int iCounter;
	
	// noch nicht initialisiert ?
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return false;
	}
	
	// Straßenname ok?
	if (!bStreetOk(way_to_name, true) || !bStreetOk(way_back_name, true)) {
		return false;
	}
	
	if (length < 0) {
		cerr << "--> Fehler: Weglaenge kleiner 0!" << endl;
		vSendeNachricht("Weglaenge kleiner 0!");
		return false;
	}
	
	if (numPoints < 2) {
		cerr << "--> Fehler: Mindestens zwei Koordinaten fuer die Strasse notwendig!" << endl;
		vSendeNachricht("Mindestens zwei Koordinaten fuer die Strasse notwendig!");
		return false;
	}
	
	// Strasse senden
	ssNachricht << "street " << way_to_name << " " << way_back_name << " " << length << " " << numPoints;
	
	for (iCounter = 0; iCounter < numPoints * 2; iCounter += 2) {
		if ( (points_xy[iCounter] > 0) && (points_xy[iCounter] < p_iXSize) && (points_xy[iCounter + 1] > 0) && (points_xy[iCounter + 1] < p_iYSize) ) {
			ssNachricht << " " << points_xy[iCounter] << " " << points_xy[iCounter + 1];
		} else {
			cerr << "--> Fehler: Koordinaten ausserhalb des Verkehrsplanes! Ueberspringe..." << endl;
			//vSendeNachricht("Koordinaten ausserhalb des Verkehrsplanes! Ueberspringe...");
		}
	}
	
	ssNachricht << "#";
	
	if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
#ifdef DEBUG
		cerr << "Strasse gesendet: " << ssNachricht.str() << endl;
#endif
		//Sleep(100);
		return true;
	} else {
		cerr << "--> Fehler: Senden Strasse fehlgeschlagen!" << endl;
		vSendeNachricht("Senden Strasse fehlgeschlagen!");
		return false;
	}	
}

// PKW zeichnen
bool bZeichnePKW(const string& carname, const string& streetname, double rel_position, double speed, double tank) {
	ostringstream ssNachricht;
	
	// noch nicht initialisiert ?
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return false;
	}
	
	// PKW-Name, Position und Geschwindigkeit in den Grenzen?
	if (!bVehikelOk(carname, rel_position, speed)) {
		return false;
	}
	
	if (tank < 0.0) {
		cerr << "--> Fehler: Tank < 0.0l!" << endl;
		vSendeNachricht("Tank < 0.0l!");
		return false;
	}
	
	if (tank > 999.9) {
		cerr << "--> Fehler: Versteckte Tanks sind nicht erlaubt! Tankinhalt < 1000l!" << endl;
		vSendeNachricht("Versteckte Tanks sind nicht erlaubt! Tankinhalt < 1000l!");
		return false;
	}
	
	// Existiert die Straße?
	if (!bStreetOk(streetname, false)) {
		cerr << "--> Fehler: Diese Strasse gibt es nicht!" << endl;
		vSendeNachricht("Diese Strasse gibt es nicht!");
		return false;
	}
	
	ssNachricht << "sc " << carname << " " << streetname << setiosflags(ios::fixed);
	ssNachricht << " " << setw(7) << setprecision(4) << rel_position;
	ssNachricht << " " << setw(6) << setprecision(1) << speed;
	ssNachricht << " " << setw(6) << setprecision(1) << tank << "#";
	
	if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
#ifdef DEBUG
		cerr << "PKW gesendet: " << ssNachricht.str() << endl;
#endif
		//Sleep(100);
		return true;
	} else {
		cerr << "--> Fehler: Senden PKW fehlgeschlagen!" << endl;
		vSendeNachricht("Senden PKW fehlgeschlagen!");
		return false;
	}
}

// Zeichne Fahrrad
bool bZeichneFahrrad(const string& bikename, const string& streetname, double rel_position, double speed) {
	ostringstream ssNachricht;
	
	// noch nicht initialisiert ?
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return false;
	}
	
	// Fahrradname, Position und Geschwindigkeit in den Grenzen?
	if (!bVehikelOk(bikename, rel_position, speed)) {
		return false;
	}
	
	// Existiert die Straße?
	if (!bStreetOk(streetname, false)) {
		cerr << "--> Fehler: Diese Strasse gibt es nicht!" << endl;
		vSendeNachricht("Diese Strasse gibt es nicht!");
		return false;
	}
	
	ssNachricht << "sb " << bikename << " " << streetname << setiosflags(ios::fixed);
	ssNachricht << " " << setw(7) << setprecision(4) << rel_position;
	ssNachricht << " " << setw(6) << setprecision(1) << speed << "#";
	
	if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
#ifdef DEBUG
		cerr << "Fahrrad gesendet: " << ssNachricht.str() << endl;
#endif
		//Sleep(100);
		return true;
	} else {
		cerr << "--> Fehler: Senden Fahrrad fehlgeschlagen!" << endl;
		vSendeNachricht("Senden Fahrrad fehlgeschlagen!");
		return false;
	}
}

// sendet die aktuelle Simulationszeit an den erweiterten SimuServer
// (angepasste Funktion)
void vSetzeZeit(const double dTime) {	
	ostringstream ssNachricht;
#ifdef DEBUG
	cout << dTime << endl;
#endif
	// noch nicht initialisiert ?
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return;
	}
	
	if (dTime < 0.0) {
		cerr << "--> Fehler: Die Zeit darf nicht negativ sein!" << endl;
		vSendeNachricht("Die Zeit darf nicht negativ sein!");
		return;
	}
	
	ssNachricht << "time " << dTime << "#";
	
	if (p_cGrafikServerVerbindung->Send(ssNachricht.str().c_str(), ssNachricht.str().size())) {
#ifdef DEBUG
		cerr << "Zeit gesendet: " << ssNachricht.str() << endl;
#endif
		//Sleep(100);
		return;
	} else {
		cerr << "--> Fehler: Senden der Zeit fehlgeschlagen!" << endl;
		vSendeNachricht("Senden der Zeit fehlgeschlagen!");
		return;
	}
}

// wartet mSec Millisekunden
void Sleep(const int mSec) {
	if (mSec > 0) {
		usleep(mSec * 1000);
	}
	return;
}

// Grafikserver beenden
void vBeendeGrafik(void) {
	// noch nicht initialisiert ?
	if (!p_bInitialisiert) {
		cerr << "--> Fehler: GrafikServer noch nicht initialisert!" << endl;
		return;
	}
	
	vSendeNachricht("Simulation beendet!");
	p_cGrafikServerVerbindung->Send("close#", 6);
#ifdef DEBUG
	cerr << "Close gesendet." << endl;
#endif
	//Sleep(100);
	p_cGrafikServerVerbindung->Disconnect();
	delete p_cGrafikServerVerbindung;
	p_cGrafikServerVerbindung = NULL;
	return;
}

/*
 *	Zusätzliche Schnittstellen wegen eventueller Konvertierungsprobleme bei string/char*
 */

bool bZeichneStrasse(const char* way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy) {
	string sHinweg = string(way_to_name);
	string sRueckweg = string(way_back_name);
	
	return bZeichneStrasse(sHinweg, sRueckweg, length, numPoints, points_xy);
}

bool bZeichneStrasse(const string& way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy) {
	string sRueckweg = string(way_back_name);
	
	return bZeichneStrasse(way_to_name, sRueckweg, length, numPoints, points_xy);
}

bool bZeichneStrasse(const char* way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy) {
	string sHinweg = string(way_to_name);
	
	return bZeichneStrasse(sHinweg, way_back_name, length, numPoints, points_xy);
}

bool bZeichnePKW(const char* carname, const char* streetname, double rel_position, double speed, double tank) {
	string sName = string(carname);
	string sWeg = string(streetname);
	
	return bZeichnePKW(sName, sWeg, rel_position, speed, tank);
}

bool bZeichnePKW(const string& carname, const char* streetname, double rel_position, double speed, double tank) {
	string sWeg = string(streetname);
	
	return bZeichnePKW(carname, sWeg, rel_position, speed, tank);
}

bool bZeichnePKW(const char* carname, const string& streetname, double rel_position, double speed, double tank) {
	string sName = string(carname);
	
	return bZeichnePKW(sName, streetname, rel_position, speed, tank);
}

bool bZeichneFahrrad(const char* bikename, const char* streetname, double rel_position, double speed) {
	string sName = string(bikename);
	string sWeg = string(streetname);
	
	return bZeichneFahrrad(sName, sWeg, rel_position, speed);
}

bool bZeichneFahrrad(const string& bikename, const char* streetname, double rel_position, double speed) {
	string sWeg = string(streetname);
	
	return bZeichneFahrrad(bikename, sWeg, rel_position, speed);
}

bool bZeichneFahrrad(const char* bikename, const string& streetname, double rel_position, double speed) {
	string sName = string(bikename);
	
	return bZeichneFahrrad(sName, streetname, rel_position, speed);
}

// eof
