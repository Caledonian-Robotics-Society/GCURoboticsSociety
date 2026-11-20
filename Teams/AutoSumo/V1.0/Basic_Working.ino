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

// Motor driver pins

#define IN1 16 //analog (27)
#define IN2 4 //analog (26)
#define IN3 23 //analog (25)
#define IN4 2 //analog (33)
int ENA = 32; //speed of M1(14)
int ENB = 14; //speed of M2(32)


void moveForward(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)
  
  delay(t);

  
}

void moveBackward(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)

  delay(t);

  
}

void turnRight(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

    if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)

  delay(t);


}

void turnLeft(unsigned int v/*speed*/, unsigned int t/*time*/)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

    if(v > 255)
  {
    v = 255;
  }
  if(t > 4294967295)
  {
    t = 4294967295;
  }

  analogWrite(ENA, v);  //motor 1 speed (max of 255)
  analogWrite(ENB, v);  //motor 2 speed (max of 255)

  delay(t);


}

void rStop(unsigned int t/*time*/)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

  delay(t);
}
//Ultrasonic Sensor Code with Averaging & Change Detection */

const int trigPins[] = {26, 3};  // Array for Trigger Pins [Front, Back]
const int echoPins[] = {27, 2};  // Array for Echo Pins [Front, Back]

const int maxDistance = 77; // Max detection distance in cm

#define SOUND_SPEED 0.034 // Speed of sound in cm/µs

long duration[2];
int distanceCm[2][2];  // Stores last two readings for averaging
//int avgFDistance = 0;
//int avgBDistance = 0;
int lastPrintedAvg[2] = {-1, -1};  // Stores last printed average values

void ultraSonics()
{
  
        for (int i = 0; i < 2; i++) {
    // **Trigger the sensor**
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
  
    // **Read Echo Pin**
    duration[i] = pulseIn(echoPins[i], HIGH);

    if(distanceCm[i][1] > 77)
    {
      distanceCm[i][1] = 77;
    }
    
    // **Shift old reading to index 1 and store new reading at index 0**
    distanceCm[i][1] = distanceCm[i][0];
    distanceCm[i][0] = (duration[i] * SOUND_SPEED) / 2;

    // **Calculate Average of Last Two Readings**
    int avgDistance = (distanceCm[i][0] + distanceCm[i][1]) / 2.0;

    //if(i == 0) avgFDistance = avgDistance;
    //else if(i == 1) avgBDistance = avgDistance;
    // **Print only if the average changes**
    if (avgDistance != lastPrintedAvg[i]) {
      if (avgDistance <= maxDistance) {
        Serial.print(i == 0 ? "Front Average Distance (cm): " : "Back Average Distance (cm): ");
        Serial.println(avgDistance);
      } else {
        Serial.println(i == 0 ? "Front Average Distance: Out of Range" : "Back Average Distance: Out of Range");
      }
      lastPrintedAvg[i] = avgDistance;  // Update last printed value
    }

  

  delay(10); // Short delay before next reading
  }
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

  Serial.begin(19200); // Serial communication

  for (int i = 0; i < 2; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

    

}

void loop() 
{
  
  int val_1 = 255 - analogRead(0) / 2;
  int val_2 = 255 - analogRead(1) / 2;

  ultraSonics();

  if(lastPrintedAvg[0] < 70)
  {
    moveForward(255, 100);
  }
  else{
    rStop(1);
  }

}