/**
 * ClockHandler.cpp
 * Datei um die Uhrzeiten zu Handeln
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    20.3.2011
 */

#include "SerialHandler.h"
#include "Global.h"
#include "Button.h"
#include "ClockHandler.h"
#include "PluginLoader.h"
#include "Pins.h"
#include "DisplayMatrix.h"

/*
 *  Initialisierung der Funktion
 */
void initSerialHandler()
{
}

// Prüfen Daten zur Verarbeitung anstehen
boolean SerialHandlerIsDataAvailable()
{
  if (Serial.available() > 0)
    return true;
  else
    return false;
}

// @TODO Die auszugebenden Strings optimieren, hier wird 1KB Speicher verschwendet
// Tipp: sprintf nutzen! Dann wird nur eine Überladung von Serial.print mit kompiliert
void SerialHandlerProcessData()
{
  // read the incoming byte:
  char incomingChar = Serial.read();
  Button tmpButton(-1);

  if (incomingChar == 'm')
  {
    Serial.println("Mode changed");
    incCurrentMode();
    forceLDRupdate();
  }
  else if (incomingChar == '+' || incomingChar == '1')
  {
    Serial.println("Button + pressed");
    callPluginButton(getCurrentMode(), tmpButton, BUTTON1);
  }
  else if (incomingChar == '-' || incomingChar == '2')
  {
    Serial.println("Button - pressed");
    callPluginButton(getCurrentMode(), tmpButton, BUTTON2);
  }
  else if (incomingChar == 't')
  {
    Serial.print("My current time: ");
    Serial.print(getHours());
    Serial.print(":");
    Serial.print(getMinutes());
    Serial.print(":");
    Serial.println(getSeconds());
  }
  else if (incomingChar == 's')
  {
    Serial.print("Last sync with DCF77: ");
    Serial.println(getLastSync());
  }
  else
  { 
    Serial.print("'");
    Serial.print(incomingChar);
    Serial.println("' is no command");
    
    // Hier gibt es Probleme, dass die Uhr nicht mehr läuft.
    // Anscheinend passiert dies, wenn zu viele (zu lange?) Serial.print ausgeführt werden 
    
    //Serial.println("Known commands:");
    //Serial.println("-------------------------------");
    //Serial.println("m    change [m]ode");
    //Serial.println("t    display current [t]ime");
    //Serial.println("s    display time of last [s]ync with dcf77. (since poweron)");
    //Serial.println("+,1  emulate press of button[1] (minute++)");
    //Serial.println("-,2  emulate press of button[2] (hour++)");
    //Serial.println("-------------------------------");
  }
}

