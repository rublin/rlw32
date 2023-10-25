
#include <WiFiManager.h>
#include "buzzer.h"
#include "screen.h"

WiFiManager wm;

void setup(void)
{
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
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
}

void loop()
{
  wm.process();

  test();
  // playTones();
}