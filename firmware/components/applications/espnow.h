#ifndef ESP_NOW_H_
#define ESP_NOW_H_

#include "comm_stack_config.h"

void espnow_init();
void espnow_deinit();

int espnow_send(struct js_stamp* stamp);

#endif /* ESP_NOW_H_ */
