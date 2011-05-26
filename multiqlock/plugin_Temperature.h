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

#include "WProgram.h"
#include "Button.h"

void showTemperature();
void initTemperature(int x, int y);
void updateTemperature(int timeDiff);
void buttonTemperature(Button btn, byte id);

#endif

