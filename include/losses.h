#pragma once

#ifndef LOSSES_FUNCTION_H
#define LOSSES_FUNCTION_H

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "ntptime.h"

extern String currentDate; 
extern int currentDay;
extern JsonObject currentStats;
extern JsonObject currentIncrease;
extern time_t lastUpdated;

String getValueWithIncrease(String param);
String getValue(String param);
int getIncrease(String param);
void getLosses();

#endif