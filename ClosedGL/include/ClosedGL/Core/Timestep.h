#pragma once

struct Timestep {

	const float delta;

	Timestep(float deltaTime = 0.0f): delta(deltaTime) {}

	operator float() const { return delta; }

};
