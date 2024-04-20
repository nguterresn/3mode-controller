#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define JOYSTICK_DELTA 20
struct joystick {
  uint8_t pin;
} __attribute__((packed));

void joystick_init(struct joystick* joystick, uint8_t pin);
uint16_t joystick_read(struct joystick* joystick);

#ifdef __cplusplus
}
#endif

#endif
