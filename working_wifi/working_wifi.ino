#include "ESP8266.h"
#include <SoftwareSerial.h>
#include <math.h>
 
#define SSID     "domokom178"
#define PASSWORD "12341234"
#define TEMP_PIN A0
 
SoftwareSerial mySerial(4, 5);
ESP8266 wifi(mySerial);
//String name = "yushok_111";
 
void setup(void) {
  Serial.begin(9600);
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println("http://192.168.1.88:5000/");
  } else {
    Serial.println("Wi-Fi connection error");
  }
}
 
void loop(void) {
  int temp = 500;
  if (wifi.createTCP("192.168.1.88", 5000)) {
    String data = "GET /push_light?";
    data += "new_light=" + String(temp) + " HTTP/1.1\r\n";
    data += "Host: 192.168.1.88\r\n\r\n";
    wifi.send(data.c_str(), data.length());
    Serial.println(data);
    wifi.releaseTCP();
  } else {
    Serial.println("create TCP error");
  }
  delay(1000);
}
