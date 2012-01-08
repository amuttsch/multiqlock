/**
 * pluginLoader.cpp
 * Funktionen für den Aufruf einzelner Plugins
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    21.3.2011
 */

#include "PluginLoader.h"
#include "Global.h"

// Functionpointer für die pluginVerwaltung
typedef struct s_pluginPointer
{
  void (*initPtr)();
  void (*updatePtr)(int timeDiff);
  void (*showPtr)();
  void (*buttonPtr)(Button btn, byte id);
  int updateInterval;
};

// Anzahl registriete Plugins
int pluginCount = 0;
s_pluginPointer *pluginPointer;

// Variablen für FramerateErtmittlung
int lastMillis = 0;

// Soll ein Update erzwungen werden?
boolean forceUpdate;

/***
 * Pluginverwaltung
 * Hier sind die Funktionen, die für das Registrieren und Ausführen der der Plugins notwendig sind
 */
void registerPlugin(void (*x_initPtr)(), void (*x_updatePtr)(int timeDiff), void (*x_showPtr)(), void (*x_buttonPtr)(Button btn, byte id), int x_updateInterval)
{
  pluginPointer = (s_pluginPointer *) realloc(pluginPointer, (pluginCount + 1) * sizeof(s_pluginPointer));
  pluginPointer[pluginCount].initPtr   = x_initPtr;
  pluginPointer[pluginCount].updatePtr = x_updatePtr;
  pluginPointer[pluginCount].showPtr   = x_showPtr;
  pluginPointer[pluginCount].buttonPtr = x_buttonPtr;
  
  pluginPointer[pluginCount].updateInterval = x_updateInterval;
  
  pluginCount++;
  
  return;
}

void callPluginInit()
{
  int i = 0;
  for (i=0;i<pluginCount;i++)
  {
    pluginPointer[i].initPtr();
  }
  
  lastMillis = 0;
  forceUpdate = false;
  
  return;
}

void callPluginUpdate(int mode)
{
  // Get the FrameRate
  int currentMillis = millis();
  if (currentMillis - lastMillis > pluginPointer[mode].updateInterval || forceUpdate)
  {
    pluginPointer[mode].updatePtr(currentMillis-lastMillis);
    lastMillis  = currentMillis;
    forceUpdate = false;
  }
  return;
}

void callPluginShow(int mode)
{
  return pluginPointer[mode].showPtr();
}

void callPluginButton(int mode, Button btn, byte id)
{
    return pluginPointer[mode].buttonPtr(btn, id);
}

int getPluginCount()
{
  return pluginCount;
}

void forcePluginUpdate()
{
  forceUpdate = true;
}
