int LDRvalue = 0;
int LDRpin = A0;
int piezoPin1 = 8;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  LDRvalue = analogRead(LDRpin);
  Serial.println(LDRvalue);
  if(LDRvalue<300)
  {
    tone(piezoPin1, 1000, 250);
  }
  delay(100);
 
}
