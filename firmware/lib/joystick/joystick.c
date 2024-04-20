#include "joystick.h"
#include <Arduino.h>

void joystick_init(struct joystick* joystick, uint8_t pin)
{
  joystick->pin = pin;

  pinMode(pin, INPUT);
}

uint16_t joystick_read(struct joystick* joystick)
{
  joystick->data = analogRead(joystick->pin);
  return joystick->data;
}
