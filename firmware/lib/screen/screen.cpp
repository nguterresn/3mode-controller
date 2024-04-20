#include "screen.h"
#include "gui_list.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

struct gui {
  enum gui_name name;
  const uint8_t* bitmap;
  struct gui*    next;
};

struct screen {
  struct gui wifi;
  struct gui rf;
  struct gui ble;
};

static struct screen screen;
static struct gui* head;

static volatile bool gui_has_changed = false;
static void screen_loop(void* v);
static void screen_refresh(void);
static void (*change_comm_stack)(enum gui_name) = NULL; // To change the communication stack

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void IRAM_ATTR screen_interrupt(void)
{
  if (gui_has_changed) {
    return;
  }
  head            = head->next;
  gui_has_changed = true;
}

void screen_init(void (*comm_stack_init)(enum gui_name))
{
  screen.wifi = { .name = WIFI, .bitmap = bitmap_wifi, .next = &screen.rf };
  screen.rf   = { .name = RF, .bitmap = bitmap_rf, .next = &screen.ble };
  screen.ble  = { .name = BLE, .bitmap = bitmap_ble, .next = &screen.wifi };
  head        = &screen.wifi;

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;) {
    }
  }
  screen_refresh();

  change_comm_stack = comm_stack_init;

  xTaskCreate(screen_loop, "screen_loop", configMINIMAL_STACK_SIZE * 10, NULL, 0, NULL);
}

enum gui_name screen_get_name(void)
{
  return head->name;
}

static void screen_loop(void* v)
{
  (void)v;
  for (;;) {
    if (gui_has_changed) {
      screen_refresh();
      if (change_comm_stack != NULL) {
        change_comm_stack(head->name); // change the communication stack
      }
      gui_has_changed = false;
    }
    vTaskDelay(300);
  }
}

static void screen_refresh(void)
{
  display.clearDisplay();
  display.drawBitmap(0, 0, head->bitmap, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  display.display();
}
