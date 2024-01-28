#pragma once

#include <thread>
#include "ClosedGL/Core/Application.h"

extern Application* ClosedGL::create(AWindow* window);

int main() {

	Log::init();

	EventHandler eventHandler;
	std::thread t([&eventHandler]() {
		eventHandler.run();
	});

	GLFWWindow* window = new GLFWWindow(&eventHandler);

	auto app = ClosedGL::create(window);
	eventHandler.registerListener(app);
	app->init();

	app->run();

	eventHandler.stop();
	t.detach();
	
	delete app;

	return 0;
}

