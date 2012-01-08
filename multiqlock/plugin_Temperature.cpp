/**
 * pluginTemperature.h
 * Anzeige der akutellen Temperatur
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    12.4.2011
 */
 
#include "plugin_Temperature.h"
#include "DisplayMatrix.h"
#include "outputObjects.h"
#include "Pins.h"

// Hier den Wert des im Spannungsteiler eingebauten Widerstands eintragen
// in Ohm. (Hier 2000Ohm)
#define STWIDERSTAND 2000

int currentTemperature;

// Initialisierung
void initTemperature()
{
  currentTemperature = 0;
  
  pinMode(temperatureInputPin, INPUT);
  
  return;
}

// Update
void updateTemperature(int timeDiff)
{
  // Zunächst die Eingangsspannung lesen
  // analogRead gibt - bis 1023 zurück. Jede Einheit entspricht 4.9mV (0.0049V)
  // Daher mal 4.9 / 1023 rechnen
  double temp = analogRead(temperatureInputPin) * 4.9 / 1023;
  
  // Nun den Widerstand anhand des ohmschen Gesetzes Errechnen
  double ws   = STWIDERSTAND / ((5 / temp) - 1);
 
  // Da der KTY81-122 keinen linearen Widerstand hat, die Temperatur
  // in °K mit dieser Funktion errechnen.
  currentTemperature = -ws*ws*0.000038028 + ws*0.203357327+131.394;
  
  // Von °K in °C umrechnen
  currentTemperature -= 273;
}
  
// Anzeigefunktion
void showTemperature()
{ 
  clearMatrix();
  
  // Temperatur
  for (int i = 0; i < 7; i++) {
    setMatrixOr(1 + i, Seconds_ziffern[currentTemperature / 10][i] << 11);
    setMatrixOr(1 + i, Seconds_ziffern[currentTemperature % 10][i] << 5);
  }
  
  // Gradzeichen
  CORNER_UPPER_RIGHT;
  
  writeMatrix();
  
  return;
}

void buttonTemperature(Button btn, byte id)
{

}

