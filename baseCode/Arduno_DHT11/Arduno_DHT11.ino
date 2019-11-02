/* DHTServer - ESP8266 Webserver with a DHT sensor as an input

   Based on ESP8266Webserver, DHTexample, and BlinkWithoutDelay (thank you)

   Version 1.0  5/3/2014  Version 1.0   Mike Barela for Adafruit Industries
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
// Replace with your network details
const char* ssid     = "smart";
const char* password = "17812341234";
const char* sensor_name = "room";
String poss_data[2] = {"temp", "humidity"};

ESP8266WebServer server(80);
DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
 
float humidity, temp;  // Values read from sensor
String webString="";     // String to display
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor

String collected_sting(String arr[]){
  String rrr = arr[0];
  for(int i=1; i<sizeof(arr);i++){rrr += ";" + arr[i];}
  return "{\"sensor_name\": \"" + String(sensor_name) + "\", \"data\": \"" + rrr + "\"}";
  }


void handle_root() {
  Serial.println();
  server.send(200, "text/plain", collected_sting(poss_data));
  delay(100);
}
 
void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  dht.begin();           // initialize temperature sensor

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", handle_root);
  server.on("/temp", [](){
    getvalues();
    server.send(200, "text/plain", String((int)temp));
    });
  server.on("/humidity", [](){
    getvalues();
    server.send(200, "text/plain", String((int)humidity));
    });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 

void getvalues() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   
    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    // Check if any reads failed and exit early (to try again).
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp = dht.readTemperature();     // Read temperature as C
    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}
