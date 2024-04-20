#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

struct joystick {
  uint8_t  pin;
  uint16_t data;
} __attribute__((packed));

struct joystick_data {
  uint16_t x;
  uint16_t y;
};

#define JOYSTICK_DELTA 20

void joystick_init(struct joystick* joystick, uint8_t pin);
uint16_t joystick_read(struct joystick* joystick);

#ifdef __cplusplus
}
#endif

#endif
