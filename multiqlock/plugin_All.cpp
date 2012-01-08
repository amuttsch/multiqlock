/**
 * All.cpp
 * Alle LEDs leuchten lassen
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#include "plugin_All.h"
#include "DisplayMatrix.h"
#include "Global.h"

// Initialisierung
void initAll()
{
  return;
}

// Update
void updateAll(int timeDiff)
{
  return;
}
  
// Anzeigefunktion
void showAll()
{ 
  clearMatrix();
  for (int i = 0; i < MATRIX_ROWS; i++) 
  {
    setMatrix(i, 65535);
  }
  writeMatrix();  
  
  return;
}

void buttonAll(Button btn, byte id)
{

}
