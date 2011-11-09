/* 
 * ClientSocket 0.2
 * (c) Robert Uhl 2009
 * Datei: ClientSocket.cpp
 * Inhalt: ClientSocket Implementierung
 */

#include "ClientSocket.h"

//#define DEBUG DEBUG		// Debugging an/aus(auskommentieren!)

/*
 *		PUBLIC Methoden
 */

// Konstruktor, der den Typ des Sockets übergeben bekommt
ClientSocket::ClientSocket(const int iType) : p_iType(iType), p_iSocket(-1), p_bVerbunden(false) {
	p_iSocket = socket(AF_INET, p_iType, 0);	// Socket anlegen
	
	if (p_iSocket == -1) {
		std::cerr << "--> Socket konnte nicht angelegt werden!" << std::endl;
	}
}

// Destruktor
ClientSocket::~ClientSocket(void) {
	if (p_bVerbunden) {
		Disconnect();
	}
}

/*
 *		PRIVATE Methoden
 */

// Verbindung zum Server aufnehmen
// Rückgabe:	true wenn Verbindung erfolgreich aufgebaut
bool ClientSocket::Connect(const std::string& sServer, const unsigned short iPort) {
	struct sockaddr_in strAdresse;
	struct in_addr strInAdresse;
	struct hostent* strHost;
	
	if (p_iSocket == -1) {
		std::cerr << "--> Connect(): Socket wurde nicht angelegt!" << std::endl;
		return false;
	}
	
	if (p_bVerbunden) {
		std::cerr << "--> Connect(): Achtung, noch verbunden! Keine neue Verbindung angelegt!" << std::endl;
		return false;
	}
	
	// Domainnamen in IP auflösen
	strHost = gethostbyname(sServer.c_str());
#ifdef DEBUG
	std::cout << "Host: " << strHost->h_name << std::endl;
	std::cout << "IP: " << inet_ntoa( **(struct in_addr**) strHost->h_addr_list) << std::endl;
	std::cout << "Port: " << iPort << std::endl;
#endif
	// IP-Adresse für connect() erzeugen
	strInAdresse = **(struct in_addr**) strHost->h_addr_list;
	strAdresse.sin_family = AF_INET;
	strAdresse.sin_port = htons(iPort);
	strAdresse.sin_addr = strInAdresse;
	
	// Verbindung aufbauen
	if (connect(p_iSocket, (struct sockaddr*) &strAdresse, sizeof(strAdresse)) == -1) {
		std::cerr << "--> connect() nicht erfolgreich!" << std::endl;
		return false;
	} else {
		p_bVerbunden = true;
		return true;
	}
}

// Verbindung zum Server abbauen
void ClientSocket::Disconnect(void) {
	if (close(p_iSocket) == -1) {
		std::cerr << "--> Disconnect(): Konnte die Verbindung nicht schliessen!" << std::endl;
	} else {
		p_bVerbunden = false;
	}
}

// Sendet etwas über das Socket
bool ClientSocket::Send(const void* vDaten, ssize_t data_len) {
	if (p_iSocket == -1) {
		std::cerr << "--> Send(): Socket wurde nicht angelegt!" << std::endl;
		return false;
	} else if (!p_bVerbunden) {
		std::cerr << "--> Send(): Noch keine Verbindung aufgebaut!" << std::endl;
		return false;
	}
	
	// Senden
	if (send(p_iSocket, vDaten, data_len, 0) != data_len) {
		std::cerr << "--> Send(): Es konnte nicht alles gesendet werden!" << std::endl;
		return false;
	}
	
	return true;
}

// eof