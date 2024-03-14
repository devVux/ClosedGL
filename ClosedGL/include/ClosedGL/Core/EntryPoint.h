#pragma once

#include <thread>
#include "ClosedGL/Core/Application.h"
#include "ClosedGL/Core/Input.h"

extern Application* ClosedGL::create(Window* window);

int main() {

	Log::init();

	EventHandler eventHandler;
	std::thread t([&eventHandler]() {
		eventHandler.run();
	});

	Window window(&eventHandler);
	window.init();

	GLFWInput* input = new GLFWInput(&window);
	Input::setInputMode(input);

	auto app = ClosedGL::create(&window);
	eventHandler.registerListener(app);

	app->run();

	eventHandler.stop();
	t.detach();
	
	delete app;
	delete input;

	return 0;
}

