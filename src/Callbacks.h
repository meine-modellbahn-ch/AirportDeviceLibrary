#pragma once
#include <Arduino.h>

typedef void (*LedCallback)(uint8_t board, uint8_t channel, uint16_t value);
typedef void (*ButtonCallback)(uint8_t button, uint8_t state);
