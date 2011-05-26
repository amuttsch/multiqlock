  /**
 * Seconds.cpp
 * Anzeige des Sekundenanteils der Uhrzeit
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#include "plugin_Seconds.h"
#include "ClockHandler.h"
#include "DisplayMatrix.h"
#include "Zahlen.h"

int Seconds_matrixX;
int Seconds_matrixY;
byte Seconds_hours;
byte Seconds_min;
byte Seconds_sec;

// Initialisierung der Sekundenuhr
void initSeconds(int x, int y)
{
  Seconds_matrixX = x;
  Seconds_matrixY = y;
  
  return;
}

// Update der Sekundenuhr-Anzeige
void updateSeconds(int timeDiff)
{
  // Uhrzeit von der RTC ermitteln
  Seconds_hours = getHours();
  Seconds_min = getMinutes();
  Seconds_sec = getSeconds();

  return;
}
  
// Anzeigefunktion der Sekundenuhr
void showSeconds()
{  
  clearMatrix();
  for (int i = 0; i < 7; i++) {
    setMatrixOr(1 + i, Seconds_ziffern[Seconds_sec / 10][i] << 11);
    setMatrixOr(1 + i, Seconds_ziffern[Seconds_sec % 10][i] << 5);
  }
  
  // Die Matrix auf die LEDs multiplexen
  writeMatrix();
  
  return;
}

void buttonSeconds(Button btn, byte id)
{

}
