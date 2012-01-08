/**
 * Blank.cpp
 * Leeren Bildschirm ausgeben
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#ifndef BLANK_H
#define BLANK_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void showBlank();
void initBlank();
void updateBlank(int timeDiff);
void buttonBlank(Button btn, byte id);

#endif

