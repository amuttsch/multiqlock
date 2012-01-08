/**
 * Scramble.cpp
 * LEDs zuf�llig leuchten lassen
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#ifndef SCRAMBLE_H
#define SCRAMBLE_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void showScramble();
void initScramble();
void updateScramble(int timeDiff);
void buttonScramble(Button btn, byte id);

#endif

