#pragma once

#include <thread>
#include "ClosedGL/Core/Application.h"
#include <ClosedGL/Layers/View.h>
#include <ClosedGL/Layers/Controller.h>
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
	View* view = new View(app);
	view->init();
	Controller* controller = new Controller(app, view);
	eventHandler.registerListener(app);
	app->init();

	app->run();

	eventHandler.stop();
	t.detach();
	
	delete app;
	delete view;
	delete controller;
	delete input;

	return 0;
}

