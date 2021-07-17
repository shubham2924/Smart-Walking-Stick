const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor
const int piezoPin1 = 8;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
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
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
