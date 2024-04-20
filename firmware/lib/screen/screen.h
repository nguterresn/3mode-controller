#ifndef SCREEN_H_
#define SCREEN_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

enum gui_name {
  WIFI,
  RF,
  BLE
};

void IRAM_ATTR screen_interrupt(void);
void screen_init(void (*comm_stack_init)(enum gui_name));
enum gui_name screen_get_name(void);

#endif /* SCREEN_H_ */
