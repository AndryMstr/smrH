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
  Serial.print(tempvar);     //пичатаем tempvar  в  монитор порта
  Serial.print(coma);
  delay(500);  //ждём 0.5 (половину)сикунды
  light = analogRead(PHRES);//вводим в перименую  light значение с порта PHRES
  Serial.println(light);//пичатаем  в  монитор порта перименую  light
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
SPI.begin(); // инициализация SPI
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
