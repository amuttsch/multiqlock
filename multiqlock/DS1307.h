/**
 * DS1307.h
 * Klasse fuer den Zugriff auf die DS1307 Echtzeituhr.
 *
 * @mc       Arduino/RBBB
 * @autor    Christian Aschoff / caschoff _AT_ mac _DOT_ com
 * @version  1.1
 * @datum    1.3.2011
 *
 * Versionshistorie:
 * V 1.1:  - dayOfMonth nach date umbenannt.
 */
#ifndef DS1307_H
#define DS1307_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #define Wire_read(a) Wire.read(a)
  #define Wire_write(a) Wire.write(a)  
#else
  #define Wire_read(a) Wire.receive(a)
  #define Wire_write(a) Wire.send(a)
  #include "WProgram.h"
#endif

class DS1307 {
public:
  DS1307(int address);

  void readTimeOnly();
  void writeTime();

  void setSeconds(byte seconds);
  void setMinutes(byte minutes);
  void incMinutes();
  void setHours(byte hours);
  void incHours();
  void setDayOfWeek(byte dayOfWeek);
  void setDate(byte date);
  void setMonth(byte month);
  void setYear(byte year);
  char* getLastSync();
  void setLastSync(char* timestamp);

  byte getSeconds();
  byte getMinutes();
  byte getHours();
  byte getDayOfWeek();
  byte getDate();
  byte getMonth();
  byte getYear();

private:
  int _address;

  byte _seconds;
  byte _minutes;
  byte _hours;
  byte _dayOfWeek;
  byte _date;
  byte _month;
  byte _year;

  byte decToBcd(byte val);
  byte bcdToDec(byte val);   
  
  char* _lastSync;
};

#endif

