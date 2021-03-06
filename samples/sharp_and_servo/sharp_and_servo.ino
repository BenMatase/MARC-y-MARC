/*
Benjamin Matase, AC Li, Mark (Rick) Moyer, Yash Mittal
20 February, 2016

An arduino C program used to control a robot to navigate a simulated Mars
evironment.

Servo setup:   brown-  gnd
               red  -  5v
               yellow- servoPin
*/

#include <Servo.h>
#include <SharpIR.h>

#define ir A5
#define model 1080

SharpIR sharp(ir, 10, 90, model); // creates a distance sensor object
Servo myservo; // create servo object to control a servo
 
int servoPos = 90; // variable to store the servo position
int servoInc = 1;
int servoPin = 9; //pin to put servo output to
int dis = 0;

int turnAmt = 0; //How much 
 
void setup() 
{ 
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object 
  pinMode(ir, INPUT);
  Serial.begin(9600);
} 
 
void loop() 
{ 
  if(servoPos > 179) {
    servoInc = -1;
  } else if(servoPos < 1) {
    servoInc = 1;
  }
  servoPos += servoInc;
  myservo.write(servoPos);
  
  dis = sharp.distance(); 
}
