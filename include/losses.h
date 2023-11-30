#pragma once

#ifndef LOSSES_FUNCTION_H
#define LOSSES_FUNCTION_H

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "ntptime.h"

extern WiFiClientSecure *client;
extern HTTPClient https;
extern String currentDate;
extern int currentDay;
extern time_t lastUpdated;
extern const char units_matrix[15][30];
extern int losses[15];
extern int increases[15];

void getLosses();

#endif