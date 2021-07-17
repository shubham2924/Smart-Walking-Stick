#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int PiezoPin2 = 4;
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor
int LDRvalue = 0;
int LDRpin = A0;
int piezoPin1 = 8;
void setup() {
Serial.begin(115200);
pinMode(PiezoPin2,OUTPUT);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening(); //This sets the module as receiver
}
void loop()
{
if (radio.available())              //Looking for the data.
{
char text[32] = "";                 //Saving the incoming data
radio.read(&text, sizeof(text));    //Reading the data
radio.read(&button_state, sizeof(button_state));    //Reading the data
if(button_state == HIGH)
{
tone(PiezoPin2, 1000, 250);
Serial.println(text);
}
else
{
digitalWrite(PiezoPin2, LOW);
Serial.println(text);}
}
delay(5);
 long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(1000);
   if( cm < 30 )
   {
    tone(piezoPin1, 1000, 250);
    
    if( cm < 15)
      {
        tone(piezoPin1, 2000, 800);
      }

  //tone(piezoPin, 1000, 500);
  
    Serial.println("Yes");
   }
  LDRvalue = analogRead(LDRpin);
  Serial.println(LDRvalue);
  if(LDRvalue<60)
  {
    tone(piezoPin1, 1000, 250);
  }
  delay(100);
 
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
