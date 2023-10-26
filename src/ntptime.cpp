#include "ntptime.h"

DoubleResetDetector* drd;

void setupDateTime()
{
  DateTime.setServer("ua.pool.ntp.org");
  DateTime.setTimeZone("EET-2EEST,M3.5.0/3,M10.5.0/4");
  DateTime.begin();
  if (!DateTime.isTimeValid())
  {
    Serial.println("Failed to get time from server.");
  }
  else
  {
    Serial.printf("Date Now is %s\n", DateTime.toISOString().c_str());
    Serial.printf("Timestamp is %ld\n", DateTime.now());
  }
}