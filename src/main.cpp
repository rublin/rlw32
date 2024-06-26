#include <WiFiManager.h>
#include "screen.h"

WiFiManager wm;

const int CONFIG_PORTAL_TIMEOUT = 300;
const int SECONDS_IN_HOUR = 3600;
const char *CONFIG_PORTAL_SSID = "GloryToUkraine";

void configPortalTimeoutCallback()
{
  Serial.println("Configuration portal timeout callback started");
  ESP.restart();
}

void setup(void)
{
  Serial.begin(115200);
  setupScreen();
  setupBuzzer();
  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);

  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT);
  wm.setWiFiAutoReconnect(true);
  wm.setConfigPortalTimeoutCallback(configPortalTimeoutCallback);
  wm.setShowInfoUpdate(true);
  wm.setConnectTimeout(30);
  wm.setConnectRetries(5);

  if (drd->detectDoubleReset())
  {
    wm.startConfigPortal(CONFIG_PORTAL_SSID);
    Serial.println("Double Reset Detected");
    displayWiFiConfiguration();
  }
  else
  {
    if (!wm.autoConnect(CONFIG_PORTAL_SSID))
    {
      Serial.println("Failed to connect");
      displayWiFiConfiguration();
    }
    else
    {
      // if you get here you have connected to the WiFi
      Serial.println("connected...yeey :)");

      client->setTimeout(10);
      https.setTimeout(10000);
      client->setInsecure();

      displayWiFiConnected();
      setupDateTime();
      getLosses();
    }

    drd->stop();
  }
}

void loop()
{
  wm.process();

  if (WiFi.isConnected())
  {
    time_t now = DateTime.now();
    if ((now - lastUpdated) > SECONDS_IN_HOUR / 6)
    {
      Serial.println(String("Free heap2: ") + ESP.getFreeHeap());
      getLosses();
      Serial.println(String("Free heap3: ") + ESP.getFreeHeap());
    }

    showTime();
    displayLosses();
    showTime();
    displayLosses(8);
  }
  else if (!wm.getConfigPortalActive())
  {
    Serial.println("WiFi connection lost. Trying to reconnect...");
    ESP.restart();
  }
}
