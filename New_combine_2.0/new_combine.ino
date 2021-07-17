//ULTRASONIC SENSOR
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor
int piezoPin = 8;
//TRANSMITTER SENSOR
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 4;

void setup() {
  //TX and RX CODE
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(4, OUTPUT);
   radio.begin();                  //Starting the Wireless communication
   radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
   radio.setPALevel(RF24_PA_MIN);//You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
   radio.startListening(); 
             

   
}
void loop() {
  //ULTRASONIC SENSOR
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
   //rx code
   if (radio.available())              //Looking for the data.
     {
       char text[32] = "";                 //Saving the incoming data
       radio.read(&text, sizeof(text));    //Reading the data
       radio.read(&button_state, sizeof(button_state));    //Reading the data
       if(button_state == HIGH)
     {
       digitalWrite(4, HIGH);
       Serial.println(text);
     }
   else
     {
       digitalWrite(4, LOW);
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
