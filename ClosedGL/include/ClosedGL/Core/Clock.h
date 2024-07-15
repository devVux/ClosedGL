#pragma once

#include <chrono>
#include <cassert>

using namespace std::chrono;


	struct Timestep {

		double delta;

		Timestep(double deltaTime = 0.0): delta(deltaTime) { }

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


namespace Time {

	extern Timestep delta;


	class Clock {

		public:

			Clock(uint32_t n = 10): mStart(getCurrentTime()), mLastUpdate(mStart), mTickInterval(1.0f / n) { }

			// Set the tick interval in seconds
			void setTickInterval(double interval) {
				mTickInterval = interval;
			}

			Timestep tickInterval() {
				return mTickInterval;
			}

			// Get the elapsed time in seconds since the last tick
			Timestep tick() {
				Timestep now = getCurrentTime();
				Timestep duration = now - mLastUpdate;
				mLastUpdate = now;
				return duration;
			}

			// Get the total elapsed time in seconds since the program started
			Timestep elapsed() {
				return getCurrentTime() - mStart;
			}


		private:

			Timestep getCurrentTime() {
				return duration_cast<duration<double>>(high_resolution_clock::now().time_since_epoch()).count();
			}


		private:

			Timestep mStart;
			Timestep mLastUpdate;
			Timestep mTickInterval;

	};

	class Timer {

		public:

			~Timer() {
				mRunning = false;
			}

			template <class Rep, class Period, class F, class ...Args>
			void every(std::chrono::duration<Rep, Period> time, F&& fn, Args&&... args) {

				assert(mRunning == false && "Timer already running");

				mRunning = true;

				t = std::thread([this, time, &fn, &args...]() {

					Timestep elapsed;
					Timestep target(static_cast<float>(time.count()));

					while (mRunning) {

						elapsed += mClock.tick();
						if (elapsed >= target) {

							fn(std::forward<Args>(args)...);
							elapsed -= target;

						}

					}

					});

				t.detach();

			}

			template <class Rep, class Period, class F, class ...Args>
			void after(std::chrono::duration<Rep, Period> time, F&& fn, Args&&... args) {

				assert(mRunning == false && "Timer already running");

				mRunning = true;

				t = std::thread([this, time, &fn, &args...]() {

					Timestep elapsed;
					Timestep target(static_cast<float>(time.count()));

					while (mRunning) {

						elapsed += mClock.tick();
						if (elapsed >= target) {
							fn(std::forward<Args>(args)...);
							mRunning = false;
						}

					}

					});

				t.detach();

			}

		private:

			bool mRunning { false };
			std::thread t;

			Clock mClock;

	};

};
