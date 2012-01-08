/**
 * DisplayMatrix.h
 * Mit dieser Datei werden die Matrixausgaben gesteuert.
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    20.3.2011
 */
#ifndef DISPLAYMATRIX_H
#define DISPLAYMATRIX_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

void initMatrix();
void setMatrix(char y, word data);
void setLED(int x, int y);
void setMatrixOr(char y, word data);
void writeLine(int x0, int y0, int x1, int y1);
word getMatrix(char y);
void writeMatrix();
void clearMatrix();
int getBrightnessLo();
int getBrightnessHi();
void setBrightnessLo(int value);
void setBrightnessHi(int value);
void overrideBrightness(int value);
// Nach dem Moduswechsel wieder ein LDR update anfordern
void forceLDRupdate();
void iProcess();
boolean validateXY(int x, int y);

#endif

