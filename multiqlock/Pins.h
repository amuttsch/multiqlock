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
/**
 * Das Rechtecksignal der RTC fuer den Interrupt
 */
#define rtcSQWSignal      2
#define outputEnablePin   3  // Der serielle Ausgang zu den Multiplexern
#define rtcSQWLed         4
#define dcf77Led          8
#define dcf77Signal       9

// Der Temperatursensor
#define temperatureInputPin A0

// Der Helligkeitssensor
#define brightnessInputPin  A3

// Ueber die Wire-Library festgelegt:
// Arduino analog input 4 = I2C SDA
// Arduino analog input 5 = I2C SCL

#endif

