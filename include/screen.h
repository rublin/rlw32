#pragma once

#ifndef SCREEN_FUNCTION_H
#define SCREEN_FUNCTION_H

#include <TFT_eSPI.h>
#include <U8g2_for_TFT_eSPI.h>

extern TFT_eSPI tft;
extern U8g2_for_TFT_eSPI u8f;

void setupScreen();
void test();

#endif