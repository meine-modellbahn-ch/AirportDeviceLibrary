#include "Protocol.h"
#include "Debug.h"

Protocol::Protocol(WiFiClient* client, uint8_t deviceId) {
    _client = client;
    _deviceId = deviceId;
}

void Protocol::onLed(LedCallback cb) { _ledCb = cb; }
void Protocol::onButton(ButtonCallback cb) { _buttonCb = cb; }

uint8_t Protocol::crc8(uint8_t* data, uint16_t len, uint8_t crc) {
    for (uint16_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x07 : (crc << 1);
        }
    }
    return crc;
}

void Protocol::sendFrame(uint8_t type, uint8_t* data, uint16_t len) {
    uint8_t header[6];
    header[0]=0xAA; header[1]=0x03; header[2]=type;
    header[3]=_deviceId;
    header[4]=(len>>8)&0xFF;
    header[5]=len&0xFF;

    _client->write(header,6);
    _client->write(data,len);

    uint8_t crc = crc8(header,6);
    crc = crc8(data,len,crc);
    _client->write(&crc,1);
}

void Protocol::read() {
    static uint8_t buffer[128];
    static uint16_t idx=0;

    while(_client->available()){
        buffer[idx++] = _client->read();

        if(idx>6){
            uint16_t payloadLen=(buffer[4]<<8)|buffer[5];
            uint16_t frameLen=6+payloadLen+1;

            if(idx>=frameLen){
                handleFrame(buffer,frameLen);
                idx=0;
            }
        }
    }
}

void Protocol::handleFrame(uint8_t* buffer, uint16_t len) {
    uint8_t type = buffer[2];
    uint8_t* payload = &buffer[6];

    Debug::log("Frame RX");

    if(type==0x02 && _ledCb){
        _ledCb(payload[0],payload[1],(payload[2]<<8)|payload[3]);
    }

    if(type==0x10 && _buttonCb){
        _buttonCb(payload[0],payload[1]);
    }
}
