#include<SharpIR.h>

#define ir A5
#define model 1080
SharpIR sharp(ir, 25, 90, model);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ir, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

  int dis = sharp.distance();
  Serial.println(dis);
}
