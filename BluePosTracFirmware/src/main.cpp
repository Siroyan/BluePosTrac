#include <Arduino.h>
#include <bluefruit.h>

#define MANUFACTURER_ID   0x0059

uint8_t beaconUuid[16] = {
  0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78,
  0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0
};

BLEBeacon beacon(beaconUuid, 0x0102, 0x0304, -54);

void startAdv(void) {  
  Bluefruit.Advertising.setBeacon(beacon);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void setup() {
  Serial.begin(115200);
  while ( !Serial ) delay(10);
  Serial.println("Bluefruit52 Beacon Example");
  Serial.println("--------------------------\n");
  Bluefruit.begin();
  Bluefruit.autoConnLed(false);
  Bluefruit.setTxPower(0);    // Check bluefruit.h for supported values
  beacon.setManufacturer(MANUFACTURER_ID);
  startAdv();
  Serial.println("Broadcasting beacon, open your beacon app to test");
  suspendLoop();
}

void loop() {}