#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct button {
  uint8_t pin;
} __attribute__((packed));

void button_init(struct button* button, uint8_t pin, void (*interrupt_function)());
void button_deinit(struct button* button);

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H_ */
