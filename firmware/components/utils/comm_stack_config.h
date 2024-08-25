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

const uint8_t wifi_dest_mac_address[] = { 0x1A, 0xFF, 0x00, 0xFF, 0x00, 0xFF };
const uint64_t rf_dest_address        = 0xF0F0F0F0E1; // 40HEXbit

#ifdef __cplusplus
}
#endif

#endif /* COMM_STACK_CONFIG_H_ */
