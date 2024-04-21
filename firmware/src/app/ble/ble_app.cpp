#include "ble_app.h"
#include <Arduino.h>

void ble_app_init()
{
  if (btStarted()) {
    return;
  }
  btStart();

  // It is missing a connection to a bluetooth central (scan, service, charac,...)
}

void ble_app_deinit()
{
  if (!btStarted()) {
    return;
  }
  btStop();
}
