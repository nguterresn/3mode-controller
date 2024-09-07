#include "joystick.h"
#include "Arduino.h"
#include "esp32-hal-adc.h"
#include "esp32-hal-gpio.h"
#include <stdint.h>

#define CALIBRATION_MAX  (4096)
#define CALIBRATION_ZER0 (2048)
#define CALIBRATION_DELTA \
  (256) // The lower the Vref, the bigger should be this number.
#define UPDATE_DELTA (25)

static uint16_t joystick_mitigate_noise(uint16_t read);
static void     joystick_cb(void);

void joystick_init(struct joystick* js, uint8_t pin, uint8_t pin_irq)
{
  js->pin     = pin;
  js->pin_irq = pin_irq;

  pinMode(js->pin, INPUT);
  pinMode(js->pin_irq, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(js->pin_irq), joystick_cb, FALLING);
}

uint16_t joystick_read(struct joystick* js)
{
  return joystick_mitigate_noise(analogRead(js->pin));
}

int16_t joystick_has_moved(struct joystick* js)
{
  uint16_t new_read = joystick_read(js);
  if (abs(js->read - new_read) > UPDATE_DELTA) {
    js->read = new_read;
    return new_read;
  }

  return -1;
}

static uint16_t joystick_mitigate_noise(uint16_t read)
{
  if ((CALIBRATION_ZER0 < read &&
       read < (CALIBRATION_ZER0 + CALIBRATION_DELTA)) ||
      (CALIBRATION_ZER0 > read &&
       read > (CALIBRATION_ZER0 - CALIBRATION_DELTA))) {
    return CALIBRATION_ZER0;
  }
  if ((CALIBRATION_MAX - CALIBRATION_DELTA) < read && read <= CALIBRATION_MAX) {
    return CALIBRATION_MAX;
  }
  if (0 <= read && read < CALIBRATION_DELTA) {
    return 0;
  }
  return read;
}

static void joystick_cb(void)
{
}

