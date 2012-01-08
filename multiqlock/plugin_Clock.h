/**
 * Clock.h
 * Anzeige der Uhrzeit
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    20.3.2011
 */
#ifndef CLOCK_H
#define CLOCK_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void showClock();
void initClock();
void updateClock(int timeDiff);
void buttonClock(Button btn, byte id);

#endif

