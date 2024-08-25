#ifndef NRF24_H_
#define NRF24_H_

#include "comm_stack_config.h"

void nrf24_init();
void nrf24_deinit();

int nrf24_send(struct js_stamp* stamp);

#endif /* NRF24_H_ */
