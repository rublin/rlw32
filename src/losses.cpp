#include "losses.h"

 String currentDate; 
 int currentDay;
 JsonObject currentStats;
 JsonObject currentIncrease;
 time_t lastUpdated;

String getValueWithIncrease(String param) {
  int increase = (int)currentIncrease[param];
  int val = (int)currentStats[param];
  if (increase > 0) {
    return String(val) + "  +" + increase;
  }
  return String(val);
}

String getValue(String param) {
  return String((int)currentStats[param]);
}

int getIncrease(String param) {
  int increase = (int)currentIncrease[param];
  if (increase > 0) {
    return increase;
  }
  return 0;
}

void getLosses(){
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

          const char *date = data["date"]; // "2023-10-17"
          int day = data["day"];

          currentDate = date;
          currentDay = day;
          currentStats = data["stats"];
          currentIncrease = data["increase"];

          lastUpdated = DateTime.now();
          Serial.println(currentDay);
        }
      }
    }
    else
    {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
}
