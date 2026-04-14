#pragma once
#include <Arduino.h>

class Debug {
public:
    static void begin(bool enabled) { _enabled = enabled; }
    static void log(const char* msg) { if (_enabled) Serial.println(msg); }

private:
    static bool _enabled;
};
