#include "wifi_app.h"
#include <Arduino.h>
#include <WiFi.h>
#include "esp_now.h"
#include "comm_stack_config.h"

void wifi_app_init()
{
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();

  esp_now_init();

  esp_now_peer_info_t peer_info = { 0 };
  memcpy(peer_info.peer_addr, wifi_dest_mac_address, 6);
  peer_info.channel = 0;
  peer_info.encrypt = false;

  esp_now_add_peer(&peer_info);
}

void wifi_app_deinit()
{
  esp_now_deinit();
  WiFi.mode(WIFI_MODE_NULL); // disables wifi
}

int wifi_app_transmit(uint8_t* data, uint8_t data_length)
{
  return esp_now_send(wifi_dest_mac_address, data, data_length);
}
