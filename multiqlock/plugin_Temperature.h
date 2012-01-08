/**
 * pluginTemperature.h
 * Anzeige der akutellen Temperatur
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    12.4.2011
 */
#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void showTemperature();
void initTemperature();
void updateTemperature(int timeDiff);
void buttonTemperature(Button btn, byte id);

#endif

