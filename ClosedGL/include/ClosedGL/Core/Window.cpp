#include "pch.h"

#include "Window.h"

#include "ClosedGL/Events/Event.h"
#include "ClosedGL/Events/WindowEvents.h"
#include "ClosedGL/Events/KeyEvents.h"
#include "ClosedGL/Events/MouseEvents.h"

Window::Window(IEventHandler* eventHandler, const WindowProps& props): mEventHandler(eventHandler), mProps(props), window(nullptr) {
	
}

Window::~Window() {
	glfwDestroyWindow(window);
	delete mEventHandler;
}

void Window::init() {

	int success = glfwInit();
	assert(success != 0);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	window = glfwCreateWindow(mProps.width, mProps.height, mProps.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	success = gladLoadGL();
	assert(success != 0);

	glViewport(0, 0, mProps.width, mProps.height);

	glfwSwapInterval(1);

	glfwSetErrorCallback([](int error, const char* description) {
		//ERRORE("{}: {}", error, description);
	});

	glfwSetWindowUserPointer(window, (void*) mEventHandler);

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		
		const auto& eventHandler = (IEventHandler*) glfwGetWindowUserPointer(window);
		eventHandler->push(new WindowCloseEvent);

	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int keyCode, int scancode, int action, int mode) {
		
		const auto& eventHandler = (IEventHandler*) glfwGetWindowUserPointer(window);

		switch (action) {

			case GLFW_PRESS:
			
				eventHandler->push(new KeyPressedEvent(keyCode));
				break;

			case GLFW_RELEASE:
			
				eventHandler->push(new KeyReleasedEvent(keyCode));
				break;

			case GLFW_REPEAT:
				
				eventHandler->push(new KeyTypedEvent(keyCode, 1));
				break;

		}

	});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		//const auto& eventHandler = (IEventHandler*) glfwGetWindowUserPointer(window);
		//	eventHandler->push(new WindowResizeEvent(w, h));
		glViewport(0, 0, w, h);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {

		const auto& eventHandler = (IEventHandler*) glfwGetWindowUserPointer(window);

		switch (action) {
			
			case GLFW_PRESS:
				eventHandler->push(new MouseButtonPressedEvent(button));
				break;

			case GLFW_RELEASE:
				eventHandler->push(new MouseButtonReleasedEvent(button));
				break;

		}
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {

		const auto& eventHandler = (IEventHandler*) glfwGetWindowUserPointer(window);
		eventHandler->push(new MouseMovedEvent({ (float) x, (float) y}));

	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {

		const auto& eventHandler = (IEventHandler*) glfwGetWindowUserPointer(window);
		eventHandler->push(new MouseScrolledEvent((float) xOffset, (float) yOffset));

	});

}

void Window::update() {
		
	glfwPollEvents();
	glfwSwapBuffers(window);

}
