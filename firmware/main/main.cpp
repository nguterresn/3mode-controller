#include "Arduino.h"
#include "HardwareSerial.h"
#include "gpio_list.h"
#include "dip.h"
#include "masks.h"
#include "joystick.h"
#include "app.h"
#include "espnow.h"
#include "nrf24.h"

static struct joystick js_x;
static struct joystick js_y;
static struct app app_esp_now;
static struct app app_nrf;

static struct app* app;
static void change_app(struct app* next_app);

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

  change_app(&app_esp_now); // Install as default;
}

void loop()
{
  // (1) Check DIP.
  if (dip_has_changed()) {
    uint8_t read = dip_read();
    Serial.printf("Value for the DIP4 '%02x'\n", (int)read);

    if (MASKED(read, MASK_NRF)) {
      change_app(&app_nrf);
    }
    else if (MASKED(read, MASK_ESP_NOW)) {
      change_app(&app_esp_now);
    }
    // Other: nothing.
  }

  // (2) Check Joysticks.
  if (joystick_has_moved(&js_x) != -1 || joystick_has_moved(&js_y) != -1) {
    struct js_stamp stamp = {
      .x = js_x.read,
      .y = js_y.read,
    };
    app->send(&stamp);
  }
}

static void change_app(struct app* next_app)
{
  if (next_app == app) {
    return;
  }

  if (app) {
    // Only deinit if there was a app installed.
    app->deinit();
  }
  app = next_app;
  app->init();
}
