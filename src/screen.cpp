#include "screen.h"

TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f;

const int RSSI_MAX = -50;
const int RSSI_MIN = -100;
const int PIXEL_SHIFT = 8;
const int CONFIG_PORTAL_TIMEOUT = 300;
const char unit_names_matrix[15][30] = {"ос.складу", "танків", "ББМ", "арт.систем", "РСЗВ", "ППО", "літаків", "гелікоптерів",
                                        "авт.техніки", "кораблів", "крил.ракет", "БпЛА", "спец.техніки", "рак.комплеків", "підв.човнів"};
const char unit_names_matrix2[15][30] = {"Ос. склад:", "Танки:", "ББМ:", "Арт.сист:", "РСЗВ:", "ППО:", "Літаки:", "Гелікопт.:",
                                         "Авто.техн:", "Кораблі:", "Крил.рак.:", "БпЛА:", "Спец.техн:", "Рак.компл:", "Підв.човн:"};

void setupScreen()
{
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  u8f.begin(tft);
  u8f.setFontMode(0); // use u8g2 none transparent mode
}

void showTime()
{
  tft.fillScreen(TFT_BLACK);
  DateTimeParts parts = DateTime.getParts();
  int osIncrease = increases[0];

  if (
      osIncrease > 1000 &&
      parts.getHours() > 9 && parts.getHours() < 19 && parts.getMinutes() == 0)
  {
    Serial.println("Starting to play tones");
    playTones();
  }

  drawCentreString(parts.format("%d %b  %a"), 25, TFT_YELLOW, u8g2_font_profont29_tr);
  drawTime(parts);
  drawCentreString("День війни: " + String(currentDay), 200, TFT_YELLOW, u8g2_font_inr24_t_cyrillic);
  String increaseLine = getIncreaseLine();
  // 20 seconds
  for (int i = 0; i < 200; i++)
  {
    // one second
    if ((i % 10) == 0)
    {
      int j = (i / 10) % 2;
      if (j == 0)
      {
        blinkColon(true);
      }
      else
      {
        blinkColon(false);
      }
    }
    // 5 seconds
    if ((i % 50) == 0)
    {
      int j = (i / 50) % 2;
      if (j == 0)
      {
        drawWiFiParams("WiFi: " + WiFi.SSID().substring(0, 10) + " " + dBmtoPercentage(WiFi.RSSI()) + " " + VERSION);
      }
      else
      {
        drawWiFiParams("Local IP: " + WiFi.localIP().toString() + " " + VERSION);
      }
    }

    drawIncreaseLine(increaseLine, i * PIXEL_SHIFT);
    delay(100);
  }
}

void drawIncreaseLine(String line, int shift)
{
  tft.fillRect(0, 140, TFT_HEIGHT, 25, 0x3800);
  u8f.setForegroundColor(TFT_WHITE);
  u8f.setFont(u8g2_font_10x20_t_cyrillic);
  u8f.setCursor(0 - shift, 160);
  u8f.print(line);
}

String getIncreaseLine()
{
  String buffer = String("           ");
  String result = String("За минулу добу знищено: ");

  for (int i = 0; i < 15; i++)
  {
    int unit = increases[i];
    if (unit > 0)
    {
      if (i > 0)
      {
        result = result + ", ";
      }
      result = result + unit_names_matrix[i] + " " + unit;
    }
  }
  return buffer + result;
}

void drawWiFiParams(String text)
{
  tft.fillRect(0, 220, TFT_HEIGHT, 20, TFT_BLACK);
  u8f.setForegroundColor(TFT_WHITE);
  u8f.setFont(u8g2_font_9x15_t_cyrillic);
  int width = u8f.getUTF8Width(text.c_str());
  u8f.setCursor(calcXcenter(width), 235);
  u8f.print(text);
}

void displayWiFiConnected()
{
  tft.fillScreen(TFT_BLACK);
  u8f.setForegroundColor(TFT_BLUE);
  u8f.setFont(u8g2_font_fub20_tr);
  u8f.setCursor(5, 60);
  u8f.print("WiFi status:");
  u8f.setCursor(5, 140);
  u8f.print("WiFi network:");

  drawCentreString("Connected!", 100, TFT_YELLOW, u8g2_font_fub20_tr);
  drawCentreString(WiFi.SSID(), 180, TFT_YELLOW, u8g2_font_fub20_tr);
}

void displayWiFiConfiguration()
{
  tft.fillScreen(TFT_BLACK);

  u8f.setForegroundColor(TFT_BLUE);
  u8f.setFont(u8g2_font_fub20_tr);
  u8f.setCursor(5, 60);
  u8f.print("WiFi status:");
  drawCentreString("NOT connected", 100, TFT_RED, u8g2_font_fub20_tr);

  u8f.setForegroundColor(TFT_WHITE);
  u8f.setFont(u8g2_font_10x20_t_cyrillic);
  u8f.setCursor(0, 150);
  u8f.print("Connect to AP: GloryToUkraine");
  u8f.setCursor(0, 180);
  u8f.print("Open 192.168.4.1 in your browser");
  u8f.setCursor(0, 210);
  u8f.print("You have " + String(CONFIG_PORTAL_TIMEOUT / 60) + " minutes to configure");
}

void displayLosses(const int startFrom)
{
  tft.fillScreen(TFT_BLACK);
  u8f.setFont(u8g2_font_10x20_t_cyrillic);
  u8f.setForegroundColor(TFT_WHITE);

  int y = 20; // starting position
  for (int i = startFrom; i < 15; i++)
  {
    String name = unit_names_matrix2[i];
    int value = losses[i];
    int increase = increases[i];
    // Serial.println(String(name) + " " + value + " " + increase + " i=" + i);

    u8f.setCursor(0, y);
    u8f.print(name);
    u8f.setCursor(180, y);
    u8f.print(value);
    if (increase > 0)
    {
      u8f.setCursor(270, y);
      u8f.print("+" + String(increase));
    }
    y = y + 30;

    if (y > TFT_WIDTH)
    {
      break;
    }
  }

  delay(5000);
}

String dBmtoPercentage(int dBm)
{
  int quality;
  if (dBm <= RSSI_MIN)
  {
    quality = 0;
  }
  else if (dBm >= RSSI_MAX)
  {
    quality = 100;
  }
  else
  {
    quality = 2 * (dBm + 100);
  }
  return String(quality) + "%";
}

void drawCentreString(const String &text, const int y, const uint16_t color, const uint8_t *font)
{
  u8f.setForegroundColor(color);
  u8f.setFont(font);
  int width = u8f.getUTF8Width(text.c_str());
  u8f.setCursor(calcXcenter(width), y);
  u8f.print(text);
}

void drawTime(DateTimeParts parts)
{
  String hour = parts.format("%H");
  String minute = parts.format("%M");
  tft.fillRoundRect(35, 44, 115, 88, 3, TFT_SILVER);
  tft.fillRoundRect(170, 44, 115, 88, 3, TFT_SILVER);

  u8f.setForegroundColor(TFT_BLUE);
  u8f.setBackgroundColor(TFT_SILVER);
  u8f.setFont(u8g2_font_logisoso78_tn);

  int width = u8f.getUTF8Width(hour.c_str());
  int x = (35 + 57) - (width / 2);
  u8f.setCursor(x, 125);

  u8f.print(hour);

  width = u8f.getUTF8Width(minute.c_str());
  u8f.setCursor((170 + 57) - (width / 2), 125);
  u8f.print(minute);
  u8f.setBackgroundColor(TFT_BLACK);

  tft.drawWideLine(34, 88, 294, 88, 2, TFT_BLACK, TFT_BLACK);
  blinkColon(false);
}

void blinkColon(bool hide)
{
  tft.fillRect(TFT_HEIGHT / 2 - 10, 65, 20, 60, TFT_BLACK);
  u8f.setFont(u8g2_font_logisoso78_tn);
  u8f.setCursor(147, 120);
  if (hide)
  {
    u8f.setForegroundColor(0x0010);
    u8f.print(":");
  }
  else
  {
    u8f.setForegroundColor(TFT_BLUE);
    u8f.print(":");
  }
}

int calcXcenter(int w)
{
  return (TFT_HEIGHT - w) / 2;
}
