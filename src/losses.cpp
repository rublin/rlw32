#include "losses.h"

String currentDate;
int currentDay;
JsonObject currentStats;
JsonObject currentIncrease;
time_t lastUpdated;

const char units_matrix[15][30] = {"personnel_units", "tanks", "armoured_fighting_vehicles", "artillery_systems", "mlrs", "aa_warfare_systems", "planes", "helicopters",
                                   "vehicles_fuel_tanks", "warships_cutters", "cruise_missiles", "uav_systems", "special_military_equip", "atgm_srbm_systems", "submarines"};

String getValueWithIncrease(String param)
{
  int increase = (int)currentIncrease[param];
  int val = (int)currentStats[param];
  if (increase > 0)
  {
    return String(val) + "  +" + increase;
  }
  return String(val);
}

String getValue(String param)
{
  return String((int)currentStats[param]);
}

int getIncrease(String param)
{
  int increase = (int)currentIncrease[param];
  if (increase > 0)
  {
    return increase;
  }
  return 0;
}

void getLosses()
{
  WiFiClientSecure *client = new WiFiClientSecure;
  HTTPClient https;
  client->setInsecure();
  if (!https.begin(*client, "https://russianwarship.rip/api/v2/statistics/latest"))
  {
    Serial.println("BEGIN FAILED...");
  }
  https.addHeader("accept", "application/json");
  int httpCode = https.GET();
  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
    {
      // print server response payload
      String payload = https.getString();
      Serial.println(payload);
      DynamicJsonDocument doc(1600);
      DeserializationError error = deserializeJson(doc, payload);

      if (error)
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      else
      {
        JsonObject data = doc["data"];
        JsonObject stats = data["stats"];
        JsonObject increase = data["increase"];

        int persons = stats[units_matrix[0]];
        const char *date = data["date"]; // "2023-10-17"
        int day = data["day"];
        if (persons > 0 && day > 0)
        {
          currentDate = date;
          currentDay = day;
          currentStats = stats;
          currentIncrease = increase;

          lastUpdated = DateTime.now();
          Serial.println(String("Updated losses. Day: ") + currentDay + ". Persons: " + persons);
        }
        else
        {
          Serial.println("Failed to update losses.");
        }
      }
    }
  }
  else
  {
    Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
  }
  https.end();
}
