/**
 * Clockthree.pde
 * Die "Firmware" der Selbsbau-QLOCKTWO.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 *           Andreas Muttscheller
 *           Benedikt Gerlich
 * @version  2.0
 * @datum    21.3.2011
 *
 * TO-DOs:
 * - Die Helligkeitsabhaengige Steuerung implementieren (Lesen von brightnessInputPin,
 *   PWM auf outputEnablePin oder Taktverhaeltnis in writeMatrix() ganz unten aendern)
 * - ganzes Datum vom DCF77 in DS1307 schreiben, ausgabe von 'Specials' an bestimmten
 *   Datumswerten (Geburtstag etc.)
 * - 74HC595-Register ueber die schnellen ASM-Befehle ansprechen
 *   Siehe: http://www.instructables.com/id/Arduino-is-Slow-and-how-to-fix-it/
 *   Siehe: http://arduino.cc/en/Hacking/PinMapping168
 * - DCF77 von Text auf reine Zahlen umstellen, das sollte schneller werden (Flackern
 *   nach dem Minutenwechsel sichtbar bei der Anzeige der Sekunden)
 *
 * Versionshistorie:
 * V 1.1:  - DCF77 auf reine Zeit ohne Strings umgestellt.
 *         - Ganzes Datum wird in die DS1307 geschrieben.
 * V 1.2:  - Schnelles Schreiben der Shift-Register eingefuehrt.
 * V 1.3:  - Auf eigene DCF77-Bibliothek umgestellt (MyDCF77) und DCF77Helper verbessert.
 * V 1.4:  - Glimmen/Nachleuchten dank Tipp von Volker beseitigt (http://www.mikrocontroller.net/topic/209988).
 *         - Erneute Fehlerbereinigung in der DCF77-Bibliothek.
 * V 1.5:  - Die Helligkeit laesst sich ueber die Variable 'brightness' einstellen (Bereich 1-9) bzw.
 *           ueber den Compiler-Schalter 'ENABLE_LDR' einschalten.
 * V 1.6:  - Fehler in der DCF77Helper-Bibliothek behoben.
 * V 2.0:  - Komplette Umstrukturierung des Programms auf Modulbasis
 * V 2.1:  - Weitere Auslagerungen in Headerdateien; Temperatursensor; Updateintervall pro Plugin einstellbar:
 *           Nur gefüllte Zeilen schreiben; Letzten Modus in EEPROM schreiben (define SAVEMODE)
 */

#include <Wire.h>
#include <EEPROM.h>

#include "Button.h"
#include "DisplayMatrix.h"
#include "ClockHandler.h"
#include "PluginLoader.h"

// includes für dynamische Plugins wie z.B. Pong etc.

// Um ein Plugin zu aktivieren bzw. deaktivieren, einfach die .h Datei
// und das registerPlugin ein/auskommentieren
#include "plugin_Clock.h"
#include "plugin_Seconds.h"
#include "plugin_Scramble.h"
#include "plugin_Blank.h"
#include "plugin_All.h"
#include "plugin_BinaryClock.h"
#include "plugin_Fireworks.h"
#include "plugin_Pong.h"
//#include "plugin_Temperature.h"

//#define DEBUG
#define SAVEMODE

// Abmessungen der Matrix
#define XWIDTH 11
#define XHEIGHT 10

#define MODEADDRESS 0

Button button1(5); // (minutes)
Button button2(6); // (hours)
Button modeChangeButton(7);

int mode = 0;
  
/**
 * Initialisierung. setup() wird einmal zu Beginn aufgerufen, wenn der
 * Arduino Strom bekommt.
 */
void setup() {
#ifdef DEBUG
  Serial.begin(57600);
  Serial.println("Starting in debug-mode...");
#endif
  
  initClockHandler();
  
  // Plugins anmelden
  registerPlugin(initClock, updateClock, showClock, buttonClock, 500);
  registerPlugin(initSeconds, updateSeconds, showSeconds, buttonSeconds, 250);
  registerPlugin(initScramble, updateScramble, showScramble, buttonScramble, 750);
  registerPlugin(initBlank, updateBlank, showBlank, buttonBlank, 1000);
  registerPlugin(initAll, updateAll, showAll, buttonAll, 1000);
  registerPlugin(initBinary, updateBinary, showBinary, buttonBinary, 250);
  registerPlugin(initBinary, updateBinary, showBinary2, buttonBinary, 250);
  registerPlugin(initPong, updatePong, showPong, buttonPong, 275);
  registerPlugin(initFireworks, updateFireworks, showFireworks, buttonFireworks, 275);
  //registerPlugin(initTemperature, updateTemperature, showTemperature, buttonTemperature, 1000);
  
  // Die Plugins initialisieren
  callPluginInit(XWIDTH, XHEIGHT);
  
  // Die Matrix leeren
  initMatrix(XWIDTH, XHEIGHT);
  
  // ggf. letzen Modus laden
#ifdef SAVEMODE
  mode = EEPROM.read(MODEADDRESS);
#endif

  if(mode >= getPluginCount()) {
      mode = 0;
  }
}

/**
 * lopp() wird endlos auf alle Ewigkeit vom Microcontroller durchlaufen
 */
void loop()
{  
  // hier werden die Module geupdated
  callPluginUpdate(mode);
  
  callPluginShow(mode);

  // Taste Minuten++ gedrueckt?
  if (button1.pressed()) {  
    callPluginButton(mode, button1, BUTTON1);
  }

  // Taste Stunden++ gedrueckt?
  if (button2.pressed()) {
    callPluginButton(mode, button2, BUTTON2);
  }

  // Taste Moduswechsel gedrueckt?
  if (modeChangeButton.pressed()) {
    mode++;   
    if(mode >= getPluginCount()) {
      mode = 0;
    }
    setUpdateFromRtc(true);
    // ggf. Moduswechsel speichern
#ifdef SAVEMODE
    EEPROM.write(MODEADDRESS, mode);
#endif
  }
  
  // Uhr updaten
  updateClockHandler();
}
