#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Callbacks.h"

class Protocol {
public:
    Protocol(WiFiClient* client, uint8_t deviceId);

    void sendFrame(uint8_t type, uint8_t* data, uint16_t len);
    void read();

    void onLed(LedCallback cb);
    void onButton(ButtonCallback cb);

private:
    WiFiClient* _client;
    uint8_t _deviceId;

    LedCallback _ledCb = nullptr;
    ButtonCallback _buttonCb = nullptr;

    uint8_t crc8(uint8_t* data, uint16_t len, uint8_t crc = 0);
    void handleFrame(uint8_t* buffer, uint16_t len);
};
