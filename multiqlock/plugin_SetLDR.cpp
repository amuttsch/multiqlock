/**
 * plugin_SetLDR.cpp
 * Helligkeit der QlockThree regulieren
 *
 * @mc       Arduino/RBBB
 * @autor    Eberhard Rensch / Andreas Muttscheller
 * @version  1.0
 * @datum    04.1.2012
 */
#include <EEPROM.h>
#include "plugin_SetLDR.h"
#include "DisplayMatrix.h"
#include "Global.h"
#include "outputObjects.h"

boolean saveChangedValue;

void saveBrightness(int mode)
{
  if (saveChangedValue)
  {
    if (mode == 0)
    {
      EEPROM.write(EEPROM_ADR_BRIGHTNESS_LO, getBrightnessLo());
    }
    else
    {
      EEPROM.write(EEPROM_ADR_BRIGHTNESS_HI, getBrightnessHi());
    }
    saveChangedValue = false;
  }
}

// Initialisierung
void initSetLDR()
{
  saveChangedValue = false;
  return;
}

// Update
void updateSetLDRHi(int timeDiff)
{
  return;
}
  
// Anzeigefunktion
void showSetLDRHi()
{ 
  clearMatrix();
  for (int i = 0; i < MATRIX_ROWS; i++) 
  {
    setMatrix(i, hiLo[1][i]); // Anzeige HI/LO getauscht-demnach Anzeige LO! 21.07.11
  }
  
  // Die einzustellende Helligkeit anzeigen
  overrideBrightness(getBrightnessHi());
  writeMatrix();  
  
  return;
}

void buttonSetLDRHi(Button btn, byte id)
{
  // Beim Moduswechsel ggf. die Helligkeit sichern
  if (id == BUTTONM)
  {
    saveBrightness(1);
    // Neuen Helligkeitswert vom LDR anfordern
    forceLDRupdate();
  }
  // Helligkeit ändern
  if (id == BUTTON1)
  {
    if (getBrightnessHi() < 255)
    {
      setBrightnessHi(getBrightnessHi() + 1);
      saveChangedValue = true;
    }
  }
  if (id == BUTTON2)
  {
    if (getBrightnessHi() > getBrightnessLo())
    {
      setBrightnessHi(getBrightnessHi() - 1);
      saveChangedValue = true;
    }
  }
  #ifdef DEBUG
  Serial.print("BrightnessHi: ");
  Serial.println(getBrightnessHi());
  #endif
}

// Update
void updateSetLDRLo(int timeDiff)
{
  return;
}
  
// Anzeigefunktion
void showSetLDRLo()
{ 
  clearMatrix();
  for (int i = 0; i < MATRIX_ROWS; i++) 
  {
    setMatrix(i, hiLo[0][i]); // Anzeige HI/LO getauscht-demnach Anzeige HI! 21.07.11
  }
  
  // Die einzustellende Helligkeit anzeigen
  overrideBrightness(getBrightnessLo());
  writeMatrix();
  
  return;
}

void buttonSetLDRLo(Button btn, byte id)
{
    // Beim Moduswechsel ggf. die Helligkeit sichern
  if (id == BUTTONM)
  {
    saveBrightness(0);
    // Neuen Helligkeitswert vom LDR anfordern
    forceLDRupdate();
  }
  // Helligkeit ändern
  if (id == BUTTON1)
  {
    if (getBrightnessLo() < getBrightnessHi())
    {
      setBrightnessLo(getBrightnessLo() + 1);
      saveChangedValue = true;
    }
  }
  if (id == BUTTON2)
  {
    if (getBrightnessLo() > 0)
    {
      setBrightnessLo(getBrightnessLo() - 1);
      saveChangedValue = true;
    }
  }
  #ifdef DEBUG
  Serial.print("BrightnessLo: ");
  Serial.println(getBrightnessLo());
  #endif
}
