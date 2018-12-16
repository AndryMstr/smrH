#define  LED1  7 //ригистрируем 7 пин как DISPLAI_PIN 
#define  LED2  8//ригистрируем А0 как TEMP 
#define  LED3  9//ригистрируем 8 пин как MOTOR
#define  PHRES1 A1//ригистрируем А1 как PHRES
#define  PHRES2 A0//ригистрируем 13 пин как LED
#define  PHRES3 A2//ригистрируем A2 внешний фоторезистор
int lit1;
int lit2;
int lit3;

void setup() {
  // put your setup code here, to run once:
  pinMode(PHRES1,INPUT); 
  pinMode(PHRES2,INPUT);
  pinMode(PHRES3,INPUT); 
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);  
  
  Serial.begin(9600);

}

void loop() {

    
  lit1 = analogRead(PHRES1);
  lit2= analogRead(PHRES2);
  lit3= analogRead(PHRES3);

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
  if (lit1<200){digitalWrite(LED1,HIGH);} // TODO изменить границы.
  if (lit1>200){digitalWrite(LED1,LOW);}  
}
