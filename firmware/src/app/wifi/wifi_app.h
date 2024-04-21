#ifndef WIFI_APP_H_
#define WIFI_APP_H_

#include <stdio.h>

void wifi_app_init();
void wifi_app_deinit();

int wifi_app_transmit(uint8_t* data, uint8_t data_length);

#endif
