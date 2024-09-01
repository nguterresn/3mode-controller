#include "nrf24.h"
#include "comm_stack_config.h"
#include "mirf.h"
#include <Arduino.h>

#include <driver/spi_master.h>
#include <driver/gpio.h>
#include <string.h>

static NRF24_t dev;

void nrf24_init()
{
  Nrf24_init(&dev);
  uint8_t payload = sizeof(struct js_stamp);
  uint8_t channel = 0;
  Nrf24_config(&dev, channel, payload);

  // The RX Address of Pipe 0 is also set with the same address as the TX address.
  // I believe it is forced by this library to comply with the Auto ACK, but it is not needed.
  esp_err_t ret = Nrf24_setTADDR(&dev, (uint8_t*)address);
  if (ret != ESP_OK) {
    return;
  }

  // Print settings
  // Nrf24_printDetails(&dev);
}

void nrf24_deinit()
{
  // GPIO out as well (Missing from the lib).
  spi_bus_remove_device(dev._SPIHandle);
  // Should also reset the SPI bus, but the host id is private. Go figure 🤌
  memset(&dev, 0, sizeof(NRF24_t));
}

int nrf24_send(struct js_stamp* stamp)
{
  Nrf24_send(&dev, (uint8_t*)stamp);
  return 0;
}
