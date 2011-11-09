Zum Starten des Simulationsservers ist zumindest ein Runtimesystem
von Java 2 (JRE) erforderlich. Im CIP-Pool ist das entsprechende JDK installiert 
und der Speicherort des jar-Files bekannt. Das jar-File wird beim
Initialisieren des Servers (bInitialisiereGrafik()) automatisch gestartet.

M�chten Sie den Server zuhause einsetzen, so m�ssen Sie das jar-File in 
das Projektverzeichnis kopieren und das JRE installiert haben.

Hier gleich die L�sungen zu h�ufigen Problemen ;-) :

    1) Das JRE ist nicht installiert.
       Um dies zu erkennen, �ffnen Sie eine CMD-Eingabeaufforderung und geben dort
       java -Version
       ein. Wenn dies zur Meldung "Unbekannter Befehl" f�hrt oder die Version vor 1.6 liegt:
       -> Laden Sie das JRE vom Serviceportal oder von http://java.sun.com/
       herunter und installieren Sie es.

    2) Ihre Firewall verhindert Kommunikation mit Port 7654.
       Ihr Programm muss mit Ihrem lokalen Rechner (127.0.0.1) Kommunikation
       �ber Port 7654 aufnehmen k�nnen. Bei einigen pers. Firewalls muss dies
       explizit erlaubt werden.

    3) Das Programm findet den jar-File nicht in Ihrem Projektverzeichnis.
       -> Kopieren Sie den jar-File dorthin (Wenn Sie das Programm aus der VS starten, ist es
       das Verzeichnis, wo auch ihre cpp- und h-Dateien liegt).
       Im CIP-Pool wird automatisch der jar-File vom Server (P:\UserGrp\PI2) gestartet.

    4) Sie benutzen die Visual Studio Version 6 oder Visual Studio 2003 / 2005.
       Sie haben die falsche Version der DLL. Bitte benutzen Sie die andere Version der DLL oder 
       Visual Studio 2010 (z.B. vom MSDN AA Portal).

Wenn Punkt 4 das Problem noch nicht l�st, wenden Sie sich bitte an die Betreuung
(pers�nlich, per E-Mail oder Diskussionsgruppe).
