/*
Benjamin Matase, AC Li, Mark (Rick) Moyer, Yash Mittal
20 February, 2016

An arduino C program used to control a robot to navigate a simulated Mars
evironment.

Fun fact, you can't name your sketch main or else the compiler freaks out

Pin key;
2- Wheels
3- Wheels
4- Wheels
5- Wheels
6- Wheels
7- Wheels
9 - Servo
A2- pr
A3- pr
A5- IR


Servo setup:   brown-  gnd
               red  -  5v
               yellow- servoPin(9)
               
SharpIR setup:   black- gnd
                 red  - 5v
                 white- ir(A5)
                 
Motor setup:    motor

Photores setup:  power- 5v
                 gnd  - gnd
                 output- prPin1(10), prPin2(11)
                 resistors - 10 kohms
*/

#include <Servo.h>
#include <SharpIR.h>

enum state{
  FIND_A_WALL,
  HUG_WALL,
  FIND_THE_WALL
};

//SERVO
Servo myservo;           // create servo object to control a servo

int servoPos = 90;         // variable to store the servo position
int servoInc = 1;          //which direction to move servo
int servoSpeed = 1;        //how fast to rotate servo
const int servoPin = 9;     //pin to put servo output to
const int servoMax = 129;  //max degrees for servo to move to
const int servoMin = 39;    //min degrees for servo to move to

//SHARP IR
#define ir A5        //Analog pin to connect SharpIR sensor to
#define model 1080    //not sure, ask Yash

SharpIR sharp(ir, 10, 90, model); // creates a distance sensor object

int dis = 0;        //var to hold reading from SharpIR sensor
const int disMax = 20;  //max value of obj to be determined "in way"
const int disMin = 10;  //min value of obj to be determined "in way"

//WHEELS
//left motor
const int speedR = 7;    //speed pin for left motor (ENA)
const int enRForPin = 6;   //enable left forward pin (IN2)
  const int enRRevPin = 5;   //enable left forward pin (IN1)
//right motor
const int speedL = 4;    //speed pin for right motor (ENB)
const int enLForPin = 2;   //controller pin 1 for right motor (IN4)
const int enLRevPin = 3;   //controller pin 2 for right motor (IN3)
const int SpeedL = 250; // Default speed
const int SpeedR = 200;

int wheelTurn = 0; //Magnitude of turn, I guess could be difference of wheels
                   //(- is left and + is right and 0 is straight)
int wheelSpeed = 0;    //speed of actual robots, dependent on wheel (0-255)

//PHOTORES
#define prLPin A3        //Analog pin for right photoresisotr
#define prRPin A2        //Analog pin for left photoresistor
const int black = 100; //to be experimentally determined what is black
const int green = 60;  //same^
const int ledPin = 12;  //pin for the led
<<<<<<< HEAD:main_sketch/main_sketch_AC.ino
=======

//MISC
enum state {
  FIND_WALL,
  HUG_WALL,
  ROCK,
  
};
>>>>>>> origin/master:main_sketch/main_sketch.ino

//MISC
enum state {
  FIND_WALL,
  HUG_WALL,
  ROCK,
  
};

int count = 0;

state currState = FIND_A_WALL;
 
void setup() 
{ 
  //Servo
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object 
  
  //SharpIR
  pinMode(ir, INPUT);
  
  //PhotoRes
  pinMode(prLPin, INPUT);
  pinMode(prRPin, INPUT);
  
  //Wheels
  pinMode(speedL, OUTPUT);
  pinMode(enLForPin, OUTPUT);
  pinMode(enLRevPin, OUTPUT);
  pinMode(speedR, OUTPUT);
  pinMode(enRForPin, OUTPUT);
  pinMode(enRRevPin, OUTPUT);

  //Serial
  Serial.begin(9600);
} 
 
void loop() //might need reordering of handling
{ 
  //do servo things
  handleServo();
  dis = 0;
  //measure distance from sharpIR
  dis = sharp.distance();
  Serial.println(dis);
<<<<<<< HEAD:main_sketch/main_sketch_AC.ino
<<<<<<< HEAD
//  if (dis < 30 && dis > 20) {
//    if(count == 3) {
//      moveLeft();
//      delay(2000);
//    } else {
//      count++;
//    }
//    return;
//  } 

    if (sharp.distance() > 30) {
      moveForward();
      return;
    } else {
      moveLeft();
      delay(1000);
      return;
  }
=======
=======
>>>>>>> origin/master:main_sketch/main_sketch.ino
  
  //do wheel things
  handleWheels();
>>>>>>> origin/master
  
  //check photoresistors
  //handlePhotores();
}

void handleWheels() {
  if (dis > 30) {
    moveForward();
    return;
  } else {
    moveLeft();
    delay(250);
    return;
  }
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
//  Serial.print(prL);
//  Serial.print(":");
//  Serial.println(prR);
  
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

void moveForward() {
  analogWrite(speedL, SpeedL);
  analogWrite(speedR, SpeedR);
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
}

void moveBackward() {
  analogWrite(speedL, SpeedL);
  analogWrite(speedR, SpeedR);
  digitalWrite(enLForPin, LOW);
  digitalWrite(enLRevPin, HIGH);
  digitalWrite(enRForPin, LOW);
  digitalWrite(enRRevPin, HIGH);
}

void moveRight() {
  analogWrite(speedL, SpeedL);
  analogWrite(speedR, SpeedR);
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
  digitalWrite(enLForPin, LOW);
  digitalWrite(enLRevPin, HIGH);
}

void moveLeft() {
  analogWrite(speedL, SpeedL);
  analogWrite(speedR, SpeedR);
  digitalWrite(enRForPin, LOW);
  digitalWrite(enRRevPin, HIGH);
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
}

void moveStop() {
  digitalWrite(speedL, LOW);
  digitalWrite(speedR, LOW);
}

void quarterRight() {
  moveRight();
  delay(220);
}

void quarterLeft() {
  moveLeft();
  delay(250);
}

void turnaroundL() {
  moveLeft();
  delay(1000);
}

void turnaroundR() {
  moveRight();
  delay(1000);
}

boolean isRockAhead() {
  if (dis > 45) {
    return false;
  }
  return true;
}


