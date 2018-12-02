#include <QuadDisplay.h>//
#define DISPLAI_PIN 7
#define TEMP A0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(TEMP,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //displayInt(DISPLAI_PIN, 123);
  int tempvar;
  float voltage;
  float gradus;
  tempvar = analogRead(TEMP);
  Serial.println(tempvar);
  voltage = tempvar*5/1024; //значение в вольтах
  gradus = voltage*100 - 273.15;
  displayFloat(DISPLAI_PIN, tempvar, 1);
  delay(500);
  }
