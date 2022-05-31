/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep

 modified again 25 Mar 2022
 by Rob8136
 This does not rely on delay and is better at multitasking than the previous versionb 
*/

#include <Servo.h>
#define echoPin 8  // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
unsigned long int lastPingTime = 0;
unsigned long int lastPingTimeMicros = 0;
unsigned long int lastServoMoveTime = 0;
const int servoDelay = 15;
bool increasingAngle = true;
// defines variables for dist
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
bool sendPing = false;
int pings = 3;
int distanceAvg = 0;


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);   // go to initial position
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT for ultrasonic
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

void loop() {
  lastPingTime = millis();   // update time
  if(lastPingTime - lastServoMoveTime >= servoDelay){    //If servo delay time is up
    if(increasingAngle == true){    //increase or decrease position angle based on direction set by increasingAngle
      pos ++;
      sendPing = true;
      digitalWrite(trigPin, LOW);
      lastPingTimeMicros = micros();
    }
    if(increasingAngle == false){
      pos --;
      sendPing = true;
      digitalWrite(trigPin, LOW);
      lastPingTimeMicros = micros();
    }
    if(pos >= 180 && increasingAngle == true){
      increasingAngle = false;    //Far enough, change direction
    }
    if(pos <= 0 && increasingAngle == false){
      increasingAngle = true;    //Far enough, change direction
    }
    myservo.write(pos);   //move servo to updated position
    lastServoMoveTime = millis();
  }
  //send pulse once a movement
  if(micros() - lastPingTimeMicros >= 2 && sendPing == true){
    distanceAvg = 0;
    for(int i = 0; i < pings; i ++){
      if(i > 1){
        delayMicroseconds(2);   
      }
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      distanceAvg += distance;
    }
    distanceAvg = distanceAvg / pings;
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distanceAvg);
    Serial.println(" cm");
    sendPing = false;
  }
  // Clears the trigPin condition 
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  //duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
}
