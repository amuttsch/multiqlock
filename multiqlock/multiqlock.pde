/**
 * multiqlock.pde
 * Die "Firmware" der Selbsbau-QLOCKTWO.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 *           Andreas Muttscheller
 *           Benedikt Gerlich
 *           Bernhard Göberndorfer
 * @version  2.3.3
 * @datum    07.01.2012
 */
 
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <TimerOne.h>

#include "Button.h"
#include "DisplayMatrix.h"
#include "ClockHandler.h"
#include "PluginLoader.h"
#include "SerialHandler.h"
#include "Global.h"
#include "Pins.h"

// includes für dynamische Plugins wie z.B. Pong etc.

// Um ein Plugin zu aktivieren bzw. deaktivieren, einfach die .h Datei
// und das registerPlugin ein/auskommentieren
#include "plugin_Clock.h"
#include "plugin_Seconds.h"
#include "plugin_Analog.h"
#include "plugin_Scramble.h"
#include "plugin_Blank.h"
#include "plugin_All.h"
#include "plugin_BinaryClock.h"
#include "plugin_Fireworks.h"
#include "plugin_Pong.h"
#include "plugin_Temperature.h"
#ifdef LAYOUT_EBERHARD
  #include "plugin_SetLDR.h"
#endif

Button button1(minusAndMinutePin); // (minutes)
Button button2(plusAndHourPin); // (hours)
Button modeChangeButton(modePin); // Mode

/**
 * Prüfen ob der EEPROM korrekt initialisiert ist. Ggf. initialisieren
 */
void checkEEPROM()
{
   char ident0 = (char)EEPROM.read(EEPROM_ADR_IDENT);
   char ident1 = (char)EEPROM.read(EEPROM_ADR_IDENT+1);
   if(ident0 != EEPROM_IDENTIFIER0 || ident1 != EEPROM_IDENTIFIER1) // EEPROM uninitialisiert!
   {
     // Initialisiere EEPROM mit default Werten
     EEPROM.write(EEPROM_ADR_BRIGHTNESS_LO, 10);
     EEPROM.write(EEPROM_ADR_BRIGHTNESS_HI, 255);    
     EEPROM.write(EEPROM_MODE, 0);  
	 
     EEPROM.write(EEPROM_ADR_IDENT, EEPROM_IDENTIFIER0);
     EEPROM.write(EEPROM_ADR_IDENT+1, EEPROM_IDENTIFIER1);
   }
}
  
/**
 * Initialisierung. setup() wird einmal zu Beginn aufgerufen, wenn der
 * Arduino Strom bekommt.
 */
void setup()
{
  // Debugmodus ggf. starten
  // Serielle Übertragung immer starten, wegen Moduswechsel über den seriellen Eingang
  Serial.begin(57600);
  #ifdef DEBUG
    Serial.print("QlockTwo - Multiqlock v");
    Serial.println(MQ_VERSION);
    Serial.println("nice to speak to you... ");

  #endif
  
  checkEEPROM();
  
  Wire.begin(); // starte Wire library als I2C-Bus Master

  #ifdef LAYOUT_EBERHARD
    SPI.begin();
    SPI.setBitOrder(LSBFIRST);
    //--- Activate the PWM timer
    Timer1.initialize(TIMER_DELAY); // Timer for updating pwm pins
    Timer1.attachInterrupt(iProcess);
  #endif
  
  initClockHandler();
  
  // Plugins anmelden
  registerPlugin(initClock, updateClock, showClock, buttonClock, 500);
  registerPlugin(initSeconds, updateSeconds, showSeconds, buttonSeconds, 250);
  registerPlugin(initAnalog, updateAnalog, showAnalog, buttonAnalog, 1000);
  registerPlugin(initAnalog, updateAnalogSnake, showAnalogSnake, buttonAnalog, 1000);
  registerPlugin(initScramble, updateScramble, showScramble, buttonScramble, 750);
  registerPlugin(initBlank, updateBlank, showBlank, buttonBlank, 1000);
  registerPlugin(initAll, updateAll, showAll, buttonAll, 1000);
  registerPlugin(initBinary, updateBinary, showBinary, buttonBinary, 250);
  registerPlugin(initBinary, updateBinary, showBinary2, buttonBinary, 250);
  registerPlugin(initPong, updatePong, showPong, buttonPong, 275);
  registerPlugin(initFireworks, updateFireworks, showFireworks, buttonFireworks, 275);
  registerPlugin(initTemperature, updateTemperature, showTemperature, buttonTemperature, 1000);
  
  // Helligkeitsanpassung nur beim Layout von Eberhard
  #ifdef LAYOUT_EBERHARD
    registerPlugin(initSetLDR, updateSetLDRLo, showSetLDRLo, buttonSetLDRLo, 250);
    registerPlugin(initSetLDR, updateSetLDRHi, showSetLDRHi, buttonSetLDRHi, 250);
  #endif
  
  // Die Plugins initialisieren
  callPluginInit();
  
  // Die Matrix leeren
  initMatrix();
  
  // ggf. letzen Modus laden
  setCurrentMode(0);
#ifdef SAVEMODE
  setCurrentMode(EEPROM.read(EEPROM_MODE));
#endif

  // Den seriellen Handler initialisieren
  initSerialHandler();
}

/**
 * loop() wird endlos auf alle Ewigkeit vom Microcontroller durchlaufen
 */
void loop()
{  
  boolean serialModeChange = false;
  // hier werden die Module geupdated
  callPluginUpdate(getCurrentMode());
  
  callPluginShow(getCurrentMode());
  
  // Sind Daten auf dem seriellen Bus?
  if (SerialHandlerIsDataAvailable())
    SerialHandlerProcessData();

  // Taste Minuten++ gedrueckt?
  if (button1.pressed()) {  
    callPluginButton(getCurrentMode(), button1, BUTTON1);
  }

  // Taste Stunden++ gedrueckt?
  if (button2.pressed()) {
    callPluginButton(getCurrentMode(), button2, BUTTON2);
  }

  // Taste Moduswechsel gedrueckt?
  if (modeChangeButton.pressed()) {
    // Plugin kann bei Moduswechsel noch Daten sichern (Für Einstellung Hi Lo)
    callPluginButton(getCurrentMode(), modeChangeButton, BUTTONM);
    incCurrentMode();
    
    setUpdateFromRtc(true);
    
    // ggf. Moduswechsel speichern
    #ifdef SAVEMODE
      EEPROM.write(EEPROM_MODE, mode);
    #endif

    // Nach einem Moduswechsel immer das Plugin aktualisieren
    forcePluginUpdate();
    
    serialModeChange = false;
  }
  
  // Uhr updaten
  updateClockHandler();
}

