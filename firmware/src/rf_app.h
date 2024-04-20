#ifndef RF_APP_H_
#define RF_APP_H_

#include <stdio.h>

void rf_app_init();
void rf_app_deinit();

int rf_app_transmit(uint8_t* data, uint8_t data_length);

#endif /* RF_APP_H_ */
