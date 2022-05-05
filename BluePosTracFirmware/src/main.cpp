#include <Arduino.h>
#include <bluefruit.h>

void startAdv(void) {   
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.setType(BLE_GAP_ADV_TYPE_NONCONNECTABLE_SCANNABLE_UNDIRECTED);
  struct ATTR_PACKED
  {
    uint16_t manufacturer;
    uint8_t sensor_len;
    uint16_t sensor_type;
    uint8_t sensor_values[4];
  } sensor_data =
  {
    .manufacturer = 0x0822,
    .sensor_len = sizeof(sensor_data) - 3,
    .sensor_type = 0x0000,
    .sensor_values = {0, 1, 2, 3},
  };
  Bluefruit.Advertising.addData(BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, &sensor_data, sizeof(sensor_data));
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(200, 200);
  Bluefruit.Advertising.setFastTimeout(0);
  Bluefruit.Advertising.start(0);
}

void setup() {
  Bluefruit.begin();
  Bluefruit.autoConnLed(false);
  Bluefruit.setTxPower(4);
  startAdv();
  suspendLoop();
}

void loop() {}