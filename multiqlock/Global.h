/**
 * Global.h
 * Globale Variablen und Einstellungen
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    24.9.2011
 */
#ifndef GLOBAL_H
#define GLOBAL_H

#define MQ_VERSION 2.3.1

// ****************************************************************************************************
// Logging Einstellungen
// ****************************************************************************************************

// Debugflag
//#define DEBUG
// Debug separat für diesen Modus
//#define DEBUG_MYDCF77


// ****************************************************************************************************
// EEPROM Einstellungen
// ****************************************************************************************************

// Soll der letzte Modus gespeichert werden und beim Starten der Uhr geladen werden?
//#define SAVEMODE

// EEPROM Identifier
#define EEPROM_IDENTIFIER0 'M'
#define EEPROM_IDENTIFIER1 'Q'

// Adressen um auf den Speicher zuzugreifen
#define EEPROM_ADR_IDENT 0 // Achtung! Hier wird Addresse 0 und 1 verwendet!
#define EEPROM_ADR_BRIGHTNESS_LO 2
#define EEPROM_ADR_BRIGHTNESS_HI 3
#define EEPROM_MODE 4


// ****************************************************************************************************
// Globale Layout Einstellungen (Layout-Unabhängig)
// ****************************************************************************************************

// Hardwarelayout definieren
// siehe: https://groups.google.com/group/qlocktwo/browse_thread/thread/e96f0611e87c237b#
//#define LAYOUT_ORIGINAL
#define LAYOUT_EBERHARD

// Abmessungen der Matrix
#define MATRIX_COLUMNS 11
#define MATRIX_ROWS 10

// Wie soll Uhrzeit angezeigt werden: 
#define DE_DE // DE_DE: ES IST EIN UHR    / ZWANZIG NACH / ZWANZIG VOR
//#define DE_AT // DE_AT: ES IST PUNKT EINS / ZEHN VOR     / FUENF VOR DREIVIERTEL

// Was für eine Anzeige soll verwendet werden?
// VIERTEL VOR oder DREIVIERTEL bzw VIERTEL oder VIERTEL NACH
// Zeile Auskommentieren für VIERTEL VOR
#define DREIVIERTEL_ANZEIGE

// Dieser Schalter stellt die Anzeige auf den Kopf, falls man die Kabel beim Anoden-
// multiplexer nicht kreuzen moechte.
// #define UPSIDE_DOWN

// Falls eine Schaltung mit internen Button Pullups verwendet wird, Zeile einkommentieren, ansonsten auskommentieren
//#define INTERNAL_BUTTON_PULLUP

#if INTERNAL_BUTTON_PULLUP
#define BUTTON_PRESSED LOW
#else
#define BUTTON_PRESSED HIGH
#endif


// ****************************************************************************************************
// Einstellungen nur für das Original Layout
// ****************************************************************************************************

// Wer einen LDR (an A3) installiert hat, kann diese Zeile auskommentieren und hat dann eine von
// der Umgebungshelligkeit abhaengige Helligkeit.
// -> Bei Eberhart wird der LDR immer abgefragt!
#define ENABLE_LDR

// Dieser Schalter erhoeht die Helligkeit, indem er nicht beleuchtete Zeilen ueberspringt. (Tipp
// von Johannes)
// #define SKIP_BLANK_LINES



// ****************************************************************************************************
// Einstellungen nur für das Eberhart Layout
// ****************************************************************************************************

// Das TIMER_DELAY legt die Refresh-Rate des Multiplexers fest
// Höhere Werte (solange die Anzeige nicht flackert) sind besser, da dann die CPU
// mehr Zeit für andere Aufgaben hat!
#define TIMER_DELAY 120

// Bei meinem LDR bekomme ich folgende Werte vom Analog-Eingang
// Volle Helligkeit (Schreibtischlampe direkt über LDR): 250
// Normale Helligkeit (Normale Zimmerbeleuchtung): 560
// Dämmerung: 980
// Dunkelheit: 1020
// Je nach verwendetem LDR (und Bauteiltoleranzen) können diese Werte bei
// jedem anders ausfallen. In diesem Fall einfach im Debug-Mode die Werte anzeigen
// lassen (adjustBrigtness, LDR readout) und die folgenden Konstanten entsprechend
// anpassen.
const uint16_t ldrBrightSample = 20; // Hell
const uint16_t ldrDarkSample = 980; // Dunkel
const float ldrGain = .2f; // "Empfindlichkeit" der Helligkeitsanpassug

#endif

