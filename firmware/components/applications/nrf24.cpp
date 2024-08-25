#include "nrf24.h"
// #include "Mirf.h"
#include "gpio_list.h"
#include "mirf.h"

NRF24_t dev;

void nrf24_init()
{
}

void nrf24_deinit()
{
}

int nrf24_send(struct js_stamp* stamp)
{
  (void)stamp;
  return 0;
}
