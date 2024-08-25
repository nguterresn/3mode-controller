#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct joystick {
  uint8_t  pin;
  uint8_t  pin_irq;
  uint16_t read;
};

void joystick_init(struct joystick* js, uint8_t pin, uint8_t pin_irq);
uint16_t joystick_read(struct joystick* js);
void joystick_save(struct joystick* js, uint16_t read);
int16_t joystick_has_moved(struct joystick* js);

#ifdef __cplusplus
}
#endif

#endif /* JOYSTICK_H_ */
