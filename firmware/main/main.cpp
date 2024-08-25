//file: main.cpp
#include "Arduino.h"
#include "gpio_list.h"
#include "dip.h"
#include "masks.h"
#include "joystick.h"
#include "espnow.h"

extern SemaphoreHandle_t sem;

static struct joystick js_x;
static struct joystick js_y;

int (*send)(uint16_t, uint16_t) = NULL;

void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect
  }

  dip_init();
  joystick_init(&js_x, GPIO_JOYSTICK_X, GPIO_JOYSTICK_X_IRQ);
  joystick_init(&js_y, GPIO_JOYSTICK_Y, GPIO_JOYSTICK_Y_IRQ);
}

void loop()
{
  if (xSemaphoreTake(sem, 0)) {
    uint8_t read = dip_read();
    Serial.printf("Value for reading it %x\n", (int)read);

    // Decision maker!
    // if
    if (MASKED(read, MASK_NRF)) {
      // Init nrf and load send function!
    }
    else if (MASKED(read, MASK_ESP_NOW)) {
      espnow_init();
      send = espnow_send;
    }
    else {
      exit(-1);
    }
  }
  if (joystick_has_moved(&js_x) != -1 || joystick_has_moved(&js_y) != -1) {
    if (send) {
      send(js_x.read, js_y.read);
    }
  }
}
