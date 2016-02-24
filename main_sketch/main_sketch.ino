/*
Benjamin Matase, AC Li, Mark (Rick) Moyer, Yash Mittal
20 February, 2016

An arduino C program used to control a robot to navigate a simulated Mars
evironment.

Fun fact, you can't name your sketch main or else the compiler freaks out

Servo setup:   brown-  gnd
               red  -  5v
               yellow- servoPin(9)
               
SharpIR setup:   black- gnd
                 red  - 5v
                 white- ir(A5)
                 
Motor setup:    ask AC

Photores setup:  power- 5v
                 gnd  - gnd
                 output- prPin1(10), prPin2(11)
                 resistors - x ohms
*/

#include <Servo.h>
#include <SharpIR.h>
 
//SERVO
Servo myservo;           // create servo object to control a servo

int servoPos = 90;         // variable to store the servo position
int servoInc = 1;          //which direction to move servo
int servoSpeed = 1;        //how fast to rotate servo
const int servoPin = 9;     //pin to put servo output to
const int servoMax = 179;  //max degrees for servo to move to
const int servoMin = 1;    //min degrees for servo to move to

//SHARP IR
#define ir A5        //Analog pin to connect SharpIR sensor to
#define model 1080    //not sure, ask Yash

SharpIR sharp(ir, 10, 90, model); // creates a distance sensor object

int dis = 0;        //var to hold reading from SharpIR sensor
const int disMax = 20;  //max value of obj to be determined "in way"
const int disMin = 10;  //min value of obj to be determined "in way"

//WHEELS
int wheelTurn = 0; //Magnitude of turn, I guess could be difference of wheels
                   //(- is left and + is right and 0 is straight)
int wheelSpeed = 0;    //speed of actual robots, dependent on wheel

//PHOTORES
const int prLPin = 10;  //pin to hook up left photoresistor to
const int prRPin = 11;  //pin to hook up right photoresistor to
const int black = 100; //to be experimentally determined what is black
const int green = 60;  //same^

 
void setup() 
{ 
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object 
  pinMode(ir, INPUT);
  pinMode(prLPin, INPUT);
  pinMode(prRPin, INPUT);
  Serial.begin(9600);
} 
 
void loop() //might need reordering of handling
{ 
  //do servo things
  handleServo();
  
  //measure distance from sharpIR
  dis = sharp.distance();
  
  //do wheel things
  handleWheels();
  
  //check photoresistors
  handlePhotores();
}

void handleWheels() {
  // collision range
  if(dis >= disMin && dis <= disMax) { 
    //start turning by certain amount NOT CORRECT RN
    wheelTurn = servoPos;
  }
  //TODO figure out
}

void handleServo() {
  //oscillates between servoMax and servoMin
  if(servoPos > servoMax) {
    servoInc = -1;
  } else if(servoPos < servoMin) {
    servoInc = 1;
  }
  
  servoPos += servoInc * servoSpeed;
  myservo.write(servoPos);
}

void handlePhotores() {
  //get values from both.
  int prL = analogRead(prLPin);
  int prR = analogRead(prRPin);
  
  //determine if we hit a line and what angle
  if(prL > black && prR > black) {
    //black for both
  } else if(prL > black && prR <= black) {
    //black for left, white for right
  } else if(prL <= black && prR > black) {
    //white for left, black for right
  } else {
    //white for both 
  }
  
  //if hit line, what do?
  //How know if green?
}
