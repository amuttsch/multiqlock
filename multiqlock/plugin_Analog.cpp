/**
 * Analog.cpp
 * Zeigt analoge Uhr
 *
 * @mc       Arduino/RBBB
 * @autor    Bernhard Göberndorfer
 * @version  4.0
 * @datum    11.01.2012
 */
#include "plugin_Analog.h"

//#define DEBUG;
// save coords of clock hands 
int   Analog_mEndX;
int   Analog_mEndY;
int   Analog_hEndX;
int   Analog_hEndY;
// which info should be shown? (Analog & Snake)
boolean Analog_sDisp;
boolean Analog_mDisp;
boolean Analog_hDisp;

int Analog_hours;
int Analog_min;
int Analog_sec;



// calcualte angle of analog clock in radian
// toRadian(9, 12) = toRadian(21, 24) = toRadian(45, 60)
float toRadian(int val, int full)
{
  return val * 2 * 3.14 / full;
}


//// calulates angle of analog clock in degree
//// toDegree(9, 12) = 270 = toDegree(21, 24) = toDegree(45, 60)
//float toDegree(int val, int full)
//{
//  return 360 / full * val;
//}


/* 
 * draw 'snake-lines' as 'shadow' of clock hands: 
 * 
 * @param margin        margin to border (e.g. 2)
 * @param currentValue  current time (e.g. 45 - minutes)
 * @param maxValue      max. possible value of currentValue (e.g. 60 - minutes)
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

	// ^^ line-topleft
	if (leds >= (maxLedsl+maxLedsu+maxLedsr+maxLedsor)) {
		c = (leds-(maxLedsl+maxLedsu+maxLedsr+maxLedsor));
		writeLine(margin+c, margin, margin, margin);
		leds = leds-c-1;
	}
		
	// << line-left
	if (leds >= (maxLedsu+maxLedsr+maxLedsor)) {
		c = (leds-(maxLedsu+maxLedsr+maxLedsor));
		writeLine(margin, MATRIX_ROWS-1-margin, margin, MATRIX_ROWS-1-margin-c);
		leds = leds-c-1;
	}
	
	// == line-bottom
	if (leds >= (maxLedsr+maxLedsor)) {
		c = (leds-(maxLedsr+maxLedsor));
		writeLine(MATRIX_COLUMNS-1-margin-c, MATRIX_ROWS-1-margin, MATRIX_COLUMNS-1-margin, MATRIX_ROWS-1-margin);
		leds = leds-c-1;
	}
	
	// >> line-right
	if (leds >= maxLedsor) {
		c = (leds-maxLedsor);
		writeLine(MATRIX_COLUMNS-1-margin, margin+c, MATRIX_COLUMNS-1-margin, margin);
		leds = leds-c-1;
	}
	
	// ^^ line-topright
	c = (leds);
	writeLine(ANALOG_CENTER_X+c, margin, ANALOG_CENTER_X, margin);
}


void initAnalog()
{
  // which info should be shown at pluginstart ?
  Analog_sDisp = false;
  Analog_mDisp = true;
  Analog_hDisp = true;
  return;
}

// Update position of clock hands
// ... only update if clock hand should be shown
// ... only update if time has changed (could be done using timeDiff....)
void updateAnalog(int timeDiff)
{
  if (Analog_sDisp && Analog_sec != (int)getSeconds()) {
    Analog_sec = (int)getSeconds();
  }
  if (Analog_mDisp && Analog_min != (int)getMinutes()) {
    Analog_min = (int)getMinutes();
    float Analog_mAngle = toRadian(Analog_min, 60);
    Analog_mEndX = (int)(ANALOG_mLENGTH * sin(Analog_mAngle));
    Analog_mEndY = -(int)(ANALOG_mLENGTH * cos(Analog_mAngle));
  }
  if (Analog_hDisp && Analog_hours != (int)getHours()) {
    Analog_hours = (int)getHours();
    float Analog_hAngle = toRadian(Analog_hours, 24);
    Analog_hEndX = (int)(ANALOG_hLENGTH * sin(Analog_hAngle));
    Analog_hEndY = -(int)(ANALOG_hLENGTH * cos(Analog_hAngle));
  }
}
  
// show analog clock with clock hand
void showAnalog()
{ 
    clearMatrix();
    
    if (Analog_hours < 12) { // a.m.
      CORNER_UPPER_LEFT;
      CORNER_UPPER_RIGHT;
    } else { // p.m.
      CORNER_LOWER_RIGHT;
      CORNER_LOWER_LEFT;
    }
    
    if (Analog_sDisp) {
      writeSnake(0, Analog_sec, 60);
    }
    if (Analog_mDisp) {
      writeLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, ANALOG_CENTER_X + Analog_mEndX, ANALOG_CENTER_Y + Analog_mEndY);
    }
    if (Analog_hDisp) {
      writeLine(ANALOG_CENTER_X, ANALOG_CENTER_Y, ANALOG_CENTER_X + Analog_hEndX, ANALOG_CENTER_Y + Analog_hEndY);
    }
    
    writeMatrix();

}
  
  
// update current time
void updateAnalogSnake(int timeDiff)
{
  if (Analog_sDisp && Analog_sec != (int)getSeconds()) {
    Analog_sec = (int)getSeconds();
  }
  if (Analog_mDisp && Analog_min != (int)getMinutes()) {
    Analog_min = (int)getMinutes();
  }
  if (Analog_hDisp && Analog_hours != (int)getHours()) {
    Analog_hours = (int)getHours();
  }
}

// only display snake lanes as Clock
void showAnalogSnake()
{ 
  
    clearMatrix();
    
    if (Analog_hours < 12) { // a.m.
      CORNER_UPPER_LEFT;
      CORNER_UPPER_RIGHT;
    } else { // p.m.
      CORNER_LOWER_RIGHT;
      CORNER_LOWER_LEFT;
    }

    if (Analog_sDisp) {
      if (!Analog_mDisp) {
        writeSnake(3, Analog_sec, 60);
      } else {
        writeSnake(4, Analog_sec, 60);
      }
    }

    if (Analog_mDisp) {
      writeSnake(3, Analog_min, 60);
    }
    
    if (Analog_hDisp) {
      writeSnake(0, Analog_hours%12, 12);
      writeSnake(1, Analog_hours%12, 12);
      if (!Analog_sDisp && !Analog_mDisp) {
        writeSnake(2, Analog_hours%12, 12);
      }
    }
    
    writeMatrix();
}

void buttonAnalog(Button btn, byte id)
{
  // button hour++ 
  // show or hide seconds hand
  if (id == BUTTON2) {  
    Analog_sDisp = !Analog_sDisp;
//    Analog_update = true;
    forcePluginUpdate();
  }

  // button minute++
  // show or hide minute hand
  if (id == BUTTON1) {     
    Analog_mDisp = !Analog_mDisp;
//    Analog_update = true;
    forcePluginUpdate();
  }
}


