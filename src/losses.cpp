#include "losses.h"

String currentDate;
int currentDay;
time_t lastUpdated;
int losses[15];
int increases[15];

const char units_matrix[15][30] = {"personnel_units", "tanks", "armoured_fighting_vehicles", "artillery_systems", "mlrs", "aa_warfare_systems", "planes", "helicopters",
                                   "vehicles_fuel_tanks", "warships_cutters", "cruise_missiles", "uav_systems", "special_military_equip", "atgm_srbm_systems", "submarines"};

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

          for (int i = 0; i < 15; i++)
          {
            losses[i] = stats[units_matrix[i]];
            increases[i] = increase[units_matrix[i]];
            Serial.println(String("Losse: ") + losses[i] + "; increase: " + increases[i]);
          }

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
