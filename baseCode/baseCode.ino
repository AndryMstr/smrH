#define TEMP A0
void setup() {
  Serial.begin(9600); 
  pinMode(TEMP,INPUT);
}

void loop() {
  int tempvar;
  tempvar = analogRead(TEMP);
  Serial.println(tempvar);
  delay(500);
  }
