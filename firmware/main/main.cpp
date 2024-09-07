#include "Arduino.h"
#include "HardwareSerial.h"
#include "gpio_list.h"
#include "dip.h"
#include "modes.h"
#include "joystick.h"
#include "app.h"
#include "espnow.h"
#include "nrf24.h"
#include <cstdint>
#include <sys/types.h>

static struct joystick js_x;
static struct joystick js_y;
static struct app app_esp_now;
static struct app app_nrf;

static void check_and_change_app(void);

void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect
  }

  dip_init();
  joystick_init(&js_x, GPIO_JOYSTICK_X, GPIO_JOYSTICK_X_IRQ);
  joystick_init(&js_y, GPIO_JOYSTICK_Y, GPIO_JOYSTICK_Y_IRQ);

  app_install(&app_esp_now, espnow_init, espnow_deinit, espnow_send, NULL);
  app_install(&app_nrf, nrf24_init, nrf24_deinit, nrf24_send, NULL);

  check_and_change_app();
}

void loop()
{
  // (1) Check DIP.
  if (dip_has_changed()) {
    check_and_change_app();
  }

  // (2) Check Joysticks.
  if (joystick_has_moved(&js_x) != -1 || joystick_has_moved(&js_y) != -1) {
    struct js_stamp stamp = {
      .x = js_x.read,
      .y = js_y.read,
    };
    app_send(&stamp);
  }
}

static void check_and_change_app(void)
{
  uint8_t read = dip_read();

  Serial.printf("Value for the DIP4 '%02x'\n", (int)read);
  switch (read) {
  case DIP_ESP_NOW:
    app_next(&app_esp_now);
    break;
  case DIP_NRF:
    app_next(&app_nrf);
    break;
  default:
    // Other: nothing.
    app_next(NULL);
    break;
  }
}
