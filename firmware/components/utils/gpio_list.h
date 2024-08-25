#ifndef GPIO_LIST_H
#define GPIO_LIST_H

// Source:
// https://www.luisllamas.es/en/esp32-s3-hardware-details-pinout/

// On ESP32-S3
// ADC1_CH0 - GPIO 1
// ADC1_CH1 - GPIO 2
// ADC1_CH2 - GPIO 3
// ADC1_CH3 - GPIO 4
// ADC1_CH4 - GPIO 5
// ADC1_CH5 - GPIO 6
// ADC1_CH6 - GPIO 7
// ADC1_CH7 - GPIO 8
// ADC1_CH8 - GPIO 9
// ADC1_CH9 - GPIO 10

#define GPIO_JOYSTICK_Y     1 // Must be ADC1
#define GPIO_JOYSTICK_X     2 // Must be ADC1
#define GPIO_JOYSTICK_Y_IRQ 14
#define GPIO_JOYSTICK_X_IRQ 17

#define GPIO_RF_SPI_CE      4  // whatever
#define GPIO_RF_SPI_CNS     10 // SPI3
#define GPIO_RF_SPI_SCK     12 // SPI3
#define GPIO_RF_SPI_MOSI    11 // SPI3
#define GPIO_RF_SPI_MISO    13 // SPI3

#define GPIO_DIP_1          6
#define GPIO_DIP_2          7
#define GPIO_DIP_3          8
#define GPIO_DIP_4          9

#endif /* GPIO_LIST_H */
