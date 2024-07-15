#pragma once

#include <memory>

template <class T>
using Ref = std::shared_ptr<T>;

template <class T>
using Scope = std::unique_ptr<T>;

template <class T, class... Args>
inline Ref<T> makeRef(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template <class T, class... Args>
inline Scope<T> makeScope(Args&&... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}


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

template <class T>
struct Coords {
	T x;
	T y;
	T width;
	T height;
};
