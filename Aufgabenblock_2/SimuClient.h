/* 
 * SimuClient für MacOS/Linux (Praktikum Informatik 2, WS 2009/10 RWTH Aachen)
 * Version 0.5
 * von Robert Uhl, 2009 - 2010
 * Vielen Dank an den Lehrstuhl EECS, RWTH Aachen, für den Zugang zum Quellcode
 * des SimuClient für Windows.
 * Datei: SimuClient.h
 * Inhalt: SimuClient sendet Daten an den (erweiterten) Java-Grafik-Server
 */

#ifndef SIMUCLIENT_H
#define SIMUCLIENT_H

#include <string>
using namespace std;

/**
 * Grafik-Server initialisieren
 * Standard: bStarteServer = true, sServer = "localhost", iPort = 7654
 */
bool bInitialisiereGrafik(int sizeX, int sizeY, bool bStarteServer = true, const string& sServer = "localhost", const unsigned short iPort = 7654);

/**
 * Zeichnet eine Kreuzung
 */
bool bZeichneKreuzung(int posX, int posY);

/**
 * Straße zeichnen
 */
bool bZeichneStrasse(const string& way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy);

/**
 * PKW zeichnen
 */
bool bZeichnePKW(const string& carname, const string& streetname, double rel_position, double speed, double tank);

/**
 * Zeichne Fahrrad
 */
bool bZeichneFahrrad(const string& bikename, const string& streetname, double relposition, double speed);

/**
 * Sendet die aktuelle Simulationszeit an den erweiterten SimuServer
 */
void vSetzeZeit(const double dTime);

/**
 * Ersetzt die Sleep()-Funktion von Windows, die mSek übernimmt
 */
void Sleep(const int mSec);

/**
 * Grafikserver beenden
 */
void vBeendeGrafik(void);

/*
 * Zusätzliche Schnittstellen wegen eventueller Konvertierungsprobleme bei string/char*
 */

bool bZeichneStrasse(const char* way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy);
bool bZeichneStrasse(const string& way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy);
bool bZeichneStrasse(const char* way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy);

bool bZeichnePKW(const char* carname, const char* streetname, double rel_position, double speed, double tank);
bool bZeichnePKW(const string& carname, const char* streetname, double rel_position, double speed, double tank);
bool bZeichnePKW(const char* carname, const string& streetname, double rel_position, double speed, double tank);

bool bZeichneFahrrad(const char* bikename, const char* streetname, double rel_position, double speed);
bool bZeichneFahrrad(const string& bikename, const char* streetname, double rel_position, double speed);
bool bZeichneFahrrad(const char* bikename, const string& streetname, double rel_position, double speed);

#endif	// SIMUCLIENT_H
