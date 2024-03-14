#pragma once



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
