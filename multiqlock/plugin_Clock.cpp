/**
 * Clock.cpp
 * Anzeige der Uhrzeit
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 *           Bernhard Goeberndorfer (DE_AT)
 * @version  2.0
 * @datum    07.01.2012
 */
#include "plugin_Clock.h"
#include "ClockHandler.h"
#include "DisplayMatrix.h"
#include "MyDCF77.h"
#include "Global.h"
#include "outputObjects.h"

byte Clock_hours;
byte Clock_min;
byte Clock_sec;

// Initialisierung der BinärUhr
void initClock()
{
  return;
}

// Update der BinärUhr-Anzeige
void updateClock(int timeDiff)
{
  // Uhrzeit von der RTC ermitteln
  Clock_hours = getHours();
  Clock_min   = getMinutes();
  
  return;
}

void buttonClock(Button btn, byte id)
{
  // Taste Minuten++ gedrueckt?
  if (id == BUTTON1) {  
    incMinutes();
    writeTime();

    setUpdateFromRtc(true);
  }

  // Taste Stunden++ gedrueckt?
  if (id == BUTTON2) {     
    incHours();
    writeTime();
    setUpdateFromRtc(true);
  }
}

/**
 * Setzt die vier Punkte in den Ecken, je nach minutes % 5 (Rest)
 */
void setClockMinutes(int minutes) {
  switch (minutes % 5) {
  case 0:
    break;
  case 1:
    CORNER_UPPER_LEFT;
    break;
  case 2:
    CORNER_UPPER_LEFT;
    CORNER_UPPER_RIGHT;
    break;
  case 3:
    CORNER_UPPER_LEFT;
    CORNER_UPPER_RIGHT;
    CORNER_LOWER_RIGHT;
    break;
  case 4:
    CORNER_UPPER_LEFT;
    CORNER_UPPER_RIGHT;
    CORNER_LOWER_RIGHT;
    CORNER_LOWER_LEFT;
    break;
  }
}

/**
 * Setzt die Stunden, je nach hours. 'glatt' bedeutet,
 * es ist genau diese Stunde und wir muessen 'UHR'
 * dazuschreiben und EIN statt EINS, falls es 1 ist.
 */
void setHoures(int hours, boolean glatt) {
  while (hours > 12) {
    hours -= 12;
  }

#ifdef DE_DE 
  switch (hours) {
  case 0:
  case 12:
  case 24:
    H_ZWOELF;
    break;
  case 1:
  case 13:
    if (glatt) {
      H_EIN;
    } 
    else {
      H_EINS;
    }
    break;
  case 2:
  case 14:
    H_ZWEI;
    break;
  case 3:
  case 15:
    H_DREI;
    break;
  case 4:
  case 16:
    H_VIER;
    break;
  case 5:
  case 17:
    H_FUENF;
    break;
  case 6:
  case 18:
    H_SECHS;
    break;
  case 7:
  case 19:
    H_SIEBEN;
    break;
  case 8:
  case 20:
    H_ACHT;
    break;
  case 9:
  case 21:
    H_NEUN;
    break;
  case 10:
  case 22:
    H_ZEHN;
    break;
  case 11:
  case 23:
    H_ELF;
    break;
  }

#endif
#ifdef DE_AT
  switch (hours) {
  case 0:
  case 12:
  case 24:
    H_ZWOELF;
    break;
  case 1:
  case 13:
    H_EINS;
    break;
  case 2:
  case 14:
    H_ZWEI;
    break;
  case 3:
  case 15:
    H_DREI;
    break;
  case 4:
  case 16:
    H_VIER;
    break;
  case 5:
  case 17:
    H_FUENF;
    break;
  case 6:
  case 18:
    H_SECHS;
    break;
  case 7:
  case 19:
    H_SIEBEN;
    break;
  case 8:
  case 20:
    H_ACHT;
    break;
  case 9:
  case 21:
    H_NEUN;
    break;
  case 10:
  case 22:
    H_ZEHN;
    break;
  case 11:
  case 23:
    H_ELF;
    break;
  }
#endif

}

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setWords(int hours, int minutes) {
  while (hours > 12) {
    hours -= 12;
  }



#ifdef DE_DE
  ESIST;
  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    // VIER UHR
    UHR;
    setHoures(hours, true);
    break;
  case 1:
    // 5 nach
    FUENF;
    NACH;
    setHoures(hours, false);
    break;
  case 2:
    // 10 nach
    ZEHN;
    NACH;
    setHoures(hours, false);
    break;
  case 3:
    // viertel nach
    VIERTEL;
    #ifndef DREIVIERTEL_ANZEIGE
      // *** VIERTEL NACH DREI
      NACH;
      setHoures(hours, false);
    #else 
      // *** VIERTEL VIER
      setHoures(hours + 1, false);
    #endif
    break;
  case 4:
    // 20 nach
    // *** ZANZIG NACH DREI
    ZWANZIG;
    NACH;
    setHoures(hours, false);
    break;
  case 5:
    // 5 vor halb
    FUENF;
    VOR;
    HALB;
    setHoures(hours + 1, false);
    break;
  case 6:
    // halb
    HALB;
    setHoures(hours + 1, false);
    break;
  case 7:
    // 5 nach halb
    FUENF;
    NACH;
    HALB;
    setHoures(hours + 1, false);
    break;
  case 8:
    // 20 vor
    // *** ZWANZIG VOR VIER
    ZWANZIG;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 9:
    // viertel vor bzw. dreiviertel
    #ifdef DREIVIERTEL_ANZEIGE
      // *** DREIVIERTEL VIER
      DREIVIERTEL_ANZEIGE;
    #else
      // *** VIERTEL VOR VIER
      VIERTEL;
      VOR;
    #endif
    setHoures(hours + 1, false);
    break;
  case 10:
    // 10 vor
    ZEHN;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 11:
    // 5 vor
    FUENF;
    VOR;
    setHoures(hours + 1, false);
    break;
  }
  
#endif
#ifdef DE_AT
  ESIST;
  
  switch (minutes / 5) {
  case 0:
    // glatte Stunde
    // *** PUNKT VIER
    PUNKT;
    setHoures(hours, true);
    break;
  case 1:
    // 5 nach
    FUENF;
    NACH;
    setHoures(hours, false);
    break;
  case 2:
    // 10 nach
    ZEHN;
    NACH;
    setHoures(hours, false);
    break;
  case 3:
    // viertel nach
    VIERTEL;
    #ifndef DREIVIERTEL_ANZEIGE
      // *** VIERTEL NACH DREI
      NACH;
      setHoures(hours, false);
    #else 
      // *** VIERTEL VIER
      setHoures(hours + 1, false);
    #endif
    break;
  case 4:
    // 20 nach
    // *** ZEHN VOR HALB VIER
    ZEHN;
    VOR;
    HALB;
    setHoures(hours + 1, false);
    break;
  case 5:
    // 5 vor halb
    FUENF;
    VOR;
    HALB;
    setHoures(hours + 1, false);
    break;
  case 6:
    // halb
    HALB;
    setHoures(hours + 1, false);
    break;
  case 7:
    // 5 nach halb
    FUENF;
    NACH;
    HALB;
    setHoures(hours + 1, false);
    break;
  case 8:
    // 20 vor
    // *** FUENF VOR DREIVIERTEL VIER
    FUENF;
    VOR;
    DREIVIERTEL_ANZEIGE;
    setHoures(hours + 1, false);
    break;
  case 9:
    // viertel vor bzw. dreiviertel
    #ifdef DREIVIERTEL_ANZEIGE
      // *** DREIVIERTEL VIER
      DREIVIERTEL_ANZEIGE;
    #else
      // *** VIERTEL VOR VIER
      VIERTEL;
      VOR;
    #endif
    setHoures(hours + 1, false);
    break;
  case 10:
    // 10 vor
    ZEHN;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 11:
    // 5 vor
    FUENF;
    VOR;
    setHoures(hours + 1, false);
    break;
  }
#endif
}
  
// Anzeigefunktion der BinärUhr
void showClock()
{  
  clearMatrix();
  
  setWords(Clock_hours, Clock_min);
  setClockMinutes(Clock_min);
  
  writeMatrix();

  return;
}

