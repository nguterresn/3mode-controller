#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "gpio_list.h"
#include "screen.h"
#include "joystick.h"
#include "button.h"
#include "wifi_app.h"
#include "payload.h"

static struct joystick joystick_speed;
static struct joystick joystick_direction;
static struct button button;

static uint16_t x, y;

void comm_stack_init(enum gui_name gui);
void comm_stack_transmit(enum gui_name gui, uint16_t x, uint16_t y);

void setup()
{
  Serial.begin(9600);

  joystick_init(&joystick_speed, GPIO_JOYSTICK_Y);
  joystick_init(&joystick_direction, GPIO_JOYSTICK_X);

  screen_init(comm_stack_init);

  button_init(&button, GPIO_BUTTON_MOVE, screen_interrupt);

  // Init != start
  wifi_app_init();
}

void loop()
{
  uint16_t _x = joystick_read(&joystick_direction);
  uint16_t _y = joystick_read(&joystick_speed);

  if ((x + JOYSTICK_DELTA < _x || _x + JOYSTICK_DELTA < x) ||
      (y + JOYSTICK_DELTA < _y || _y + JOYSTICK_DELTA < y)) {
    x = _x;
    y = _y;
    comm_stack_transmit(screen_get_name(), x, y);
  }

  vTaskDelay(10);
}

void comm_stack_init(enum gui_name gui)
{
  if (gui == WIFI) {
    // if wifi gui enabled - esp now
    wifi_app_start();
    Serial.printf("wifi_app_init\n");
    // disable others
  }
  else if (gui == RF) {
    // else if rf gui enabled - rf24
    Serial.printf("wifi_app_deinit\n");
    wifi_app_stop();
  }
  else {
    // else - ble
    Serial.printf("wifi_app_deinit2\n");
    wifi_app_stop();
  }
}

void comm_stack_transmit(enum gui_name gui, uint16_t x, uint16_t y)
{
  uint8_t data_to_send[2] = { 0 }; // X (-100 : 100), Y (-100 : 100)

  payload_build(x, y, data_to_send);

  if (gui == WIFI) {
    wifi_app_transmit(data_to_send, sizeof(data_to_send));
  }
  else if (gui == RF) {
  }
  else {
  }
}
