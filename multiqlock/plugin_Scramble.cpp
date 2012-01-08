/**
 * Scramble.cpp
 * LEDs zufällig leuchten lassen
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#include "plugin_Scramble.h"
#include "DisplayMatrix.h"
#include "Global.h"

word tmpMatrix[MATRIX_ROWS];

// Initialisierung
void initScramble()
{  
  return;
}

// Update
void updateScramble(int timeDiff)
{
  for (int i = 0; i < MATRIX_ROWS; i++) 
  {
    tmpMatrix[i] = random(65536);
  }
  
  return;
}
  
// Anzeigefunktion
void showScramble()
{
  clearMatrix();

  for (int i = 0; i < MATRIX_ROWS; i++) 
  {
    setMatrix(i, tmpMatrix[i]);
  }
  
  // Die Matrix auf die LEDs multiplexen
  writeMatrix();
  
  return;
}

void buttonScramble(Button btn, byte id)
{

}
