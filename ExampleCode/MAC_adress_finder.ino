#include "BluetoothSerial.h"
#include "esp_bt_device.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Receiver");  // server mode

  const uint8_t* mac = esp_bt_dev_get_address();
  Serial.print("Receiver MAC: ");
  for (int i = 0; i < 6; i++) {
    if (i != 0) Serial.print(":");
    Serial.printf("%02X", mac[i]);
  }
  Serial.println();
}

void loop() {}