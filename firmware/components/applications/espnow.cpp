#include "espnow.h"
#include "esp_now.h"
#include "WiFi.h"

// Note: Attention: the bit 0 of the first byte of MAC address can not be 1.
// For example, the MAC address can set to be “1a:XX:XX:XX:XX:XX”, but can not be “15:XX:XX:XX:XX:XX”.
static esp_now_peer_info_t peer_info = { .peer_addr = { 0x1A, 0xFF, 0x00, 0xFF, 0x00, 0xFF },
                                         .channel = 0,
                                         .encrypt = false };

void espnow_init(void)
{
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK || esp_now_add_peer(&peer_info) != ESP_OK) {
    return;
  }
}

int espnow_send(struct js_stamp* stamp)
{
  esp_err_t result = esp_now_send(peer_info.peer_addr, (uint8_t*)&stamp, sizeof(struct js_stamp));

  return (int)result;
}

void espnow_deinit()
{
  esp_now_deinit();

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
