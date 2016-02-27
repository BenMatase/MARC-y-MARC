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

#define COLL_DIST 20 // Set maximum distance to avoid collision
#define TURN_DIST COLL_DIST+10 // Sets maximum distance to turn 
#define MAX_SPEED 200
#define MAX_SPEED_OFFSET 10              

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
int disMax = 0;  //max value of obj to be determined "in way"
int angMax = 0;  //max value of angle to be determined "in way"
int rightMax = 0;
int leftMax = 0;
int frontMax = 0;
int course = 0;
int pos = 0;
int speedSet = 0;

//WHEELS
//left motor
const int speedR = 7;    //speed pin for left motor (ENA)
const int enRForPin = 6;   //enable left forward pin (IN2)
  const int enRRevPin = 5;   //enable left forward pin (IN1)
//right motor
const int speedL = 4;    //speed pin for right motor (ENB)
const int enLForPin = 2;   //controller pin 1 for right motor (IN4)
const int enLRevPin = 3;   //controller pin 2 for right motor (IN3)
const int SpeedL = 230; // Default speed
const int SpeedR = 230;

//PHOTORES
#define prLPin A3        //Analog pin for right photoresisotr
#define prRPin A2        //Analog pin for left photoresistor
const int black = 700; // black left < 520, right < 650
const int green = 700;  //same^ 690 - 770
// white is > 830
const int ledPin = 12;  //pin for the led
 
void setup() 
{  
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
  //Servo
   myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object
   myservo.write(90); // tells the servo to face forward
   delay(2000); // delay for 2 seconds
   checkPath(); // Find the best path to travel
   myservo.write(90); // make sure facing forward
   moveForward(); // move forward
} 
 
void loop() //might need reordering of handling
{ 
  
   checkPath();
  //check photoresistors
//  Serial.println(isBlack);
   moveForward();
}

void checkPath() {
  int curLeft = 0;
  int curFront = 0;
  int curRight = 0;
  int curDist = 0;
  boolean isBlack = handlePhotores();
  if (isBlack) {
    moveStop();
    delay(500);
    moveBackward();
    delay(500);
    turnaround();
  }
    curDist = sharp.distance();
    int counter;
    for (counter = 0; counter < 5; counter++) {
      curDist = sharp.distan
    }
    
    Serial.println(curDist);
    if (curDist < COLL_DIST){
      checkCourse(); 
    }
    if (curDist < TURN_DIST) { // If cannot turn
    	changePath();
    }
    if (curDist > COLL_DIST || curDist < 0) {
    	angMax = pos;
    }
    if (curDist > curLeft && pos > 90) {
    	curLeft = curDist;
    }
    if (curDist > curFront && pos == 90) {
    	curFront = curDist;
    }
    if (curDist > curRight && pos < 90) {
    	curRight = curDist;
    }
    leftMax = curLeft;
    rightMax = curRight;
    frontMax = curFront;
}

void setCourse() { // Sets direction
	if (angMax < 90) {
		moveRight();
	} 
	if (angMax > 90) {
		moveLeft();
	}
	leftMax = 0;
	rightMax = 0;
	frontMax = 0;
}

void checkCourse() {
	moveBackward();
  delay(500);
	moveStop();
	setCourse();
}

void changePath() {
	if (pos < 90) {
		veerLeft();
	}
	if (pos > 90) {
		veerRight();
	}
}

// void handleServo() {
//   //oscillates between servoMax and servoMin
//   if(servoPos > servoMax) {
//     servoInc = -1;
//   } else if(servoPos < servoMin) {
//     servoInc = 1;
//   }
  
//   servoPos += servoInc * servoSpeed;
//   myservo.write(servoPos);
// }

boolean handlePhotores() {
  //get values from both.
  int prL = analogRead(prLPin);
  int prR = analogRead(prRPin);
//  Serial.print(prL);
//  Serial.print(":");
//  Serial.println(prR);
  
  //determine if we hit a line and what angle
  if(prL < 400  || prR < 600) {
    return true;
  } else {
    return false;
  }
//  } else if(prL > black && prR <= black) {
//    //black for left, white for right
//  } else if(prL <= black && prR > black) {
//    //white for left, black for right
//  } else {
//    //white for both 
//  }
  
  //if hit line, what do?
  //How know if green?
}

void moveForward() {
	// Make left and right motors go forward
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
  // slowly speed up both motors
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
  	analogWrite(speedL, speedSet + MAX_SPEED_OFFSET);
  	analogWrite(speedR, speedSet);
  	delay(5);
  }
}

void moveBackward() {
  // Make both motors rotate backward
  digitalWrite(enLForPin, LOW);
  digitalWrite(enLRevPin, HIGH);
  digitalWrite(enRForPin, LOW);
  digitalWrite(enRRevPin, HIGH);
  // slowly speed up
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
  	analogWrite(speedL, speedSet + MAX_SPEED_OFFSET);
  	analogWrite(speedR, speedSet);
  	delay(5);
  }
}

void moveRight() {
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
  digitalWrite(enLForPin, LOW);
  digitalWrite(enLRevPin, HIGH);
  analogWrite(speedL, 180);
  analogWrite(speedR, 210);
  delay(400);
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
}

void moveLeft() {
  digitalWrite(enRForPin, LOW);
  digitalWrite(enRRevPin, HIGH);
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
  analogWrite(speedL, 180);
  analogWrite(speedR, 210);
  delay(400);
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
}

void moveStop() {
  digitalWrite(speedL, LOW);
  digitalWrite(speedR, LOW);
  digitalWrite(enLForPin, LOW);
  digitalWrite(enLRevPin, LOW);
  digitalWrite(enRForPin, LOW);
  digitalWrite(enRRevPin, LOW);
}

void veerRight() {
	digitalWrite(enRForPin, LOW);
  digitalWrite(enRRevPin, HIGH);
  analogWrite(speedR, 180);
  delay(400);
  digitalWrite(enRForPin, HIGH);
  digitalWrite(enRRevPin, LOW);
  analogWrite(speedR, 180);
}

void veerLeft() {
	digitalWrite(enLForPin, LOW);
  digitalWrite(enLRevPin, HIGH);
  delay(400);
  digitalWrite(enLForPin, HIGH);
  digitalWrite(enLRevPin, LOW);
}

void turnaround() {
  moveLeft();
  delay(1000);
}


