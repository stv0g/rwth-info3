#pragma once
#pragma warning (disable:4786)
#include <string>
using namespace std;

// Folgender ifdef-Block ist die Standardmethode zum Erstellen von Makros, die das Exportieren
// aus einer DLL vereinfachen. Alle Dateien in dieser DLL werden mit dem SIMUCLIENT_EXPORTS-Symbol
// kompiliert, das in der Befehlszeile definiert wurde. Das Symbol darf nicht für ein Projekt definiert werden,
// das diese DLL verwendet. Alle anderen Projekte, deren Quelldateien diese Datei beinhalten, erkennen
// SIMUCLIENT_API-Funktionen als aus einer DLL importiert, während die DLL
// mit diesem Makro definierte Symbole als exportiert ansieht.
#ifdef SIMUCLIENT_EXPORTS
#define SIMUCLIENT_API __declspec(dllexport)
#else
#define SIMUCLIENT_API __declspec(dllimport)
#endif

// NUTZBARE FUNKTIONEN (offizielle Schnittstelle)
SIMUCLIENT_API bool bInitialisiereGrafik(int sizeX, int sizeY, char* address = "127.0.0.1");
SIMUCLIENT_API bool bZeichneKreuzung(int posX, int posY);
SIMUCLIENT_API bool bZeichneStrasse(const string& way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy);
SIMUCLIENT_API bool bZeichnePKW(const string& carname, const string& streetname, double rel_position, double speed, double tank);
SIMUCLIENT_API bool bZeichneFahrrad(const string& bikename, const string& streetname, double relposition, double speed);
SIMUCLIENT_API void vBeendeGrafik();
SIMUCLIENT_API void vSetzeZeit(const double dTime);

// Zusätzliche Schnittstellen (wegen Konvertierungsproblemen bei string/char*)

SIMUCLIENT_API bool bZeichneStrasse(const char* way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy);
SIMUCLIENT_API bool bZeichneStrasse(const string& way_to_name, const char* way_back_name, int length, int numPoints, int* points_xy);
SIMUCLIENT_API bool bZeichneStrasse(const char* way_to_name, const string& way_back_name, int length, int numPoints, int* points_xy);
SIMUCLIENT_API bool bZeichnePKW(const string& carname, const char* streetname, double rel_position, double speed, double tank);
SIMUCLIENT_API bool bZeichneFahrrad(const string& bikename, const char* streetname, double rel_position, double speed);
SIMUCLIENT_API bool bZeichnePKW(const char*  carname, const char* streetname, double rel_position, double speed, double tank);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  bikename, const char* streetname, double rel_position, double speed);
SIMUCLIENT_API bool bZeichnePKW(const char*  carname, const string& streetname, double rel_position, double speed, double tank);
SIMUCLIENT_API bool bZeichneFahrrad(const char*  bikename, const string& streetname, double rel_position, double speed);

// Wrapperfunktion fuer Sleep
SIMUCLIENT_API void vSleep(int mSec);