#include "screen.h"

TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f;

const int RSSI_MAX = -50;
const int RSSI_MIN = -100;
const int PIXEL_SHIFT = 8;
// const String VERSION = "v0.0.1";
const int CONFIG_PORTAL_TIMEOUT = 300;
const char units_matrix[15][30] = {"personnel_units", "tanks", "armoured_fighting_vehicles", "artillery_systems", "mlrs", "aa_warfare_systems", "planes", "helicopters", "vehicles_fuel_tanks", "warships_cutters", "cruise_missiles", "uav_systems", "special_military_equip", "atgm_srbm_systems", "submarines"};
const char unit_names_matrix[15][30] = {"ос.складу", "танків", "ББМ", "арт.систем", "РСЗВ", "ППО", "літаків", "гелікоптерів", "авт.техніки", "кораблів", "крил.ракет", "БпЛА", "спец.техніки", "рак.комплеків", "підв.човнів"};

void setupScreen()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    u8f.begin(tft);
    u8f.setFontMode(0); // use u8g2 none transparent mode
}

void showTime() {
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  drawCentreString(DateTime.format("%d %b  %a"), 5);

  tft.fillRect(10, 25, 28, 45, 0xC618);
  tft.fillRect(42, 25, 28, 45, 0xC618);
  tft.fillRect(93, 25, 28, 45, 0xC618);
  tft.fillRect(125, 25, 28, 45, 0xC618);

  String time = DateTime.format(DateFormatter::TIME_ONLY).substring(0, 5);
  drawTime(time, false);
  drawWarDay("War day: " + String(currentDay));

  // 20 seconds
  for (int i = 0; i < 200; i++) {

    // half a second
    if ((i % 5) == 0) {
      int j = (i / 5) % 2;
      if (j == 0) {
        drawTime(time, true);
      } else {
        drawTime(time, false);
      }
    }

    // 5 seconds
    if ((i % 50) == 0) {
      int j = (i / 50) % 2;
      if (j == 0) {
        drawWiFiParams("WiFi: " + WiFi.SSID().substring(0, 10) + " " + dBmtoPercentage(WiFi.RSSI()) + " " + VERSION);
      } else {
        drawWiFiParams("Local IP: " + WiFi.localIP().toString() + " " + VERSION);
      }
    }

    tft.fillRect(0, 75, TFT_HEIGHT, 18, 0x3800);
    u8f.setFont(u8g2_font_9x15_t_cyrillic);
    u8f.setCursor(0 - i * PIXEL_SHIFT, 88);
    u8f.print(getIncreaseLine());

    delay(100);
  }
}

String getIncreaseLine() {
  String buffer = String("     ");
  String result = String("За минулу ") + currentDay + " добу знищено: ";

  for (int i = 0; i < 15; i++) {
    int unit = getIncrease(units_matrix[i]);
    if (unit > 0) {
      if (i > 0) {
        result = result + ", ";
      }
      result = result + unit_names_matrix[i] + " " + unit;
    }
  }

  return buffer + result + buffer + result;
}

void drawWarDay(String text) {
  tft.fillRect(0, 95, 160, 20, TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  drawCentreString(text, 95);
}

void drawWiFiParams(String text) {
  tft.fillRect(0, 115, 160, 10, TFT_BLACK);
  u8f.setForegroundColor(TFT_WHITE);
  u8f.setFont(u8g2_font_5x8_t_cyrillic);
  int width = u8f.getUTF8Width(text.c_str());
  u8f.setCursor(calcXcenter(width), 125);
  u8f.print(text);
}

void displayWiFiConnected() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);

  tft.setCursor(0, 10);
  tft.print("WiFi status:");
  tft.setCursor(0, 70);
  tft.print("WiFi network:");

  tft.setTextColor(TFT_RED, TFT_BLACK);
  drawCentreString("Connected!", 40);
  drawCentreString(WiFi.SSID(), 100);

  delay(5000);
}

void displayWiFiConfiguration() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(0, 10);
  tft.print("WiFi status:");
  tft.setTextColor(0x2015);
  drawCentreString("NOT connected", 35);

  u8f.setForegroundColor(TFT_WHITE);
  u8f.setFont(u8g2_font_5x8_t_cyrillic);
  u8f.setCursor(0, 80);
  u8f.print("Connect to AP: GloryToUkraine");
  u8f.setCursor(0, 100);
  u8f.print("Open 192.168.4.1 in your browser");
  u8f.setCursor(0, 120);
  u8f.print("You have " + String(CONFIG_PORTAL_TIMEOUT / 60) + " minutes to configure");

  delay(5000);
}


void displayLosses1()
{
    Serial.println("123");
    tft.fillScreen(TFT_BLACK);

    tft.fillRect(0, 5, 160, 12, 0x10A2);
    tft.fillRect(0, 35, 160, 12, 0x10A2);
    tft.fillRect(0, 65, 160, 12, 0x10A2);
    tft.fillRect(0, 95, 160, 12, 0x10A2);

    u8f.setFont(u8g2_font_9x15_t_cyrillic);
    u8f.setForegroundColor(TFT_GREEN);

    u8f.setCursor(0, 15);
    u8f.print("Ос. склад: " + getValue("personnel_units"));
    u8f.setCursor(0, 30);
    u8f.print("Танки:     " + getValue("tanks"));
    u8f.setCursor(0, 45);
    u8f.print("ББМ:       " + getValue("armoured_fighting_vehicles"));
    u8f.setCursor(0, 60);
    u8f.print("Арт.сист:  " + getValue("artillery_systems"));
    u8f.setCursor(0, 75);
    u8f.print("РСЗВ:      " + getValue("mlrs"));
    u8f.setCursor(0, 90);
    u8f.print("ППО:       " + getValue("aa_warfare_systems"));
    u8f.setCursor(0, 105);
    u8f.print("Літаки:    " + getValue("planes"));
    u8f.setCursor(0, 120);
    u8f.print("Гелікопт.: " + getValue("helicopters"));

    delay(5000);
}

void displayLosses2() {
  tft.fillScreen(TFT_BLACK);
  u8f.setFont(u8g2_font_9x15_t_cyrillic);
  tft.fillRect(0, 5, 160, 12, 0x10A2);
  tft.fillRect(0, 35, 160, 12, 0x10A2);
  tft.fillRect(0, 65, 160, 12, 0x10A2);
  tft.fillRect(0, 95, 160, 12, 0x10A2);

  u8f.setCursor(0, 15);
  u8f.print("Авто.техн: " + getValue("vehicles_fuel_tanks"));
  u8f.setCursor(0, 30);
  u8f.print("Кораблі:   " + getValue("warships_cutters"));
  u8f.setCursor(0, 45);
  u8f.print("Крил.рак.: " + getValue("cruise_missiles"));
  u8f.setCursor(0, 60);
  u8f.print("БпЛА:      " + getValue("uav_systems"));
  u8f.setCursor(0, 75);
  u8f.print("Спец.техн: " + getValue("special_military_equip"));
  u8f.setCursor(0, 90);
  u8f.print("Рак.компл: " + getValue("atgm_srbm_systems"));
  u8f.setCursor(0, 105);
  u8f.print("Підв.човн: " + getValue("submarines"));

  delay(5000);
}
String dBmtoPercentage(int dBm) {
  int quality;
  if (dBm <= RSSI_MIN) {
    quality = 0;
  } else if (dBm >= RSSI_MAX) {
    quality = 100;
  } else {
    quality = 2 * (dBm + 100);
  }
  return String(quality) + "%";
}


void drawCentreString(const String& text, int y, int size) {
  tft.setTextSize(size);
  int16_t w = tft.textWidth(text);  //calc width of new string
  tft.setCursor(calcXcenter(w), y);
  tft.print(text);
}

void drawTime(String time, bool hide) {
  tft.setFreeFont(&FreeMonoBold12pt7b);
  tft.setTextColor(0x2015);
  tft.setCursor(12, 60);
  tft.print(time);
  tft.setFreeFont();
  if (hide) {
    tft.fillRect(75, 30, 15, 35, TFT_BLACK);
  }
}

int calcXcenter(int w) {
  return (TFT_HEIGHT - w) / 2;
}
