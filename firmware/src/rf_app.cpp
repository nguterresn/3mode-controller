#include "rf_app.h"
#include <SPI.h>
#include "RF24.h"
#include "gpio_list.h"
#include "comm_stack_config.h"

RF24 radio(GPIO_RF_SPI_CE, GPIO_RF_SPI_CNS);

void rf_app_init()
{
  if (!radio.begin()) {
    Serial.println("radio hardware is not responding!!");
    for (;;) {
      ;
    }
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(rf_dest_address);
  radio.stopListening();
}

void rf_app_deinit()
{
  radio.openWritingPipe(0xFFFFFFFFFF); // Random address. Not sure how to deinit here.
}

int rf_app_transmit(uint8_t* data, uint8_t data_length)
{
  return radio.write(data, data_length);
}
