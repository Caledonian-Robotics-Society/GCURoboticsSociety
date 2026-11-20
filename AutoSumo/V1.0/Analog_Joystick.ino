//www.elegoo.com
//2016.12.09

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Arduino pin numbers
const int SW_pin = 25; // digital pin connected to switch output
const int X_pin = 32; // analog pin connected to X output
const int Y_pin = 33; // analog pin connected to Y output

const char *receiverName = "ESP32_Receiver";  

void setup() {
  pinMode(SW_pin, INPUT_PULLUP);
  analogReadResolution(10);


  Serial.begin(115200);
  SerialBT.begin("joystick", true);  // Bluetooth device name
  Serial.println("Sender ready. Connect to ESP32_Receiver");

   if (SerialBT.connect(receiverName)) {
    Serial.println("Connected to receiver!");
  } else {

    Serial.println("Failed to connect. Retrying...");
  }
}

void loop() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");

  int x = analogRead(X_pin);
  int y = analogRead(Y_pin);

 if (SerialBT.connected()) {
    String msg = "X=" + String(x) + " Y=" + String(y);

    SerialBT.println(msg);
    Serial.println("Sent: " + msg);
    delay(1000);
  }else {
    Serial.println("Not connected. Retrying...");
    SerialBT.connect(receiverName);   // try again
    delay(2000);
  }
}
