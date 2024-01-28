#pragma once

#include <GLFW/glfw3.h>

#include "ClosedGL/Utils/Utils.h"
#include "Application.h"

namespace Input {

	static bool isKeyDown(int keyCode) {
		return glfwGetKey(NATIVE_WINDOW, keyCode) == GLFW_PRESS;
	}

	static bool isMouseButtonDown(int button) {
		return glfwGetMouseButton(NATIVE_WINDOW, button) == GLFW_PRESS;
	}

	static MouseCoord mousePos() {
		double x, y;
		glfwGetCursorPos(NATIVE_WINDOW, &x, &y);
		return MouseCoord{ static_cast<float>(x), static_cast<float>(y) };
	}

}