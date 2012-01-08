/**
 * Blank.cpp
 * Leeren Bildschirm ausgeben
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#include "plugin_Blank.h"
#include "DisplayMatrix.h"
#include "Global.h"

// Initialisierung
void initBlank()
{
  return;
}

// Update
void updateBlank(int timeDiff)
{
  return;
}
  
// Anzeigefunktion
void showBlank()
{  
  clearMatrix();
  writeMatrix();
  
  return;
}

void buttonBlank(Button btn, byte id)
{

}
