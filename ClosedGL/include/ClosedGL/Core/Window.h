#pragma once

#include "ClosedGL/Events/Event.h"

struct GLFWwindow;


struct WindowProps {
	unsigned int width;
	unsigned int height;
	std::string title;
};

class AWindow {

	public:

		AWindow(IEventHandler* eventHandler, const WindowProps& props): pEventHandler(eventHandler), mProps(props) { }
		virtual ~AWindow() = default;

		virtual void init() = 0;
		virtual void update() = 0;
		
		virtual void* native() const = 0;

		WindowProps properties() const { return mProps; };


	protected:

		IEventHandler* pEventHandler { nullptr };
		WindowProps mProps;

};


class GLFWWindow: public AWindow {

	public:
		
		GLFWWindow(IEventHandler* eventHandler, const WindowProps& props = { 1280, 720, "Test" });
		~GLFWWindow();

		virtual void init() override;
		virtual void update() override;

		virtual void* native() const { return pWindow; }

	private:

		EventDispatcher mDispatcher;

		GLFWwindow* pWindow { nullptr };

};