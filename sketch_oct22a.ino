/*
  blink detector
  darcy@inventorArtist.com
  http://inventorartist.com/blink-detector/ 
 
  uses LED to detect blinking
  just looks for rising edges

  Modified for iris goggles by Seth Stoothoff  
 
*/

#include <Servo.h>

Servo myservoL;  // create servo object to control a servo
Servo myservoR;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

int ledPin = 13;           // Visualization

int min = 0;
int max = 180;
int top = 20;
int bottom = 40;

int blinkL = 0;             // Blink indicator 0 = none 1 = blink
int sensorPinL  = 0;        // IR Sensor
int lastLevelL = 0;         // Previous IR level
int lastChangeL = 0;        // Change in IR level
int changeThresholdL = 10;  // How hard a rising edge do we need?

int blinkR = 0;             // Blink indicator 0 = none 1 = blink
int sensorPinR  = 1;        // IR Sensor
int lastLevelR = 0;         // Previous IR level
int lastChangeR = 0;        // Change in IR level
int changeThresholdR = 10;  // How hard a rising edge do we need?
 
//visualization
int duration = 100;        // Length of visualization
float lastStart = 0;       // Last start of visualization
int blinkWait = 2000;
int blinkDuration = 400;
float blinkStart = 0;
 
 
void setup() {
  Serial.begin(9600);      // Debug constructor
  pinMode(13, OUTPUT);     // Visualizatio constructor
  myservoL.attach(10);  // attaches the servo on pin 10 to the servo object
  myservoR.attach(11);  // attaches the servo on pin 11 to the servo object
}
 
void loop() {
  int sensorValueL = analogRead(sensorPinL);Serial.println(sensorValueL);  // Read Data
  // look for rising edges
  lastChangeL = sensorValueL - lastLevelL;
  lastLevelL = sensorValueL;
  if ((lastChangeL >=changeThresholdL) && (millis() >= blinkStart + blinkWait)) {
    digitalWrite(ledPin, HIGH);
    lastStart = millis();
    blinkL = 1;
  }
  
  int sensorValueR = analogRead(sensorPinR);Serial.println(sensorValueR);  // Read Data
  // look for rising edges
  lastChangeR = sensorValueR - lastLevelR;
  lastLevelR = sensorValueR;
  if ((lastChangeR >=changeThresholdR) && (millis() >= blinkStart + blinkWait)) {
    digitalWrite(ledPin, HIGH);
    lastStart = millis();
    blinkR = 1;
  }
  if (millis() >= lastStart + duration) {
    digitalWrite(ledPin, LOW);
    blinkL = 0;
    blinkR = 0;
  }

  if ((blinkL > 0 || blinkR > 0) && (millis() >= blinkStart + blinkWait)) {
    myservoL.write(max - bottom);
    myservoR.write(min + bottom);
    blinkStart = millis();
  }

  if (millis() >= blinkStart + blinkDuration) {
    myservoL.write(min + top);
    myservoR.write(max - top);
  }
//    myservoL.write(max - bottom);
//    if (blinkR > 0) {
//      myservoR.write(min + bottom);
//    }
//    delay(400);
//    
//    myservoL.write(min + top);
//    if (blinkR > 0) {
//      myservoR.write(max - top);
//    }
//    delay(2000);
//  }else if (blinkR > 0) {
//    myservoR.write(min + bottom);
//    if (blinkL > 0) {
//      myservoL.write(max - bottom);
//    }
//    delay(400);
//    
//    myservoR.write(max - top);
//    if (blinkL > 0) {
//      myservoL.write(min + top);
//    }
//    delay(2000);
  
  
  //absolute approach
  //if (sensorValueL >=205) {
  //  digitalWrite(13, HIGH);
  //}else{
  //  digitalWrite(13, LOW);
  //}
  //delay(100);
}
