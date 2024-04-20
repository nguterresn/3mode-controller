#include "button.h"
#include <Arduino.h>

void button_init(struct button* button, uint8_t pin, void (*interrupt_function)())
{
  button->pin = pin;
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), interrupt_function, FALLING);
}

void button_deinit(struct button* button)
{
  detachInterrupt(digitalPinToInterrupt(button->pin));
}
