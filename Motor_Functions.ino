/*
  USING ESP32 DEV MODULE,
  TWIN GEARBOX MOTOR
  L298N H BRIDGE
*/

/*
 L298N H BRIDGE CONTROLS:
 IN1 = LEFT MOTOR BACKWARD
 IN2 = LEFT MOTOR FORWARD
 IN3 = RIGHT MOTOR FORWARD
 IN4 = RIGHT MOTOR BACKWARD

 HIGH = OFF
 LOW = ON
 */
//#include "GyverMotor.h"

// Motor driver pins

#define IN1 16 //analog (27)
#define IN2 4 //analog (26)
#define IN3 23 //analog (25)
#define IN4 2 //analog (33)
int ENA = 32; //speed of M1(14)
int ENB = 14; //speed of M2(32)

//OBJECTS informat "GMotor motor(DRIVER2WIRE, dig_pin, PWM_pin, level)"
//GMotor motor1(DRIVER2WIRE, IN1, IN2, HIGH);
//GMotor motor2(DRIVER2WIRE, IN3, IN4, HIGH);

void moveForward(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)
  
  delay(t);

  if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }
}

void moveBackward(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)

  delay(t);

  if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }
}

void turnRight(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)

  delay(t);

  if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }
}

void turnLeft(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)

  delay(t);

  if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }
}

void Rstop(unsigned int t/*time*/)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  delay(t);
}

void setup() 
{
  //configure motor driver
  //motor1.setMode(FORWARD);
  //motor2.setMode(FORWARD);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 

  // disable motor output by setting all INx pins high
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH); 

  analogWrite(ENA, HIGH);
  analogWrite(ENB, HIGH);
}

void loop() 
{
  //int val_1 = 255 - analogRead(0) / 2;
  //int val_2 = 255 - analogRead(1) / 2;

  moveForward(255, 10000);

}
