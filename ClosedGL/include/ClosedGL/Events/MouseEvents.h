#pragma once
#include "pch.h"
#include "Event.h"

#include "ClosedGL/Utils/Utils.h"
#include <sstream>

class MouseButtonEvent: public Event {

	public:

		int button() const { return mButton; }

	protected:

		MouseButtonEvent(int button): mButton(button) {}

		NOTIFY_ALL()

	protected:

		int mButton;

};

class MouseButtonPressedEvent: public MouseButtonEvent {

	public:

		MouseButtonPressedEvent(int button): MouseButtonEvent(button) {}


		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mButton;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonPressed)

		NOTIFY_ALL()

};

class MouseButtonReleasedEvent: public MouseButtonEvent {

	public:

		MouseButtonReleasedEvent(int button): MouseButtonEvent(button) {}

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mButton;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonReleased)

		NOTIFY_ALL()

};

class MouseMovedEvent: public Event {
	
	public:

		MouseMovedEvent(MouseCoord c): mPos(c) {}

		MouseCoord pos() const { return mPos; }
		float x() const { return mPos.x; }
		float y() const { return mPos.y; }
		
		void setCoords(MouseCoord coords) { mPos = coords; }

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << mPos.x << ", " << mPos.y << ")";
			return ss.str();
		}

		EVENT_TYPE(MouseMoved)

		NOTIFY_ALL()

	private:
		
		MouseCoord mPos;

};
 

class MouseScrolledEvent: public Event {

	public:

		MouseScrolledEvent(float xOff, float yOff): mXOffset(xOff), mYOffset(yOff) { }

		float xOffset() const { return mXOffset; }
		float yOffset() const { return mYOffset; }

		virtual std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << mXOffset << ", " << mYOffset << ")";
			return ss.str();
		}

		EVENT_TYPE(MouseScrolled)
		
		NOTIFY_ALL()

	private:
		
		float mXOffset;
		float mYOffset;

};