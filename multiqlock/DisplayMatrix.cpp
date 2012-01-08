/**
 * DisplayMatrix.h
 * Mit dieser Datei werden die Matrixausgaben gesteuert.
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    20.3.2011
 */
#include <SPI.h>
#include <EEPROM.h>
#include "Pins.h"
#include "DisplayMatrix.h"
#include "ShiftRegister.h"
#include "Global.h"

// Die Helligkeit (1-9)
int brightness = 9;

#ifdef LAYOUT_ORIGINAL
  ShiftRegister shiftRegister(PinData, PinClock, PinLatch);
#endif

// Die Matrix, eine Art Bildschirmspeicher
word matrix[2][MATRIX_ROWS];
volatile boolean swapPages;
volatile uint8_t currentPage = 0;
uint8_t offscreenPage = 0;
uint8_t currentRow = 0;
// Cache für schnellere Matrixansteuerung
volatile uint8_t rowBitsLow[MATRIX_ROWS];
volatile uint8_t rowBitsHigh[MATRIX_ROWS];

// Die Helligkeit
uint8_t brightnessHi=255;
uint8_t brightnessLo=10;
boolean brightnessPWM=true;
float adjustedBrightness = 0.f;
int currentBrightness = 0;
unsigned long nextBrightnessAdjustment = 0;
int noChangeCounter = 0;
boolean ignoreBrightness = false; // Soll die aktuelle Helligkeit beim AKTUELLEN writeMatrix ignoriert werden?
                                  // Für die Helligkeitseinstellung notwendig
boolean doForceLDRupdate = false;
int ovrBrightness;

// Hilfsvariable, um das Display auf den Kopf zu stellen
#ifdef UPSIDE_DOWN
  #define DISPLAY_SHIFT  9-
#else
  #define DISPLAY_SHIFT  0+
#endif

void initMatrix()
{
  // Cache für Ansteuerung der Zeilen
  uint16_t rowbit=0x1;
  
  #ifdef LAYOUT_EBERHARD
    for(int i = 0;i<MATRIX_ROWS;i++)
    {
      rowBitsLow[i]=lowByte(rowbit);
      rowBitsHigh[i]=highByte(rowbit);
      rowbit=rowbit<<1;
    }
  #endif
	
	pinMode(PinLatch, OUTPUT);
  pinMode(PinClock, OUTPUT);
  pinMode(PinData, OUTPUT);

  digitalWrite(PinLatch,LOW);
  digitalWrite(PinData,LOW);
  digitalWrite(PinClock,LOW);
  
  // Zum Verhindern von Problemen mit den LEDs (z.B. Datenmüll in den HC595?)
  // sicherheitshalber die Spannung an den LED-Treibern abschalten...
  pinMode(outputEnablePin, OUTPUT);
  digitalWrite(outputEnablePin, LOW);
  
  // Helligkeitssensor konfigurieren
  pinMode(brightnessInputPin, INPUT);
  
  // Brightness aus EEPROM lesen
  brightnessHi=EEPROM.read(EEPROM_ADR_BRIGHTNESS_HI);
  brightnessLo=EEPROM.read(EEPROM_ADR_BRIGHTNESS_LO);

  clearMatrix();
}

// Die Matrix loeschen
void clearMatrix()
{
  #ifdef LAYOUT_EBERHARD
    offscreenPage = 1 - currentPage;
  #endif
  for (int i = 0; i < MATRIX_ROWS; i++)
  {
    matrix[offscreenPage][i] = 0;
  }
}

void setMatrix(char y, word data)
{
  // Parameter pr�fen
  if (y < 0 || y > MATRIX_ROWS)
  {
    return;
  }
  
  matrix[offscreenPage][y] = data;
  
  return;
}

void setMatrixOr(char y, word data)
{
  // Parameter pr�fen
  if (y < 0 || y > MATRIX_ROWS)
  {
    return;
  }
  
  matrix[offscreenPage][y] |= data;
  
  return;
}

void setLED(int x, int y)
{	
  if(x >= MATRIX_COLUMNS || y >= MATRIX_ROWS || x < 0 || y < 0)
  {
    return;
  }
  
	switch (x)
	{
	case 0:  matrix[offscreenPage][y] |= 0b1000000000000000;
			 break;
	case 1:	 matrix[offscreenPage][y] |= 0b0100000000000000;
			 break;
	case 2:	 matrix[offscreenPage][y] |= 0b0010000000000000;
			 break;
	case 3:  matrix[offscreenPage][y] |= 0b0001000000000000;
			 break;
	case 4:  matrix[offscreenPage][y] |= 0b0000100000000000;
			 break;
	case 5:  matrix[offscreenPage][y] |= 0b0000010000000000;
			 break;
	case 6:  matrix[offscreenPage][y] |= 0b0000001000000000;
			 break;
	case 7:  matrix[offscreenPage][y] |= 0b0000000100000000;
			 break;
	case 8:  matrix[offscreenPage][y] |= 0b0000000010000000;
			 break;
	case 9:  matrix[offscreenPage][y] |= 0b0000000001000000;
			 break;
	case 10: matrix[offscreenPage][y] |= 0b0000000000100000;
			 break;
	}
  
  return;
}

void writeLine(int x0, int y0, int x1, int y1)
{
  int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = dx+dy, e2; /* error value e_xy */
 
  for(;;){  /* loop */
    setLED(x0,y0);
    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

word getMatrix(char y)
{
  if (y < 0 || y > MATRIX_ROWS)
  {
    return 0;
  }
  
  return matrix[offscreenPage][y];
}

boolean validateXY(int x, int y)
{
	if (x < 0 || x > (MATRIX_COLUMNS - 1) || y < 0 || y > (MATRIX_ROWS - 1))
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 * Funktionen, um die Hi und Lo Helligkeit zu ermitteln und zu setzen
 */
int getBrightnessLo()
{
  return brightnessLo;
}
int getBrightnessHi()
{
  return brightnessHi;
}
void setBrightnessLo(int value)
{
  brightnessLo = value;
}
void setBrightnessHi(int value)
{
  brightnessHi = value;
}
// Nach dem Moduswechsel wieder ein LDR update anfordern
void forceLDRupdate()
{
  doForceLDRupdate = true;
}

/**
 * Soll im aktuellen writeMatrix das adjustBrightness ignoriert werden?
 */ 
void overrideBrightness(int value)
{
  ovrBrightness = value;
  ignoreBrightness = true;
}

#ifdef LAYOUT_EBERHARD
void adjustBrightness()
{
  // Soll im aktuellen Durchgang die Helligkeit irgnoriert werden?
  // Für die Anpassung der Hi Lo Werte des LDR
  if (ignoreBrightness)
  {
    ignoreBrightness = false;
    analogWrite(outputEnablePin, ovrBrightness);
    return;
  }
  if(nextBrightnessAdjustment<millis() || doForceLDRupdate)
  {
    int ldr=analogRead(brightnessInputPin);
    int mappedLDR = map(ldr, ldrDarkSample, ldrBrightSample, brightnessLo, brightnessHi);
    float targetBrightness = (float)constrain(mappedLDR, brightnessLo, brightnessHi);
    adjustedBrightness = adjustedBrightness+ldrGain*((float)targetBrightness-adjustedBrightness);
    int cb = constrain((int)(adjustedBrightness+.5f), brightnessLo, brightnessHi);
    
    if(abs(cb-currentBrightness)>0 || doForceLDRupdate)
    {
      doForceLDRupdate = false;
      noChangeCounter=0;
      currentBrightness = cb;

      analogWrite(outputEnablePin, 255-currentBrightness);

#ifdef DEBUG
      Serial.print("LDR readout: ");
      Serial.print(ldr);
      Serial.print(" Mapped LDR: ");
      Serial.print(mappedLDR);
      Serial.print(" TargetBrightness: ");
      Serial.print(targetBrightness);
      Serial.print(" CurrentBrightness: ");
      Serial.println(constrain((int)(currentBrightness+.5f), brightnessLo, brightnessHi));
#endif
    }
    else
      noChangeCounter++;
    
    unsigned long adjustingDelay=50L; 
    if(noChangeCounter>10)
    {
      adjustingDelay = 1000L; // Falls nichts passiert ist, reicht ein 1sec Delay
      noChangeCounter=10;
    }
    nextBrightnessAdjustment=millis()+adjustingDelay;
  }
}
#endif

/**
 * Die Matrix ausgeben
 */
void writeMatrix() {
  // Wenn wir das Layout von Eberhard haben, dann wird die Matrix per Interrupt ausgegeben
  #ifdef LAYOUT_EBERHARD
    for (int i = 0; i < MATRIX_ROWS; i++) {
      matrix[offscreenPage][i] = ~matrix[offscreenPage][i];
    }
    // Kennzeichen setzten, dass die Seiten gewechselt werden können
    swapPages = true;
    adjustBrightness();
    return;
  #endif
  
  #ifdef LAYOUT_ORIGINAL
    word row = 1;
    
    #ifdef ENABLE_LDR
      brightness = (1024 - analogRead(brightnessInputPin)) / 114 + 1;
    #endif
    
    for (word k = 0; k < MATRIX_ROWS + 1; k++)
    {
      // Gegen das Glimmen alle LEDs einmal aus...
      shiftRegister.prepareShiftregisterWrite();
      shiftRegister.shiftOut(65535);
      shiftRegister.shiftOut(row);
      shiftRegister.finishShiftregisterWrite();
      
      #ifdef ENABLE_LDR
        // hier kann man versuchen, das Taktverhaeltnis zu aendern (Auszeit)...
        delayMicroseconds((10-brightness)*50);
      #endif

      // Jetzt die Daten...
      #ifdef SKIP_BLANK_LINES
      if (matrix[offscreenPage][DISPLAY_SHIFT k] != 0)
      {
      #endif
        shiftRegister.prepareShiftregisterWrite();
        shiftRegister.shiftOut(~matrix[offscreenPage][DISPLAY_SHIFT k]);
        shiftRegister.shiftOut(row);
        shiftRegister.finishShiftregisterWrite();
      #ifdef SKIP_BLANK_LINES
      }
      #endif
      #ifdef ENABLE_LDR
        // hier kann man versuchen, das Taktverhaeltnis zu aendern (Anzeit)...
        delayMicroseconds(brightness*50);
      #else
        delayMicroseconds(250);
      #endif

      row = row << 1;
    }
  #endif
}

//--- Interrupt-Routine: Die Multiplexer mit der Matrix befeuern
void iProcess()
{
  if(swapPages)
  {
    currentPage = 1 - currentPage;
    swapPages = false;
  }
  
// *** Hinzugefügt Start *** 
// Damit es nicht zu "Geister-LEDs" kommt
// 18.07.11

  digitalWrite(PinLatch, LOW); 
  SPI.transfer( lowByte(0xFFFF)); 
  SPI.transfer(highByte(0xFFFF)); 
  SPI.transfer(rowBitsLow[currentRow]); 
  SPI.transfer(rowBitsHigh[currentRow]); 
  digitalWrite(PinLatch, HIGH); 

// *** Hinzugefügt Ende *** 
  
  digitalWrite(PinLatch, LOW);
  SPI.transfer(lowByte(matrix[currentPage][currentRow]));
  SPI.transfer(highByte(matrix[currentPage][currentRow]));
  SPI.transfer(rowBitsLow[currentRow]);  
  SPI.transfer(rowBitsHigh[currentRow]);
  digitalWrite(PinLatch, HIGH); 
  
  currentRow++;
  if( currentRow >= MATRIX_ROWS )
     currentRow=0;
}

