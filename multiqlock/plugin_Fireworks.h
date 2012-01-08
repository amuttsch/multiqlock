/**
 * Fireworks.h
 * Kleine Klasse zum Anzeigen eines Feuerwerks.
 *
 * @mc       Arduino/RBBB
 * @autor    Andreas Muttscheller
 * @version  1.0
 * @datum    18.3.2011
 */
 
#ifndef FIREWORKS_H
#define FIREWORKS_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "Button.h"

void initFireworks();
void updateFireworks(int timeDiff);
void showFireworks();
void buttonFireworks(Button btn, byte id);

class classFirework {
public:
	boolean done;
	void initFireworks();
	void updateFireworks(int timeDiff);
	void showFireworks();
	int getX();
	void resetStatus();

private:
	// Typedef, der den Status des Feuerwerks beinhaltet
	typedef struct s_firework
	{
		int status; // 0=neu 1=fliegt, 2=explodiert, 9=fertig
    int y; // aktuelle H�he
		int x;  // aktuelle Breite
		int explosionY; // H�he, in der die Rakete explodieren soll
		int explosionCount; // wie oft waren wir in der Explosions-Funktion?
		int maxExplosion; // Maximaler Explosionsradius (erstmal fix)
    int startOffset;
	};

	// eigentliche Variable
	s_firework firework;

	boolean intMatrix[11][10];
  boolean getMatrixShow(int x, int y);
  void setMatrixShow(int x, int y);
	void initializeFirework();
  void updateOffset();
	void updateFlight();
	void updateExplosion();
	void showFlight();
	void showExplosion();
};

#endif
