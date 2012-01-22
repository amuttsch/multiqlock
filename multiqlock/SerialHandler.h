/**
 * SerialHandler.h
 * Funktionen um mit dem angeschlossenen Computer zu kommunizieren
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    20.01.2011
 */
#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void initSerialHandler();
boolean SerialHandlerIsDataAvailable();
void SerialHandlerProcessData();

#endif

