Zum Starten des Simulationsservers ist zumindest ein Runtimesystem
von Java 2 (JRE) erforderlich. Im CIP-Pool ist das entsprechende JDK installiert 
und der Speicherort des jar-Files bekannt. Das jar-File wird beim
Initialisieren des Servers (bInitialisiereGrafik()) automatisch gestartet.

Möchten Sie den Server zuhause einsetzen, so müssen Sie das jar-File in 
das Projektverzeichnis kopieren und das JRE installiert haben.

Hier gleich die Lösungen zu häufigen Problemen ;-) :

    1) Das JRE ist nicht installiert.
       Um dies zu erkennen, öffnen Sie eine CMD-Eingabeaufforderung und geben dort
       java -Version
       ein. Wenn dies zur Meldung "Unbekannter Befehl" führt oder die Version vor 1.6 liegt:
       -> Laden Sie das JRE vom Serviceportal oder von http://java.sun.com/
       herunter und installieren Sie es.

    2) Ihre Firewall verhindert Kommunikation mit Port 7654.
       Ihr Programm muss mit Ihrem lokalen Rechner (127.0.0.1) Kommunikation
       über Port 7654 aufnehmen können. Bei einigen pers. Firewalls muss dies
       explizit erlaubt werden.

    3) Das Programm findet den jar-File nicht in Ihrem Projektverzeichnis.
       -> Kopieren Sie den jar-File dorthin (Wenn Sie das Programm aus der VS starten, ist es
       das Verzeichnis, wo auch ihre cpp- und h-Dateien liegt).
       Im CIP-Pool wird automatisch der jar-File vom Server (P:\UserGrp\PI2) gestartet.

    4) Sie benutzen die Visual Studio Version 6 oder Visual Studio 2003 / 2005.
       Sie haben die falsche Version der DLL. Bitte benutzen Sie die andere Version der DLL oder 
       Visual Studio 2010 (z.B. vom MSDN AA Portal).

Wenn Punkt 4 das Problem noch nicht löst, wenden Sie sich bitte an die Betreuung
(persönlich, per E-Mail oder Diskussionsgruppe).
