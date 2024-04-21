#include "payload.h"
#include <Arduino.h>

void payload_build(uint16_t x, uint16_t y, uint8_t* out)
{
  uint8_t* out_p = out;
  char _x = 0, _y = 0;

  _x       = map(x, 0, 4096, -100, 100);
  _y       = map(y, 0, 4096, -100, 100);

  *out_p++ = (uint8_t)_x;
  *out_p   = (uint8_t)_y;
}
