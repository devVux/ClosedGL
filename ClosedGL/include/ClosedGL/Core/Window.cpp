#include "pch.h"

#include "Window.h"

#include "ClosedGL/Events/Event.h"
#include "ClosedGL/Events/WindowEvents.h"
#include "ClosedGL/Events/KeyEvents.h"
#include "ClosedGL/Events/MouseEvents.h"

Window::Window(EventHandler* eventHandler, const WindowProps& props): pEventHandler(eventHandler), mProps(props) {

}

Window::~Window() {
	glfwDestroyWindow(pWindow);
}

void Window::init() {

	int success = glfwInit();
	assert(success == GLFW_TRUE);

	pWindow = glfwCreateWindow(mProps.width, mProps.height, mProps.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);

	glfwSwapInterval(1);

	success = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	assert(success != 0);

	TRACE("Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	TRACE("GPU: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	TRACE("Version GL: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	TRACE("Version GLSL: {}\n", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

	glfwSetErrorCallback([](int error, const char* description) {
		ERRORE("{}: {}", error, description);
	});


	glfwSetWindowUserPointer(pWindow, (void*) pEventHandler);

	glfwSetWindowCloseCallback(pWindow, [](GLFWwindow* window) {
		const auto& eventHandler = (EventHandler*) glfwGetWindowUserPointer(window);
		eventHandler->push(std::make_shared<WindowCloseEvent>());
	});

	glfwSetWindowSizeCallback(pWindow, [](GLFWwindow* window, int w, int h) {
		//const auto& eventHandler = (EventHandler*) glfwGetWindowUserPointer(window);
		//	eventHandler->push(new WindowResizeEvent(w, h));
		glViewport(0, 0, w, h);
	});

	glfwSetKeyCallback(pWindow, [](GLFWwindow* window, int keyCode, int scancode, int action, int mode) {

		const auto& eventHandler = (EventHandler*) glfwGetWindowUserPointer(window);

		switch (action) {

			case GLFW_PRESS:

				eventHandler->push(std::make_shared<KeyPressedEvent>(keyCode));
				break;

			case GLFW_RELEASE:

				eventHandler->push(std::make_shared<KeyReleasedEvent>(keyCode));
				break;

			case GLFW_REPEAT:

				eventHandler->push(std::make_shared<KeyTypedEvent>(keyCode, 1));
				break;

		}

	});

	glfwSetMouseButtonCallback(pWindow, [](GLFWwindow* window, int button, int action, int mods) {

		const auto& eventHandler = (EventHandler*) glfwGetWindowUserPointer(window);

		switch (action) {

			case GLFW_PRESS:
				eventHandler->push(std::make_shared<MouseButtonPressedEvent>(button));
				break;

			case GLFW_RELEASE:
				eventHandler->push(std::make_shared<MouseButtonReleasedEvent>(button));
				break;

		}

	});

	glfwSetCursorPosCallback(pWindow, [](GLFWwindow* window, double x, double y) {

		const auto& eventHandler = (EventHandler*) glfwGetWindowUserPointer(window);
		eventHandler->push(std::make_shared<MouseMovedEvent>(MouseCoord((float) x, (float) y)));

	});

	glfwSetScrollCallback(pWindow, [](GLFWwindow* window, double xOffset, double yOffset) {

		const auto& eventHandler = (EventHandler*) glfwGetWindowUserPointer(window);
		eventHandler->push(std::make_shared<MouseScrolledEvent>((float) xOffset, (float) yOffset));

	});

}

void Window::update() {

	glfwPollEvents();
	glfwSwapBuffers(pWindow);

}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::swapBuffers() {
	glfwSwapBuffers(pWindow);
}