/**
 * Analog.h
 * Zeigt analoge Uhr
 *
 * @mc       Arduino/RBBB
 * @autor    Bernhard Göberndorfer
 * @version  2.0
 * @datum    05.01.2012
 */
#ifndef ANALOG_H
#define ANALOG_H

#include "Button.h"
#include "ClockHandler.h"
#include "DisplayMatrix.h"
#include "Global.h"
#include "outputObjects.h" // Für EckLeds

// Arduino 1.0 oder aelter?
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// Mitte der Zeiger
#define ANALOG_CENTER_X (int)(MATRIX_COLUMNS/2)
#define ANALOG_CENTER_Y (int)(MATRIX_ROWS/2) - 1

// Sekunden als "Snake-Spur" ganz außen anzeigen. 
// Abstand zu außen: (default=0)
#define ANALOG_sMARGIN 0

// Länge der Zeiger für minuten und stunden
#define ANALOG_mLENGTH 5
#define ANALOG_hLENGTH 3 

void writeSnake (int margin, int currentValue, int maxValue);
void showAnalog();
void initAnalog();
void updateAnalog(int timeDiff);
void buttonAnalog(Button btn, byte id);

#endif


