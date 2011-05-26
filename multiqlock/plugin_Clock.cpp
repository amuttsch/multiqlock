/**
 * Clock.cpp
 * Anzeige der Uhrzeit
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    20.3.2011
 */
#include "plugin_Clock.h"
#include "ClockHandler.h"
#include "DisplayMatrix.h"
#include "MyDCF77.h"
#include "Words.h"

int Clock_matrixX;
int Clock_matrixY;
byte Clock_hours;
byte Clock_min;
byte Clock_sec;

// Initialisierung der BinärUhr
void initClock(int x, int y)
{
  Clock_matrixX = x;
  Clock_matrixY = y;
  
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
    setMatrixOr(1, 0b0000000000010000); // 1
    break;
  case 2:
    setMatrixOr(1, 0b0000000000010000); // 1
    setMatrixOr(0, 0b0000000000001000); // 2
    break;
  case 3:
    setMatrixOr(1, 0b0000000000010000); // 1
    setMatrixOr(0, 0b0000000000001000); // 2
    setMatrixOr(3, 0b0000000000000100); // 3
    break;
  case 4:
    setMatrixOr(1, 0b0000000000010000); // 1  
    setMatrixOr(0, 0b0000000000001000); // 2  
    setMatrixOr(3, 0b0000000000000100); // 3  
    setMatrixOr(2, 0b0000000000000010); // 4 
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

  if (glatt) {
    UHR;
  }

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
}

/**
 * Setzt die Wortminuten, je nach hours/minutes.
 */
void setWords(int hours, int minutes) {
  while (hours > 12) {
    hours -= 12;
  }

  ESIST;

  switch (minutes / 5) {
  case 0:
    // glatte Stunde
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
    NACH;
    setHoures(hours, false);
    break;
  case 4:
    // 20 nach
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
    ZWANZIG;
    VOR;
    setHoures(hours + 1, false);
    break;
  case 9:
    // viertel vor
    VIERTEL;
    VOR;
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

