#pragma once

#ifndef SCREEN_FUNCTION_H
#define SCREEN_FUNCTION_H

#include <TFT_eSPI.h>
#include <U8g2_for_TFT_eSPI.h>
#include "losses.h"
#include "buzzer.h"

#ifndef VERSION
  #define VERSION 0
#endif

extern TFT_eSPI tft;
extern U8g2_for_TFT_eSPI u8f;

void setupScreen();
void showTime();
void drawIncreaseLine(String line, int i);
void displayLosses(const int startFrom = 0);
String dBmtoPercentage(int dBm);
void drawCentreString(const String &text, const int y, const uint16_t color, const uint8_t *font);
void drawTime(DateTimeParts parts);
void blinkColon(bool hide);
void drawWiFiParams(String text);
String getIncreaseLine();
void displayWiFiConnected();
void displayWiFiConfiguration();
int calcXcenter(int w);

#endif