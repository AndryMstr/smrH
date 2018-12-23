#define  LED1  7 //ригистрируем 7 пин как LED1 (светодиод1)
#define  LED2  8//ригистрируем 8 как LED2 (светодиод2)
#define  LED3  9//ригистрируем 9 пин как LED3 (светодиод3)
#define  PHRES1 A1//ригистрируем А1 как PHRES
#define  PHRES2 A0//ригистрируем А0 пин как PHRES2 (внутрений фоторезистор)
#define  PHRES3 A2//ригистрируем A2 как PHRES3 внешний фоторезистор
int lit1;//ригистрируем переменую lit1
int lit2;//ригистрируем переменую lit2
int lit3;//ригистрируем переменую lit3

void setup() {
  // put your setup code here, to run once:
  pinMode(PHRES1,INPUT);//модифицируем пин PHRES1 (А1) как инпут (пин для приёма) 
  pinMode(PHRES2,INPUT);//модифицируем пин PHRES2 (А0) как инпут (пин для приёма) 
  pinMode(PHRES3,INPUT);//модифицируем пин PHRES3 (А2) как инпут (пин для приёма) 
  pinMode(LED1, OUTPUT);//модифицируем пин LED1 (7)как аутпут()
  pinMode(LED2, OUTPUT);//модифицируем пин LED2 (8)как аутпут()
  pinMode(LED3, OUTPUT);//модифицируем пин LED3 (9)как аутпут()  
  
  Serial.begin(9600);//настраеваем монитор порта на 9600 бод

}

void loop() {

    
  lit1 = analogRead(PHRES1);//вводим в переменую lit1 значение с пина PHRES1 (А1)
  lit2= analogRead(PHRES2);//вводим в переменую lit2 значение с пина PHRES2 (А0)
  lit3= analogRead(PHRES3);//вводим в переменую lit3 значение с пина PHRES3 (А2)

//  Serial.print(lit1);
//  Serial.print(' ');  
  Serial.println(lit2);
  //  Serial.print(' ');
  // Serial.println(lit3);
  //digitalWrite(LED1,lit1);
  delay(500);
// проверяем освещение снаружи
  if (lit3<200){
    digitalWrite(LED2,HIGH);
    digitalWrite(LED1,HIGH);}
  if (lit3>200){
    digitalWrite(LED2,LOW);
    digitalWrite(LED1,LOW);}
  // проверяем освещение  в комнатах 
  // дальняя комната
  if (lit2<200){digitalWrite(LED2,HIGH);}
  if (lit2>200){digitalWrite(LED2,LOW);}  
  //Ближняя комната
  if (lit1<200){digitalWrite(LED1,HIGH);} // TODO изменить границы.НЕ НАДО
  if (lit1>200){digitalWrite(LED1,LOW);}  
}
