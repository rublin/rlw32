#include "screen.h"

TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f;

void setupScreen()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    u8f.begin(tft);
    u8f.setFontMode(0); // use u8g2 none transparent mode
}

void test()
{
    tft.setTextColor(TFT_RED);
    tft.setCursor(0, 30);
    tft.setFreeFont(&CourierCyr18pt8b);

    tft.setTextColor(TFT_BLUE);
    tft.println("Regular ascii does not print");
    tft.println("Привіт....йїє"); // Cyrillic prints ok

    u8f.setFont(u8g2_font_inr24_t_cyrillic);
    u8f.setCursor(0, 200);
    u8f.setForegroundColor(TFT_GREEN);
    u8f.print("Привіт....йїє");
}