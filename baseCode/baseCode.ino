#define TEMP A0   //ригистрируем А0 как TEMP 
#define PHRES A1  //ригистрируем А1 как PHRES

void setup() {
  Serial.begin(9600);
  pinMode(TEMP,INPUT);   //модифицируем TEMP как инпут (приём)
  pinMode(PHRES,INPUT);  //модифицируем PHRES как инпут (приём)
}

void loop() {
  
  char coma[2];
  coma[0] = ',';
  coma[1] = ' ';
  int tempvar;  //ригистрируем перименую tempvar
  int light;    //ригистрируем перименую light
  tempvar = analogRead(TEMP);  //вводим в перименую tempvar значение с порта TEMP
  Serial.print(tempvar);       //пичатаем tempvar  в  монитор порта
  Serial.print(coma);
  delay(500);  //ждём 0.5 (половину)сикунды
  light = analogRead(PHRES);//вводим в перименую  light значение с порта PHRES
  Serial.println(light);    //пичатаем  в  монитор порта перименую  light
  }












  //считаваль(копия)
  // Подключение библиотек
#include <SPI.h>
#include <MFRC522.h>
// константы подключения контактов SS и RST
#define RST_PIN 9
#define SS_PIN 10
// Инициализация MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
void setup()
{
Serial.begin(9600); // инициализация последовательного порта
SPI.begin();        // инициализация SPI
mfrc522.PCD_Init(); // инициализация MFRC522
}
void loop()
{
if ( ! mfrc522.PICC_IsNewCardPresent())
return;
// чтение карты
if ( ! mfrc522.PICC_ReadCardSerial())
return;
// показать результат чтения UID и тип метки
Serial.print(F("Card UID:"));
dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
Serial.println();
Serial.print(F("PICC type: "));
byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
Serial.println(mfrc522.PICC_GetTypeName(piccType));
delay(2000);
}
// Вывод результата чтения данных в HEX-виде
void dump_byte_array(byte *buffer, byte bufferSize)
{
for (byte i = 0; i < bufferSize; i++)
{
Serial.print(buffer[i] < 0x10 ? " 0" : " ");
Serial.print(buffer[i], HEX);
}
}











// датчик газа MQ-4;
// контакт подключения аналогового вывода MQ4
const int analogInPin = A1;
const int ledPin = 8; // контакт подключения светодиода
int sensorValue = 0;  // переменная для хранения значения датчика
void setup()
{
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
}
void loop()
{
sensorValue = analogRead(analogInPin); // получить значение
if (sensorValue >= 750)                // превышение уровня
digitalWrite(ledPin, HIGH);            // зажечь светодиод превышения
else
digitalWrite(ledPin, LOW); // потушить светодиод превышения
// вывести значение в последовательный порт
Serial.print("sensor = " );
Serial.println(sensorValue); // пауза перед следующим измерением
delay(1000);
}










//SMS модуль
// подключение библиотеки SoftwareSerial
#include <SoftwareSerial.h>
// номер телефона для отправки sms (поменяйте на свой)
#define PHONE "+79031111111"
// Выводы для SoftwareSerial (у вас могут быть 7,8)
SoftwareSerial Sim900Serial(2, 3);
const int lm335=A0; // для подключения LM335
unsigned long millis1;
void setup()
{
Sim900Serial(19200); // the Hardware serial rate
}
void loop()
{
if (millis()-millis1>30*60*1000) // прошло 30 минут?
{
SendTextMessage(); // отправить sms
millis1=millis();
}
}
// подпрограмма отправки sms
void SendTextMessage()
{
// AT-команда установки text mode
Sim900Serial.print("AT+CMGF=1\r");
delay(100);
// номер телефона получателя
Sim900Serial.println("AT + CMGS = \"");
Sim900Serial.println(PHONE);
Sim900Serial.println("\"");
delay(100);
// сообщение – данные температуры
double val = analogRead(lm335);     // чтение
double voltage = val*5.0/1024;      // перевод в вольты
double temp = voltage*100 - 273.15; // в градусы Цельсия
Sim900Serial.println(temp);
delay(100);
// ASCII код ctrl+z – окончание передачи
Sim900Serial.println((char)26);
delay(100);
Sim900Serial.println();
}









//блютуз модуль
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // указываем пины RX и TX
void setup()
{
pinMode(2,INPUT);
pinMode(3,OUTPUT);
Serial.begin(38400);
mySerial.begin(9600);
}
void loop()
{
if (mySerial.available())
{
int c = mySerial.read(); // читаем из software-порта
Serial.write(c);         // пишем в hardware-порт
}
if (Serial.available())
{
int c = Serial.read(); // читаем из hardware-порта
mySerial.write(c);     // пишем в software-порт
}
}
}
