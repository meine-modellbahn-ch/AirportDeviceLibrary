#pragma once
#include <ESP8266WiFi.h>
#include "Protocol.h"
#include "Heartbeat.h"
#include "Debug.h"

class AirportDevice {
public:
    AirportDevice(const char* ssid,const char* pass,
             const char* server,uint16_t port,
             uint8_t id,bool debug=false);

    void begin();
    void loop();

    Heartbeat& heartbeat();

private:
    const char* _ssid;
    const char* _pass;
    const char* _server;
    uint16_t _port;
    uint8_t _id;

    WiFiClient _client;
    Protocol _proto;
    Heartbeat _hb;

    unsigned long _lastHB=0;
    unsigned long _lastRe=0;

    void wifi();
    void server();
    void rx();
};
