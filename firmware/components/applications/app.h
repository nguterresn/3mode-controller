#ifndef APP_H_
#define APP_H_

#include "comm_stack_config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct app {
  void (*init)();
  void (*deinit)();
  int  (*send)(struct js_stamp* stamp);
  int  (*recv)();
};

void app_install(struct app* app, void (*init)(), void (*deinit)(), int (*send)(struct js_stamp* stamp), int (*recv)());
void app_next(struct app* app);

void app_send(struct js_stamp* stamp);

#ifdef __cplusplus
}
#endif

#endif /* APP_H_ */
