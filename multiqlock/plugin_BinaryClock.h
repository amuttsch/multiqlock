/**
 * BinaryClock.h
 * Anzeige der Uhrzeit in Binär
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#ifndef BINARYCLOCK_H
#define BINARYCLOCK_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void showBinary();
void showBinary2();
void initBinary();
void updateBinary(int timeDiff);
void buttonBinary(Button btn, byte id);

#endif

