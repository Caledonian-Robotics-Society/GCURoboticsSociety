// Motor driver pins
#define IN1 16  // Motor A input 1
#define IN2 4   // Motor A input 2
#define IN3 23  // Motor B input 1
#define IN4 2   // Motor B input 2
#define ENA 32  // PWM speed control for Motor A
#define ENB 14  // PWM speed control for Motor B

// Ultrasonic sensor pins
const int trigPin = 26;         // Shared trigger pin
const int echoPinFront = 27;    // Echo pin for front sensor
const int echoPinBack = 25;     // Echo pin for back sensor (example GPIO)
const int maxDistance = 77;     // Max valid distance in cm

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(echoPinBack, INPUT);

  Serial.begin(9600); // Serial monitor
}

// Generic function to read distance from specified echo pin
long getDistanceCM(int echoPin) {
  // Trigger a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo from the selected pin
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout = 30ms
  if (duration == 0) return -1; // Timeout or error

  long distance = duration * 0.034 / 2;
  return distance;
}

void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  long frontDist = getDistanceCM(echoPinFront);
  delay(10); // Small gap between sensor reads
  long backDist = getDistanceCM(echoPinBack);

  Serial.print("Front: ");
  Serial.print(frontDist);
  Serial.print(" cm, Back: ");
  Serial.print(backDist);
  Serial.println(" cm");

  // Only move if either sensor detects something close
  if (frontDist > 0 && frontDist <= maxDistance) {
    moveForward(200);
  } else if (backDist > 0 && backDist <= maxDistance) {
    moveBackward(200);
  } else {
    stopMotors();
  }

  delay(100); // Small loop delay
}
