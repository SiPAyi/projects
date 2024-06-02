#include <EEPROM.h>
#define EEPROM_SIZE 512

// EEPROM addresses
const int addr_flag = 0;  // Address for the marker flag
const int addr_rb = addr_flag + sizeof(byte);
const int addr_pb = addr_rb + sizeof(float);
const int addr_yb = addr_pb + sizeof(float);
const int addr_axb = addr_yb + sizeof(float);
const int addr_ayb = addr_axb + sizeof(float);
const int addr_azb = addr_ayb + sizeof(float);
const byte marker = 0xAA;  // Marker value to indicate EEPROM is initialized

void isEEPROMInitialized() {
  EEPROM.begin(EEPROM_SIZE);
  byte flag = EEPROM.read(addr_flag);
  EEPROM.end();
  if(flag == marker){
    Serial.println("bias values loading from eeprom");
    loadValuesFromEEPROM();
  }else{
    Serial.println("getting bias values because no values availave at this movement");
    bias_values();
  }
}

void saveValuesToEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(addr_flag, marker);
  EEPROM.put(addr_rb, rb);
  EEPROM.put(addr_pb, pb);
  EEPROM.put(addr_yb, yb);
  EEPROM.put(addr_axb, axb);
  EEPROM.put(addr_ayb, ayb);
  EEPROM.put(addr_azb, azb);
  EEPROM.commit();
  EEPROM.end();
  Serial.println("Values saved to EEPROM.");
}

void loadValuesFromEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(addr_rb, rb);
  EEPROM.get(addr_pb, pb);
  EEPROM.get(addr_yb, yb);
  EEPROM.get(addr_axb, axb);
  EEPROM.get(addr_ayb, ayb);
  EEPROM.get(addr_azb, azb);
  EEPROM.end();
  Serial.println("Values loaded from EEPROM.");
  Serial.print("rb: ");
  Serial.println(rb);
  Serial.print("pb: ");
  Serial.println(pb);
  Serial.print("yb: ");
  Serial.println(yb);
  Serial.print("axb: ");
  Serial.println(axb);
  Serial.print("ayb: ");
  Serial.println(ayb);
  Serial.print("azb: ");
  Serial.println(azb);
}

void askToSave() {
  Serial.println("Do you want to save the initial values to EEPROM? (y/n): ");
  while (!Serial.available()) {
    // Wait for user input
  }
  char userInput = Serial.read();
  if (userInput == 'y' || userInput == 'Y') {
    saveValuesToEEPROM();
  } else if (userInput == 'n' || userInput == 'N') {
    Serial.println("then go and edit the values in the code and upload them again");
  } else {
    Serial.println("Invalid input. Please enter 'y' or 'n'.");
    askToSave();
  }
}