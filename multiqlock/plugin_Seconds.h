/**
 * Seconds.cpp
 * Anzeige des Sekundenanteils der Uhrzeit
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#ifndef SECONDS_H
#define SECONDS_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void showSeconds();
void initSeconds();
void updateSeconds(int timeDiff);
void buttonSeconds(Button btn, byte id);

#endif

