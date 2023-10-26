#include <WiFiManager.h>

#include "buzzer.h"
#include "screen.h"

WiFiManager wm;

void setup(void)
{
  Serial.begin(115200);
  setupScreen();
  // setupBuzzer();

  wm.setConfigPortalBlocking(false);
  wm.setConfigPortalTimeout(60);

  if (!wm.autoConnect("AutoConnectAP"))
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    Serial.println("connected...yeey :)");
  }

  if (WiFi.isConnected())
  {
   getLosses();
  }
}

void loop()
{
  wm.process();

  displayLosses1();
  showTime();
  // playTones();
}