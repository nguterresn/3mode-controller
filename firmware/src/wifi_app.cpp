#include "wifi_app.h"
#include <Arduino.h>
#include <WiFi.h>
#include "ESPNowW.h"
#include "comm_stack_config.h"

void wifi_app_init()
{
  wifi_app_start();

  ESPNow.init();
  ESPNow.add_peer(wifi_dest_mac_address);
}

void wifi_app_start()
{
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
}

void wifi_app_stop()
{
  // ESPNow.remove_peer(dest_address); // This breaks the code :))))
  WiFi.mode(WIFI_MODE_NULL); // disables wifi
}

int wifi_app_transmit(uint8_t* data, uint8_t data_length)
{
  return ESPNow.send_message(wifi_dest_mac_address, data, data_length);
}
