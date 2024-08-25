#include "app.h"

void app_install(struct app* app, void (*init)(), void (*deinit)(),
                 int (*send)(struct js_stamp* stamp), int (*recv)())
{
	app->init   = init;
	app->deinit = deinit;
	app->send   = send;
	app->recv   = recv;
}
