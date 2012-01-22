/**
 * Analog.h
 * Zeigt analoge Uhr
 *
 * @mc       Arduino/RBBB
 * @autor    Bernhard Göberndorfer
 * @version  4.0
 * @datum    11.01.2012
 */
#ifndef ANALOG_H
#define ANALOG_H

#include "Button.h"
#include "ClockHandler.h"
#include "DisplayMatrix.h"
#include "Global.h"
#include "outputObjects.h" // definition of CORNER_LEDS
#include "PluginLoader.h" // forcePluginUpdate() 

// Arduino 1.0 or older?
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// center of clock hands
#define ANALOG_CENTER_X (int)(MATRIX_COLUMNS/2)
#define ANALOG_CENTER_Y (int)(MATRIX_ROWS/2) - 1

#define ANALOG_mLENGTH 5
#define ANALOG_hLENGTH 3 

void writeSnake (int margin, int currentValue, int maxValue);
void showAnalog();

void initAnalog();
void updateAnalog(int timeDiff);
void buttonAnalog(Button btn, byte id);

void showAnalogSnake();
void updateAnalogSnake(int timeDiff);

#endif



