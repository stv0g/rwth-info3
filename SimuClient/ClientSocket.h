/* 
 * ClientSocket 0.2
 * (c) Robert Uhl 2009
 * Datei: ClientSocket.h
 * Inhalt: ClientSocket sendet Daten an einen Server
 */

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>


class ClientSocket {
	public:
		// Konstruktor/Destruktor
		ClientSocket(const int iType);											// als Type z.B. SOCK_STREAM für TCP
		~ClientSocket(void);
	
		// Methoden
		bool	Connect(const std::string& sServer, const unsigned short iPort);// auf Server mit Namen/IP sServer verbinden mit Portangabe
		void	Disconnect(void);
		bool	Send(const void* vDaten, ssize_t data_len);
	
	private:
		// Variablen
		const int		p_iType;		// Socket-Type
		int				p_iSocket;		// Socket-Nummer
		bool			p_bVerbunden;	// true = verbunden
};

#endif	// CLIENTSOCKET_H
// eof