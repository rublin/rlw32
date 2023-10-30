#pragma once

#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

#include "ESPDateTime.h"

#define ESP_DRD_USE_EEPROM      true
#define ESP_DRD_USE_SPIFFS      false
#define DRD_TIMEOUT 2
#define DRD_ADDRESS 0

#include <ESP_DoubleResetDetector.h>      //https://github.com/khoih-prog/ESP_DoubleResetDetector

extern DoubleResetDetector* drd;

void setupDateTime();

#endif