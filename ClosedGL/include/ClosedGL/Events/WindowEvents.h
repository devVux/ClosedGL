#pragma once
#include "pch.h"
#include "Event.h"

#include <sstream>

class WindowCloseEvent: public Event {

	public:
	
		NOTIFY_ALL()

		EVENT_TYPE(WindowClosed)
		
};

class WindowResizeEvent: public Event {

	public:
		
		WindowResizeEvent(int width, int height): mWidth(width), mHeight(height) {}

		int width() const { return mWidth; }
		int height() const { return mHeight; }

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << mWidth << 'x' << mHeight;
			return ss.str();
		}
		
		NOTIFY_ALL()

		EVENT_TYPE(WindowResized)

	private:

		int mWidth;
		int mHeight;
	
};
