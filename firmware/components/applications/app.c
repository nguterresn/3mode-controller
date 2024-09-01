#include "app.h"

static struct app* _app;

void app_install(struct app* app, void (*init)(), void (*deinit)(),
                 int (*send)(struct js_stamp* stamp), int (*recv)())
{
	app->init   = init;
	app->deinit = deinit;
	app->send   = send;
	app->recv   = recv;
}

void app_next(struct app* app)
{
	if (_app == app) {
		return;
	}

	if (_app) {
		// Only deinit if there was a app installed.
		_app->deinit();
	}
	if (!app) {
		// app_next(NULL) will deinit the latest installed app and nothing else.
		return;
	}
	_app = app;
	_app->init();
}

void app_send(struct js_stamp* stamp)
{
	if (_app && _app->send) {
		_app->send(stamp);
	}
}
