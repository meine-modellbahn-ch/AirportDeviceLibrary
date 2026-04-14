#include "Heartbeat.h"

Heartbeat::Heartbeat(Protocol* p){ _p=p; }

void Heartbeat::addI2CDevice(uint8_t addr){
    _dev[_count++]=addr;
}

bool Heartbeat::check(uint8_t addr){
    Wire.beginTransmission(addr);
    return Wire.endTransmission()==0;
}

void Heartbeat::send(){
    uint8_t payload[32];
    uint8_t i=0;

    payload[i++]=_count;

    for(int j=0;j<_count;j++){
        payload[i++]=check(_dev[j])?1:0;
    }

    _p->sendFrame(0x40,payload,i);
}

void Heartbeat::sendRegister(){
    uint8_t payload[16];
    payload[0]=_count;

    for(int i=0;i<_count;i++){
        payload[i+1]=_dev[i];
    }

    _p->sendFrame(0x30,payload,_count+1);
}
