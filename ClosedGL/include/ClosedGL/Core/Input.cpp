#include "pch.h"
#include "Input.h"

#include "ClosedGL/Core/Window.h"

IInput* Input::pInput = nullptr;

GLFWInput::GLFWInput(GLFWWindow* window): pWindow(window) {

}

bool GLFWInput::isKeyDown(Keys keyCode) const {
	return glfwGetKey(static_cast<GLFWwindow*>(pWindow->native()), keyCode) == GLFW_PRESS;
}

bool GLFWInput::isMouseButtonDown(MouseButtons button) const {
	return glfwGetMouseButton(static_cast<GLFWwindow*>(pWindow->native()), button) == GLFW_PRESS;
}

MouseCoord GLFWInput::mousePos() const {
	double x, y;
	glfwGetCursorPos(static_cast<GLFWwindow*>(pWindow->native()), &x, &y);
	return MouseCoord { static_cast<float>(x), static_cast<float>(y) };
}