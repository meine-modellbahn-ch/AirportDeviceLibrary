#include "MyDevice.h"

MyDevice::AirportDevice(const char* ssid,const char* pass,
                   const char* server,uint16_t port,
                   uint8_t id,bool debug)
: _ssid(ssid),_pass(pass),_server(server),_port(port),
  _id(id),_proto(&_client,id),_hb(&_proto)
{
    Debug::begin(debug);
}

void AirportDevice::begin(){
    Serial.begin(115200);
    wifi();
    server();
}

void AirportDevice::wifi(){
    WiFi.begin(_ssid,_pass);
    while(WiFi.status()!=WL_CONNECTED){
        delay(300);
    }
}

void AirportDevice::server(){
    while(!_client.connect(_server,_port)){
        delay(500);
    }
    _hb.sendRegister();
}

Heartbeat& AirportDevice::heartbeat(){ return _hb; }

void AirportDevice::rx(){ _proto.read(); }

void AirportDevice::loop(){
    rx();

    if(WiFi.status()!=WL_CONNECTED){
        if(millis()-_lastRe>5000){ wifi(); _lastRe=millis(); }
        return;
    }

    if(!_client.connected()){
        if(millis()-_lastRe>5000){ server(); _lastRe=millis(); }
        return;
    }

    if(millis()-_lastHB>10000){
        _hb.send();
        _lastHB=millis();
    }
}
