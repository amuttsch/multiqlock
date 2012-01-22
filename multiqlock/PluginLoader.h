/**
 * pluginLoader.h
 * Funktionen f�r den Aufruf einzelner Plugins
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    21.3.2011
 */
#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void registerPlugin(void (*x_initPtr)(), void (*x_updatePtr)(int timeDiff), void (*x_showPtr)(), void (*x_buttonPtr)(Button btn, byte id), int x_updateInterval);
void callPluginInit();
void callPluginUpdate(int mode);
void callPluginShow(int mode);
void callPluginButton(int mode, Button btn, byte id);
int getPluginCount();
void forcePluginUpdate();
void setCurrentMode(int x_mode);
int getCurrentMode();
void incCurrentMode();

#endif

