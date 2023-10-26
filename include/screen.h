#pragma once

#ifndef SCREEN_FUNCTION_H
#define SCREEN_FUNCTION_H

#include <TFT_eSPI.h>
#include <U8g2_for_TFT_eSPI.h>
#include "losses.h"

#define VERSION "v0.0.1"

extern TFT_eSPI tft;
extern U8g2_for_TFT_eSPI u8f;

void setupScreen();
void showTime();
void displayLosses1();
void displayLosses2();
void printText(char* text, uint16_t color);
String dBmtoPercentage(int dBm);
void drawCentreString(const String& text, int y, int size = 2);
void drawTime(String time, bool hide);
void drawWarDay(String text);
void drawWiFiParams(String text);
String getIncreaseLine();
void displayWiFiConnected();
void displayWiFiConfiguration();
int calcXcenter(int w);


#endif