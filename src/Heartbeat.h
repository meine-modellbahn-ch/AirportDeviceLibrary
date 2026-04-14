#pragma once
#include "Protocol.h"
#include <Wire.h>

class Heartbeat {
public:
    Heartbeat(Protocol* p);

    void send();
    void sendRegister();
    void addI2CDevice(uint8_t addr);

private:
    Protocol* _p;
    uint8_t _dev[10];
    uint8_t _count=0;

    bool check(uint8_t addr);
};
