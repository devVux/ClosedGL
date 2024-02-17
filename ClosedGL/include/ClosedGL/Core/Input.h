#pragma once

#include <GLFW/glfw3.h>

#include "ClosedGL/Events/KeyEvents.h"
#include "ClosedGL/Events/MouseEvents.h"
#include "ClosedGL/Core/Window.h"

class GLFWWindow;

class IInput {

	public:

		virtual bool isKeyDown(Keys keyCode) const = 0;
		virtual bool isMouseButtonDown(MouseButtons button) const = 0;
		virtual MouseCoord mousePos() const = 0;

};


class Input {

	public:

		static bool isKeyDown(Keys keyCode) {
			return pInput->isKeyDown(keyCode);
		}

		static bool isMouseButtonDown(MouseButtons button) {
			return pInput->isMouseButtonDown(button);
		}

		static MouseCoord mousePos() {
			return pInput->mousePos();
		}

		static void setInputMode(IInput* input) {
			if (input != nullptr)
				pInput = input;
		}

	private:

		static IInput* pInput;

};



class GLFWInput: public IInput {

	public:

		GLFWInput(Window* window): pWindow(window) { }

		virtual bool isKeyDown(Keys keyCode) const;

		virtual bool isMouseButtonDown(MouseButtons button) const;

		virtual MouseCoord mousePos() const;

	private:

		Window* pWindow;

};
