/**
 * BinaryClock.cpp
 * Anzeige der Uhrzeit in Binär
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller / Benedikt Gerlich
 * @version  1.0
 * @datum    18.3.2011
 */
#include "plugin_BinaryClock.h"
#include "ClockHandler.h"
#include "DisplayMatrix.h"
#include "Global.h"

byte Binary_hours;
byte Binary_min;
byte Binary_sec;

/**
 * Reihenfolge der Bits in einem Byte umkehren
 */
byte swapBits(byte x_input)
{
  byte tmp = x_input;
  int s = sizeof(x_input) * 8 - 1;
  
  for (x_input >>= 1; x_input; x_input >>= 1)
  {   
    tmp <<= 1;
    tmp |= x_input & 1;
    s--;
  }
  tmp <<= s;
  
  return tmp;
}

// Initialisierung der BinärUhr
void initBinary()
{
  return;
}

// Update der BinärUhr-Anzeige
void updateBinary(int timeDiff)
{
  // Uhrzeit von der RTC ermitteln
  Binary_hours = getHours();
  Binary_min = getMinutes();
  Binary_sec = getSeconds();

  return;
}

// Rahmen malen
void paintBoarder()
{
  // Rahmen
  // Oben
  writeLine(0, 0, MATRIX_COLUMNS - 1, 0);
  // Unten
  writeLine(0, MATRIX_ROWS - 1, MATRIX_COLUMNS - 1, MATRIX_ROWS - 1);
  // Links -> Die schon gezeichneten LEDs werden übersprungen
  writeLine(0, 1, 0, MATRIX_ROWS - 2);
  // Rechts -> Die schon gezeichneten LEDs werden übersprungen
  writeLine(MATRIX_COLUMNS - 1, 1, MATRIX_COLUMNS - 1, MATRIX_ROWS - 2);
}

// Anzeigefunktion der BinärUhr Hochformat
void showBinary2()
{  
  // Zeit
  byte tmpBit;
  byte swappedHours1 = Binary_hours / 10;
  byte swappedHours2 = Binary_hours % 10;
  byte swappedMin1 = Binary_min / 10;
  byte swappedMin2 = Binary_min % 10;

  byte swappedSec1 = Binary_sec / 10;
  byte swappedSec2 = Binary_sec % 10;

  clearMatrix();
  
  // Rahmen
  paintBoarder();
  
  tmpBit=1;
  for(int i=0;i<8;i++)
  {
    setMatrixOr(8 - i, (((tmpBit & swappedHours1) ? 1 : 0) << 13));
    setMatrixOr(8 - i, (((tmpBit & swappedHours2) ? 1 : 0) << 12));
    setMatrixOr(8 - i, (((tmpBit & swappedMin1) ? 1 : 0) << 11));
    setMatrixOr(8 - i, (((tmpBit & swappedMin2) ? 1 : 0) << 10));
    setMatrixOr(8 - i, (((tmpBit & swappedSec1) ? 1 : 0) << 9));
    setMatrixOr(8 - i, (((tmpBit & swappedSec2) ? 1 : 0) << 8));
        
    tmpBit<<=1;
  }
  
  writeMatrix();
  
  return;
}

// Anzeigefunktion der BinärUhr Querformat
void showBinary()
{
  clearMatrix();

  // Zeit
  setMatrix(2, swapBits(Binary_hours) << 6);
  setMatrix(4, swapBits(Binary_min) << 6);
  setMatrix(6, swapBits(Binary_sec) << 6);
        
  // Rahmen
  paintBoarder();
  
  writeMatrix();  
  
  return;
}

void buttonBinary(Button btn, byte id)
{

}
