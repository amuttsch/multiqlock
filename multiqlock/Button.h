/**
 * Button.h
 * Kleine Klasse zum Entprellen der Tasten.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.0
 * @datum    18.2.2011
 */
#ifndef BUTTON_H
#define BUTTON_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

/**
 * Die Tasten
 */
#define BUTTON1 1
#define BUTTON2 2
#define BUTTONM 3

class Button {
public:
  Button(int pin);

  boolean pressed();

private:
  int _pin;
  unsigned long _lastPressTime;
  boolean _buttonPressed;
};

#endif

