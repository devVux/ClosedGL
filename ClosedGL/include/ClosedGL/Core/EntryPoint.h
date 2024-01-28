#pragma once

#include <thread>
#include "ClosedGL/Core/Application.h"

extern Application* ClosedGL::create(IEventHandler* eventHandler);

int main() {

	Log::init();

	EventHandler eventHandler;
	std::thread t([&eventHandler]() {
		eventHandler.run();
	});

	auto app = ClosedGL::create(&eventHandler);
	eventHandler.registerListener(app);
	app->init();

	app->run();

	delete app;
	
	t.detach();

	return 0;
}

