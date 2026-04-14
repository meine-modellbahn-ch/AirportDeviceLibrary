#include <AirportDevice.h>

AirportDevice device(
  "WIFI_NAME",
  "WIFI_PASS",
  "192.168.1.63",
  3000,
  2,
  true
);

void setup(){
  device.begin();
}

void loop(){
  device.heartbeat().addI2CDevice(0x40);
  device.heartbeat().addI2CDevice(0x41);

  device.loop();
}
