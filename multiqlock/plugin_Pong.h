/**
 * Pong.h
 * Kleine Klasse zum Anzeigen von Pong.
 *
 * @mc       Arduino/RBBB
 * @autor    Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

// Anzeige jeden Frame
void showPong();

// Aktualisierung je nach Intervall
void updatePong(int timeDiff);

// Initialisieren von Pong
void initPong();

// Button abfragen
void buttonPong(Button btn, byte id);

#endif

