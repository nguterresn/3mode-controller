#ifndef ESP_NOW_H_
#define ESP_NOW_H_

#include <stdint.h>

void espnow_init();
void espnow_deinit();

int espnow_send(uint16_t x, uint16_t y);

#endif /* ESP_NOW_H_ */
