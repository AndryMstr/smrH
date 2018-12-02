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
