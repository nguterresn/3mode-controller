#include <Arduino.h>
#include "gpio_list.h"
#include "screen.h"
#include "joystick.h"
#include "button.h"
#include "payload.h"

#include "app/wifi/wifi_app.h"
#include "app/rf/rf_app.h"
#include "app/ble/ble_app.h"

static struct joystick joystick_speed;
static struct joystick joystick_direction;
static struct button button;

static uint16_t x, y;

void comm_stack_init(enum gui_name gui);
void comm_stack_transmit(enum gui_name gui, uint16_t x, uint16_t y);

SemaphoreHandle_t mutex = NULL;

void setup()
{
  Serial.begin(9600);

  mutex = xSemaphoreCreateMutex();

  joystick_init(&joystick_speed, GPIO_JOYSTICK_Y);
  joystick_init(&joystick_direction, GPIO_JOYSTICK_X);

  screen_init(comm_stack_init);

  button_init(&button, GPIO_BUTTON, screen_interrupt);

  wifi_app_init(); // Set as default.
}

void loop()
{
  uint16_t _x = joystick_read(&joystick_direction);
  uint16_t _y = joystick_read(&joystick_speed);

  if ((x + JOYSTICK_DELTA < _x || _x + JOYSTICK_DELTA < x) ||
      (y + JOYSTICK_DELTA < _y || _y + JOYSTICK_DELTA < y)) {
    x = _x;
    y = _y;
    Serial.printf("X %d y %d", x, y);
    comm_stack_transmit(screen_get_name(), x, y);
  }

  vTaskDelay(10);
}

void comm_stack_init(enum gui_name gui)
{
  if (xSemaphoreTake(mutex, (TickType_t)10)) {
    if (gui == WIFI) {
      rf_app_deinit();
      ble_app_deinit();
      wifi_app_init();
    }
    else if (gui == RF) {
      wifi_app_deinit();
      ble_app_deinit();
      rf_app_init();
    }
    else {
      wifi_app_deinit();
      rf_app_deinit();
      ble_app_init();
    }
    xSemaphoreGive(mutex);
  }
}

void comm_stack_transmit(enum gui_name gui, uint16_t x, uint16_t y)
{
  uint8_t data_to_send[2] = { 0 }; // X (-100 : 100), Y (-100 : 100)

  payload_build(x, y, data_to_send);

  if (xSemaphoreTake(mutex, (TickType_t)10)) {
    if (gui == WIFI) {
      wifi_app_transmit(data_to_send, sizeof(data_to_send));
    }
    else if (gui == RF) {
      rf_app_transmit(data_to_send, sizeof(data_to_send));
    }
    xSemaphoreGive(mutex);
  }
}
