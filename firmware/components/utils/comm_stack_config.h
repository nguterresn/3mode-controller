#ifndef COMM_STACK_CONFIG_H_
#define COMM_STACK_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct js_stamp {
  uint16_t x;
  uint16_t y;
} __attribute__((packed));

// Acording to the nRF24L01+ datasheet:
// > LSB is written first.
const uint8_t address[] = {
  0x1A, 0xFF, 0x00, 0xFF, 0x00, 0xFF
}; // Addresses are 40 bit hex

#ifdef __cplusplus
}
#endif

#endif /* COMM_STACK_CONFIG_H_ */
