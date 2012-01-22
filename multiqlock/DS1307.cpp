/**
 * DS1307.cpp
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
#include <Wire.h> // Wire library fuer I2C
#include "DS1307.h"
#include "Global.h"

/**
 * Initialisierung mit der Adresse der DS1307
 */
DS1307::DS1307(int address) {
  _address = address;
}

/**
 * Die Uhrzeit auslesen und in den Variablen ablegen
 */
void DS1307::readTimeOnly() {
  // Reset the register pointer
  Wire.beginTransmission(_address);
  Wire_write((uint8_t)0x00);
  Wire.endTransmission();
  // Statt 7 nur einen Teil ermitteln, Datum wird aktuell nicht benötigt
  Wire.requestFrom(_address, 3);

  // A few of these need masks because certain bits are control bits
  _seconds = bcdToDec(Wire_read() & 0x7f);
  _minutes = bcdToDec(Wire_read());
  _hours = bcdToDec(Wire_read() & 0x3f); // Need to change this if 12 hour am/pm

  _dayOfWeek = 0;
  _date = 0;
  _month = 0;
  _year = 0;  

// Wird aktuell nicht mehr benötigt
//  _dayOfWeek = bcdToDec(Wire.receive());
//  _date = bcdToDec(Wire.receive());
//  _month = bcdToDec(Wire.receive());
//  _year = bcdToDec(Wire.receive());  
}

/**
 * Die Uhrzeit aus den Variablen in die DS1307 schreiben
 */
void DS1307::writeTime() {
  Wire.beginTransmission(_address);
  Wire_write((uint8_t)0x00); // 0 to bit 7 starts the clock
  Wire_write(decToBcd(_seconds));
  Wire_write(decToBcd(_minutes));
  Wire_write(decToBcd(_hours)); // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire_write(decToBcd(_dayOfWeek));
  Wire_write(decToBcd(_date));
  Wire_write(decToBcd(_month));
  Wire_write(decToBcd(_year));
  Wire_write(0b00010000); // 1Hz Rechteck auf SQW fuer den Display-Update-Interrupt...
  Wire.endTransmission();
}

/**
 * Konvertierung Dezimal zu "Binary Coded Decimal"
 */
byte DS1307::decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

/**
 * Konvertierung "Binary Coded Decimal" zu Dezimal
 */
byte DS1307::bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

//
// Setter/Getter
//

void DS1307::setSeconds(byte seconds) {
  _seconds = seconds;
}

void DS1307::setMinutes(byte minutes) {
  _minutes = minutes;
}

void DS1307::incMinutes() {
  _minutes++;
  if(_minutes > 59) {
    _minutes = 0;
  }
}

void DS1307::setHours(byte hours) {
  _hours = hours;
}

void DS1307::incHours() {
  _hours++;
  if(_hours > 23) {
    _hours = 0;
  }
}

void DS1307::setDayOfWeek(byte dayOfWeek) {
  _dayOfWeek = dayOfWeek;
}

void DS1307::setDate(byte date) {
  _date = date;
}

void DS1307::setMonth(byte month) {
  _month = month;
}

void DS1307::setYear(byte year) {
  _year = year;
}

void DS1307::setLastSync(char* timestamp) {
  _lastSync = timestamp;
}

char* DS1307::getLastSync() {
  return _lastSync;
}

byte DS1307::getSeconds() {
  return _seconds;
}

byte DS1307::getMinutes() {
  return _minutes;
}

byte DS1307::getHours() {
  return _hours;
}

byte DS1307::getDayOfWeek() {
  return _dayOfWeek;
}

byte DS1307::getDate() {
  return _date;
}

byte DS1307::getMonth() {
  return _month;
}

byte DS1307::getYear() {
  return _year;
}

