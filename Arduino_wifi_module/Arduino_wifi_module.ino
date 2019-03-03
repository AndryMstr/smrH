#include "ESP8266.h"
#include <SoftwareSerial.h>
#include <math.h>
 
#define SSID     "domokom178"
#define PASSWORD "12341234"
#define TEMP_PIN A0
#define LIGHT A1


SoftwareSerial mySerial(4, 5);
ESP8266 wifi(mySerial);
String name = "AndryDjagopMaster";
 
void setup(void) {
  Serial.begin(9600);
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println("192.168.1.88:5000/");
  } else {
    Serial.println("Wi-Fi connection error");
  }
}
 
void loop(void) {
//  float v_temp = 1023.0 / analogRead(TEMP_PIN) - 1.0;
//  float temp = 1.0 / ( -log(v_temp) / 3977.0
//                            + 1.0 / 295.0 ) - 273.0;
  float light = analogRead(LIGHT);
  
  if (wifi.createTCP("http://192.168.1.88", 5000)) {
    String data = "GET /push_light?";
    data += "new_light=" + String(light) + " HTTP/1.1\r\n";
    data += "Host: 192.168.1.88\r\n\r\n";
    wifi.send(data.c_str(), data.length());
    wifi.releaseTCP();
  } else {
    Serial.println("create TCP error");
  }
  delay(1000);
}