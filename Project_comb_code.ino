//ULTRASONIC CODE:

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor
int piezoPin = 8;

//LDR CODE:

int LDRvalue = 0;
int LDRpin = A0;


//TRANSMITTER CODE:

//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//RF24 radio(9, 10); // CE, CSN         
//const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
//int button_pin = 2;
//boolean button_state = 0;

//RECEIVER CODE:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 6;


void setup() {
   //ULTRASONIC CODE:
   Serial.begin(9600); // Starting Serial Terminal

   //TRANSMITTER CODE:

   //pinMode(button_pin, INPUT);
//radio.begin();                  //Starting the Wireless communication
//radio.openWritingPipe(address); //Setting the address where we will send the data
//radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
//radio.stopListening();//This sets the module as transmitter

//RECEIVER CODE:

pinMode(6, OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver


}


void loop() {
  //ULTRASONIC CODE : 
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
    tone(piezoPin, 1000, 250);
    
    if( cm < 15)
      {
        tone(piezoPin, 2000, 800);
      }

  //tone(piezoPin, 1000, 500);
  
    Serial.println("Yes");
   }

   //LDR CODE:

   LDRvalue = analogRead(LDRpin);
  Serial.println(LDRvalue);
  if(LDRvalue<5)
  {
    tone(piezoPin, 1000, 250);
  }
  delay(100);

  //TRANSMITTER CODE:

  //button_state = digitalRead(button_pin);
//if(button_state == HIGH)
//{
//const char text[] = "Your Button State is HIGH";
//radio.write(&text, sizeof(text));                  //Sending the message to receiver
//}
//else
//{
//const char text[] = "Your Button State is LOW";
//radio.write(&text, sizeof(text));                  //Sending the message to receiver 
//}
//radio.write(&button_state, sizeof(button_state));  //Sending the message to receiver 
//delay(1000);

//RECEIVER CODE:

if (radio.available())              //Looking for the data.
{
char text[32] = "";                 //Saving the incoming data
radio.read(&text, sizeof(text));    //Reading the data
radio.read(&button_state, sizeof(button_state));    //Reading the data
if(button_state == HIGH)
{
digitalWrite(6, HIGH);
Serial.println(text);
}
else
{
digitalWrite(6, LOW);
Serial.println(text);}
}
delay(5);


}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
