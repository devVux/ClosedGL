#pragma once

#define NATIVE_WINDOW static_cast<GLFWwindow*>(Application::instance().window()->nativeWindow())

struct MouseCoord {
	float x;
	float y;

	MouseCoord(float _x, float _y) : x(_x), y(_y) { }

	bool operator==(const MouseCoord& other) const {
		return x == other.x && y == other.y;
	}
	
	bool operator!=(const MouseCoord& other) const {
		return !(*this == other);
	}

};

struct Coords {
	float x;
	float y;
	float width;
	float height;
};

struct Stats {
	uint32_t fps;
	uint32_t drawCalls;
	uint32_t polyCount;
};