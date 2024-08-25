#include "dip.h"
#include "Arduino.h"
#include "esp32-hal-gpio.h"
#include "gpio_list.h"
#include <stdint.h>

static SemaphoreHandle_t sem;
static void       dip_changed(void);

void dip_init()
{
  pinMode(GPIO_DIP_1, INPUT_PULLUP);
  pinMode(GPIO_DIP_2, INPUT_PULLUP);
  pinMode(GPIO_DIP_3, INPUT_PULLUP);
  pinMode(GPIO_DIP_4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(GPIO_DIP_1), dip_changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GPIO_DIP_2), dip_changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GPIO_DIP_3), dip_changed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(GPIO_DIP_4), dip_changed, CHANGE);

  sem = xSemaphoreCreateBinary();
  if (!sem) {
    exit(-1);
  }
}

uint8_t dip_read(void)
{
  // Note: GPIO_DIP_1 holds the LSB.
  return (digitalRead(GPIO_DIP_4) & 0x01) | ((digitalRead(GPIO_DIP_3) & 0x01) << 1) |
         ((digitalRead(GPIO_DIP_2) & 0x01) << 2) | ((digitalRead(GPIO_DIP_1) & 0x01) << 3);
}

static void dip_changed(void)
{
  xSemaphoreGiveFromISR(sem, NULL);
}

bool dip_has_changed(void)
{
  return xSemaphoreTake(sem, 0) ? true : false;
}
