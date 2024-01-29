#pragma once

#include <thread>
#include "ClosedGL/Core/Application.h"
#include "ClosedGL/Core/Input.h"

extern Application* ClosedGL::create(AWindow* window);

int main() {

	Log::init();

	EventHandler eventHandler;
	std::thread t([&eventHandler]() {
		eventHandler.run();
	});

	GLFWWindow* window = new GLFWWindow(&eventHandler);

	GLFWInput* input = new GLFWInput(window);
	Input::setInputMode(input);

	auto app = ClosedGL::create(window);
	eventHandler.registerListener(app);
	app->init();

	TRACE(Input::isKeyDown(Keys::APOSTROPHE));
	app->run();

	eventHandler.stop();
	t.detach();
	
	delete app;
	delete input;

	return 0;
}

