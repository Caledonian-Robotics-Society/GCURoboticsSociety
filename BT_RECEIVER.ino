#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define MSG_BUFFER_SIZE 128
char incoming[MSG_BUFFER_SIZE];
int idx = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Receiver");  // Receiver = server
  Serial.println("Receiver ready. Waiting for data...");
}

void loop() {
  while (SerialBT.available()) {
    char c = SerialBT.read();

    if (c == '\n') {  // end of message
      incoming[idx] = '\0';  // terminate string

      Serial.print("Raw message: ");
      Serial.println(incoming);

      // Parse values from incoming string
      int sw = -1, x = -1, y = -1;
      if (sscanf(incoming, "SW=%d X=%d Y=%d", &sw, &x, &y) == 3) {
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
        // prevent overflow
        idx = 0;
      }
    }
  }
}
