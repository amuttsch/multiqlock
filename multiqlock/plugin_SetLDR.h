/**
 * plugin_SetLDR.h
 * Helligkeit der QlockThree regulieren
 *
 * @mc       Arduino/RBBB
 * @autor    Eberhard Rensch / Andreas Muttscheller
 * @version  1.0
 * @datum    04.1.2012
 */
#ifndef SETLDR_H
#define SETLDR_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

// Eine globale Initialisierungfunktion
void initSetLDR();

void showSetLDRHi();
void updateSetLDRHi(int timeDiff);
void buttonSetLDRHi(Button btn, byte id);

void showSetLDRLo();
void updateSetLDRLo(int timeDiff);
void buttonSetLDRLo(Button btn, byte id);

#endif

