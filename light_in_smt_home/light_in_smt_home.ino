//#include "WebServer"
#include "DHT.h"
#define COLD 5  // пин для подключения охлаждения
#define WARM 6  // пин для подключения обогревателя
#define HALL_LIGHT 7  //регистрируем 7 пин как HALL_LIGHT освещение гостинной
#define ROOM_LIGHT 8  //регистрируем 8 как ROOM_LIGHT освещение комнаты
#define SIGNALISATION 9  // регистрируем новый пин для сигнализации

#define ROOM_PHRES A0  //регистрируем А0 пин как ROOM_PHRES фоторезистор комнаты
#define HALL_PHRES A1  //регистрируем А1 как HALL_PHRES фоторезистор гостинной
#define EXTERNAL_PHRES A2  //регистрируем A2 как EXTERNAL_PHRES внешний фоторезистор
#define TERMO A3  // пин подключения датчика температуры
#define IR_HALL A4  // пин для подключения IR датчика

#define DHTTYPE DHT11
//const int analogInPin = A4;



DHT dht(TERMO, DHTTYPE);
int lightHall;  // регистрируем переменую lightHall для хранения освещенности в Hall
int lightRoom;  // регистрируем переменую lightRoom для хранения освещенности в Room
int lightExternal;  // регистрируем переменую lightExternal для хранения освещенности снаружи
int temp;  //регистрируем переменую temp
int gas = 0;  // регистрируем переменную с газом

void setup() {
  pinMode(HALL_PHRES,INPUT);  // модифицируем пин HALL_PHRES (А1) как инпут (пин для приёма) 
  pinMode(ROOM_PHRES,INPUT);  // модифицируем пин ROOM_PHRES (А0) как инпут (пин для приёма) 
  pinMode(EXTERNAL_PHRES,INPUT);  // модифицируем пин EXTERNAL_PHRES (А2) как инпут (пин для приёма) 
  pinMode(IR_HALL, INPUT);

  pinMode(SIGNALISATION, OUTPUT);  // 
  pinMode(HALL_LIGHT, OUTPUT);  // модифицируем пин HALL_LIGHT (7)как аутпут()
  pinMode(ROOM_LIGHT, OUTPUT);  // модифицируем пин ROOM_LIGHT (8)как аутпут()
  pinMode(WARM, OUTPUT);  // модифицируем пин WARM (6)как аутпут()
  pinMode(COLD, OUTPUT);  // модифицируем пин COLD (5)как аутпут() 
  
  dht.begin();
  Serial.begin(9600);  // настраеваем монитор порта на 9600 бод
}

void loop() {

    
  lightHall = analogRead(HALL_PHRES);  // сохраняем в переменую lightHall значение считанное с пина HALL_PHRES (А1)
  lightRoom= analogRead(ROOM_PHRES);  // сохраняем в переменую lightRoom значение считанное с пина ROOM_PHRES (А0)
  lightExternal= analogRead(EXTERNAL_PHRES);  // сохраняем в переменую lightExternal значение считанное с пина EXTERNAL_PHRES (А2)
  irhall = analogRead(IR_HALL);  // сохраняем в переменную значение считанное с ИК датчика

  // Условие присутствия
  if (irhall< 10){
    
  }
  
  temp= dht.readTemperature();  // сохраняем в переменную temp показания температуры считанное с DHT датчика
  
  Serial.println( gas);  // печатаем в монитор порта переменую

  
  
  // Условие для включения/выключения света в Hall
  // Темно в комнате
  if (lightHall<=200) digitalWrite(HALL_LIGHT,HIGH);
  // В противном случае свет в комнате надо погасить
  else digitalWrite(HALL_LIGHT,LOW);
  
  // Условие для включения/выключения света в Room
  // Темно в комнате
  if (lightRoom<=200) digitalWrite(ROOM_LIGHT,HIGH);
  // В противном случае свет в комнате надо погасить
  else digitalWrite(ROOM_LIGHT,LOW); 

  // условие для включения нагревания и выключения охлаждения
  if (temp<21){
    digitalWrite(WARM, HIGH);  // TODO
    digitalWrite(COLD,LOW);
    }  // TODO
// условие для выключения нагревания и охлаждения
  else if (temp>=21 && temp<25) {
    digitalWrite(COLD,LOW);// TODO
    digitalWrite(WARM,LOW);}// TODO
// условие для выключения нагревателя и включения охлажения
  else:{
    digitalWrite(COLD,LOW);// TODO
    digitalWrite(WARM,LOW);}// TODO
  

  delay(500);  // ждём 0.5 сeкунд
}
