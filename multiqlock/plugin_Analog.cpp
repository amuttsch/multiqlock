/**
 * Analog.cpp
 * Zeigt analoge Uhr
 *
 * @mc       Arduino/RBBB
 * @autor    Bernhard Göberndorfer
 * @version  2.0
 * @datum    05.01.2012
 */
#include "plugin_Analog.h"

//#define DEBUG;
// Endpunkte der Zeiger werden zwischengespeichert, Winkel werden nur berechnet wenn Uhrzeit sich ändert. 
int   Analog_mEndX;
int   Analog_mEndY;
int   Analog_hEndX;
int   Analog_hEndY;
boolean Analog_sHide;
boolean Analog_mHide;
boolean Analog_hHide;
boolean Analog_update; // hat sich Anzeige geaendert?

int Analog_hours;
int Analog_min;
int Analog_sec;



// calcualtes angle of analog clock in radian
// toRadian(9, 12) = toRadian(21, 24) = toRadian(45, 60)
float toRadian(int val, int full)
{
  return val * 2 * 3.14 / full;
}


// calulates angle of analog clock in degree
// toDegree(9, 12) = 270 = toDegree(21, 24) = toDegree(45, 60)
float toDegree(int val, int full)
{
  return 360 / full * val;
}

/* 
 * zeichnet Linien nach folgendem Muster: 
 * 
 * @param margin Abstand nach Außen (zb 2)
 * @param currentValue  Aktueller Wert (zb 45)
 * @param maxValue maximal möglicher Wert (zb 60)
 *
 *        >| |< margin=2
 * ########### || 
 * ########### \/ margin=2
 * #####0000## --
 * ########0##
 * ########0##
 * ##0#####0## currentValue=45
 * ##0#####0##    maxValue =60
 * ##0#####0##
 * ##0000000##
 * ###########
 * ###########
 * 
 * 
 */
void writeSnake (int margin, int currentValue, int maxValue)
{

	int maxLedsol = ANALOG_CENTER_X-margin;
	int maxLedsl  = MATRIX_ROWS-2*margin-1;
	int maxLedsu  = MATRIX_COLUMNS-2*margin-1;
	int maxLedsr  = MATRIX_ROWS-2*margin-1;
	int maxLedsor = MATRIX_COLUMNS-ANALOG_CENTER_X-margin-1;
	
	int maxLeds = maxLedsol+maxLedsl+maxLedsu+maxLedsr+maxLedsor;
	int val = (100 * currentValue / maxValue);
	int leds = (maxLeds * currentValue / maxValue); 
	int c;
			
	// ^^ linke hälfte obere Linie 
	if (leds >= (maxLedsl+maxLedsu+maxLedsr+maxLedsor)) {
		c = (leds-(maxLedsl+maxLedsu+maxLedsr+maxLedsor));
		writeLine(margin+c, margin, margin, margin);
		leds = leds-c-1;
	}
		
	// << linke Linie 
	if (leds >= (maxLedsu+maxLedsr+maxLedsor)) {
		c = (leds-(maxLedsu+maxLedsr+maxLedsor));
		writeLine(margin, MATRIX_ROWS-1-margin, margin, MATRIX_ROWS-1-margin-c);
		leds = leds-c-1;
	}
	
	// == untere Linie
	if (leds >= (maxLedsr+maxLedsor)) {
		c = (leds-(maxLedsr+maxLedsor));
		writeLine(MATRIX_COLUMNS-1-margin-c, MATRIX_ROWS-1-margin, MATRIX_COLUMNS-1-margin, MATRIX_ROWS-1-margin);
		leds = leds-c-1;
	}
	
	// >> rechte Linie
	if (leds >= maxLedsor) {
		c = (leds-maxLedsor);
		writeLine(MATRIX_COLUMNS-1-margin, margin+c, MATRIX_COLUMNS-1-margin, margin);
		leds = leds-c-1;
	}
	
	// ^^ rechte hälfte obere Linie
	c = (leds);
	writeLine(ANALOG_CENTER_X+c, margin, ANALOG_CENTER_X, margin);
}

// Initialisierung
void initAnalog()
{
  // was soll beim Start NICHT angezeigt werden?
  Analog_sHide = false;
  Analog_mHide = false;
  Analog_hHide = false;
  return;
}

// Position der Zeiger aktualisieren
// ... nur wenn diese angezeigt werden sollen 
// ... und nur bei Wertänderung
void updateAnalog(int timeDiff)
{
  if (!Analog_sHide && Analog_sec != (int)getSeconds()) {
    Analog_sec = (int)getSeconds();
    Analog_update = true;
  }
  if (!Analog_mHide && Analog_min != (int)getMinutes()) {
    Analog_min = (int)getMinutes();
    float Analog_mAngle = toRadian(Analog_min, 60);
    Analog_mEndX = (int)(ANALOG_mLENGTH * sin(Analog_mAngle));
    Analog_mEndY = -(int)(ANALOG_mLENGTH * cos(Analog_mAngle));
    Analog_update = true;
  }
  if (!Analog_hHide && Analog_hours != (int)getHours()) {
    Analog_hours = (int)getHours();
    float Analog_hAngle = toRadian(Analog_hours, 24);
    Analog_hEndX = (int)(ANALOG_hLENGTH * sin(Analog_hAngle));
    Analog_hEndY = -(int)(ANALOG_hLENGTH * cos(Analog_hAngle));
    Analog_update = true;
  }
}
  
// Anzeigefunktion
void showAnalog()
{ 
  if (Analog_update) {
    Analog_update = false;
    clearMatrix();
    
    // Eck-Leds immer anzeigen.
    CORNER_UPPER_LEFT;
    CORNER_UPPER_RIGHT;
    CORNER_LOWER_RIGHT;
    CORNER_LOWER_LEFT;
    
    if (!Analog_sHide) {
      writeSnake(ANALOG_sMARGIN, Analog_sec, 60);
    }
    if (!Analog_mHide) {
      writeLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, ANALOG_CENTER_X + Analog_mEndX, ANALOG_CENTER_Y + Analog_mEndY);
    }
    if (!Analog_hHide) {
      writeLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, ANALOG_CENTER_X + Analog_hEndX, ANALOG_CENTER_Y + Analog_hEndY);
    }
    
    writeMatrix();
  }
}

void buttonAnalog(Button btn, byte id)
{
  // Taste Minuten++ gedrueckt?
  // Sekundenzeiger anzeigen / ausblenden
  if (id == BUTTON1) {  
    Analog_sHide = !Analog_sHide;
    updateAnalog(1);
  }

  // Taste Stunden++ gedrueckt?
  // Minutenzeiger anzeigen / ausblenden
  if (id == BUTTON2) {     
    Analog_mHide = !Analog_mHide;
    updateAnalog(1);
  }
}

