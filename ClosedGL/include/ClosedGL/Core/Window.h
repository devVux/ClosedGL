#pragma once

#include "ClosedGL/Events/Event.h"

struct GLFWwindow;

struct WindowProps {
	uint32_t width;
	uint32_t height;
	std::string title;
};

class Window {

	public:
		
		Window(EventHandler* eventHandler, const WindowProps& props = { 1280, 720, "Test" });
		~Window();

		void init();
		void update();

		void pollEvents();
		void swapBuffers();

		GLFWwindow* native() const { return pWindow; }

	private:

		EventDispatcher mDispatcher;
		EventHandler* pEventHandler;

		GLFWwindow* pWindow { nullptr };
		WindowProps mProps;

};