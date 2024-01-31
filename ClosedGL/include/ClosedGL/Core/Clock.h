#pragma once

#include <chrono>

using namespace std::chrono;

struct Timestep {

	double delta;

	Timestep(double deltaTime = 0.0f): delta(deltaTime) {}

	Timestep& operator=(const Timestep& other) {
		if (&other != this)
			delta = other.delta;
		return *this;
	}	
	Timestep& operator+=(const Timestep& other) {
		delta += other.delta;
		return *this;
	}	
	Timestep& operator-=(const Timestep& other) {
		delta -= other.delta;
		return *this;
	}

	operator double() const { return delta; }

};

class Clock {
	
	public:

		static void reset() {
			mStart = getCurrentTime();
			mLastUpdate = mStart;
			mTickInterval = 1.0f / 60.0f;
		}

		// Set the tick interval in seconds
		static void setTickInterval(double interval) {
			mTickInterval = interval;
		}

		static Timestep tickInterval() {
			return mTickInterval;
		}

		// Get the elapsed time in seconds since the last tick
		static Timestep tick() {
			Timestep now = getCurrentTime();
			Timestep duration = now - Clock::mLastUpdate;
			Clock::mLastUpdate = now;
			return duration;
		}

		// Get the total elapsed time in seconds since the program started
		static Timestep elapsed() {
			return getCurrentTime() - mStart;
		}

	private:

		static Timestep getCurrentTime() {
			return duration_cast<duration<double>>(high_resolution_clock::now().time_since_epoch()).count();
		}


	private:

		static Timestep mStart;
		static Timestep mLastUpdate;
		static Timestep mTickInterval;

};
