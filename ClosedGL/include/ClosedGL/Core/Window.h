#pragma once

#include "ClosedGL/Events/Event.h"

struct GLFWwindow;

struct WindowProps {
	unsigned int width;
	unsigned int height;
	std::string title;

	WindowProps(unsigned int w, unsigned int h, std::string t):
		width(w), height(h), title(t) {}

};

class Window {

	public:
		
		Window(IEventHandler* eventHandler, const WindowProps& props = WindowProps(1280, 720, "Test"));
		~Window();

		void init();
		
		void update();

		WindowProps properties() const { return mProps; }
		void* nativeWindow() const { return window; }

	private:

		IEventHandler* mEventHandler;

		GLFWwindow* window;

		WindowProps mProps;

		EventDispatcher mDispatcher;

};