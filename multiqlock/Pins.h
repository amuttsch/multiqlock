/**
 * Pins.h
 * Hier sind alle Pins definiert
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    12.4.2011
 */
#ifndef PINS_H
#define PINS_H

#include "Global.h"

/**
 * Das Rechtecksignal der RTC fuer den Interrupt
 */
#define rtcSQWSignal      2
#define outputEnablePin   3  // Der serielle Ausgang zu den Multiplexern
#define rtcSQWLed         4
#define dcf77Led          8
#define dcf77Signal       9

#ifdef LAYOUT_ORIGINAL
  #define PinLatch          11
  #define PinClock          12
  #define PinData           10
#endif

// LAYOUT_EBERHARD
#ifdef LAYOUT_EBERHARD
  #define PinLatch          10
  #define PinClock          13
  #define PinData           11
#endif

// Der Temperatursensor
#define temperatureInputPin A2

// Der Helligkeitssensor
#define brightnessInputPin  A3

// Die Taster
#define minusAndMinutePin 5
#define plusAndHourPin 6
#define modePin 7

// Ueber die Wire-Library festgelegt:
// Arduino analog input 4 = I2C SDA
// Arduino analog input 5 = I2C SCL

#endif

