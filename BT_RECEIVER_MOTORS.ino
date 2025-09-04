#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define MSG_BUFFER_SIZE 128
char incoming[MSG_BUFFER_SIZE];
int idx = 0;

//Robot state
bool autonomousMode = false;   // start in controlled mode
int lastSW = 1;                // joystick button (assume pull-up → released = 1)

// Parsed joystick data
int sw = -1, x = -1, y = -1;

//  ===============================
//   Stub functions for behaviour
//  ===============================
  void runControlled(int rawX, int rawY) {
  // Normalise input (0–1023) → 0.0–1.0
  float X_in = rawX / 1023.0;
  float Y_in = rawY / 1023.0;

  float X_deadzone = 0.05;  // 5% deadzone for X axis
  float Y_deadzone = 0.05;  // 5% deadzone for Y axis

  float X_out, Y_out;

  // --- X axis with deadzone ---
  if (X_in < 0.5 - X_deadzone) {
    // Below lower deadzone: line from (0, -1) to (0.5-dz, 0)
    float slope = -1.0 / (0.5 - X_deadzone);
    X_out = slope * X_in;
  } else if (X_in <= 0.5 + X_deadzone) {
    // Inside deadzone
    X_out = 0.0;
  } else {
    // Above upper deadzone: line from (0.5+dz, 0) to (1, +1)
    float slope = 1.0 / (0.5 - X_deadzone);
    X_out = slope * (X_in - (0.5 + X_deadzone));
  }

  // --- Y axis with deadzone ---
  if (Y_in < 0.5 - Y_deadzone) {
    float slope = -1.0 / (0.5 - Y_deadzone);
    Y_out = slope * Y_in;
  } else if (Y_in <= 0.5 + Y_deadzone) {
    Y_out = 0.0;
  } else {
    float slope = 1.0 / (0.5 - Y_deadzone);
    Y_out = slope * (Y_in - (0.5 + Y_deadzone));
  }

  // Motor mixing (no /2, full power preserved)
  float leftMotor_PWM  = X_out + Y_out;
  float rightMotor_PWM = X_out - Y_out;

  // Clamp outputs to -1..+1
  if (leftMotor_PWM > 1) leftMotor_PWM = 1;
  if (leftMotor_PWM < -1) leftMotor_PWM = -1;
  if (rightMotor_PWM > 1) rightMotor_PWM = 1;
  if (rightMotor_PWM < -1) rightMotor_PWM = -1;

  // Debug output
  Serial.print("Joystick raw: X=");
  Serial.print(rawX);
  Serial.print(" Y=");
  Serial.print(rawY);
  Serial.print(" | Normalised: X=");
  Serial.print(X_out, 2);
  Serial.print(" Y=");
  Serial.print(Y_out, 2);
  Serial.print(" | Motors -> L=");
  Serial.print(leftMotor_PWM, 2);
  Serial.print(" R=");
  Serial.println(rightMotor_PWM, 2);

  // TODO: map leftMotor_PWM, rightMotor_PWM (range -1 to 1) → PWM duty cycle
}

  void runAutonomous() {
    // Replace with autonomous navigation logic
    Serial.println("Autonomous mode → ignoring joystick, running AI...");
  }


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Receiver");  // Receiver = server
  Serial.println("Receiver ready. Waiting for data...");
}

void loop() {
  //Handle incoming Bluetooth data
  while (SerialBT.available()) {
    char c = SerialBT.read();

    if (c == '\n') {  // end of message
      incoming[idx] = '\0';  // terminate string

      if (sscanf(incoming, "SW=%d X=%d Y=%d", &sw, &x, &y) == 3) {
        // Detect toggle on button press (falling edge: 1 → 0)
        if (lastSW == 1 && sw == 0) {
          autonomousMode = !autonomousMode;
          Serial.print("Mode toggled: ");
          Serial.println(autonomousMode ? "AUTONOMOUS" : "CONTROLLED");
        }
        lastSW = sw;

        // Print parsed data for debugging
        Serial.print("Parsed -> SW: ");
        Serial.print(sw);
        Serial.print("  X: ");
        Serial.print(x);
        Serial.print("  Y: ");
        Serial.println(y);

      } else {
        Serial.println("Failed to parse message");
      }

      idx = 0;  // reset buffer
    } else {
      if (idx < MSG_BUFFER_SIZE - 1) {
        incoming[idx++] = c;
      } else {
        idx = 0;  // prevent overflow
      }
    }
  }

//  ===============================
//   Stub functions for behaviour
//  ===============================
/*  void runControlled(int rawX, int rawY) {
  // Normalise input (0–1023) → 0.0–1.0
  float X_in = rawX / 1023.0;
  float Y_in = rawY / 1023.0;

  // Apply transformation
  float X_out = 2 * X_in - 1;  // forward/backward
  float Y_out = 2 * Y_in - 1;  // left/right

  // Motor mixing
  float leftMotor_PWM  = X_out + Y_out;
  float rightMotor_PWM = X_out - Y_out;

  // Clamp outputs to -1..+1
  if (leftMotor_PWM > 1) leftMotor_PWM = 1;
  if (leftMotor_PWM < -1) leftMotor_PWM = -1;
  if (rightMotor_PWM > 1) rightMotor_PWM = 1;
  if (rightMotor_PWM < -1) rightMotor_PWM = -1;

  // Debug output
  Serial.print("Joystick raw: X=");
  Serial.print(rawX);
  Serial.print(" Y=");
  Serial.print(rawY);
  Serial.print(" | Normalised: X=");
  Serial.print(X_out, 2);
  Serial.print(" Y=");
  Serial.print(Y_out, 2);
  Serial.print(" | Motors -> L=");
  Serial.print(leftMotor_PWM, 2);
  Serial.print(" R=");
  Serial.println(rightMotor_PWM, 2);

  // TODO: map leftMotor_PWM, rightMotor_PWM (range -1 to 1) → PWM duty cycle
}

  void runAutonomous() {
    // Replace with autonomous navigation logic
    Serial.println("Autonomous mode → ignoring joystick, running AI...");
  }
*/
}
