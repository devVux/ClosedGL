#pragma once

#include <thread>
#include "ClosedGL/Core/Application.h"
#include <ClosedGL/Layers/View.h>
#include <ClosedGL/Layers/Controller.h>
#include <ClosedGL/Core/Input.h>
#include <ClosedGL/Core/Managers/TextureManager.h>

extern Application* ClosedGL::create(Window* window);

int main() {

	Log::init();

	EventHandler eventHandler;
	std::thread t([&eventHandler]() {
		eventHandler.run();
	});
	t.detach();


	Window window(&eventHandler);
	window.init();

	GLFWInput input(&window);
	Input::setInput(&input);



	auto app = Ref<Application>(ClosedGL::create(&window));
	app->init();

	
	eventHandler.registerListener(app);
	
	View view(app);
	view.init();


	app->run();

	

	return 0;
}

