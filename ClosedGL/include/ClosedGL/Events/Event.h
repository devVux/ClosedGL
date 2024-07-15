#pragma once

#include <string>
#include <queue>
#include <memory>
#include <mutex>

enum class EventType {
	MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled,
	KeyPressed, KeyReleased, KeyTyped,
	WindowClosed, WindowResized, WindowMoved, WindowLostFocus
};

#define EVENT_TYPE(x)	static EventType staticType() { return EventType::x; } \
						virtual std::string name() const override { return #x; } \
						virtual EventType type() const { return EventType::x; }
#define NOTIFY_ALL() virtual void notifyAll() { for (auto listener : mListeners) if (!listener.expired()) listener.lock()->onEvent(*this); }

class Event;

class EventListener {
	
	public:
		
		~EventListener() = default;

		virtual void onEvent(Event& e) = 0;

};

class Event {

	public:
		
		virtual ~Event() = default;

		virtual std::string name() const = 0;
		virtual EventType type() const = 0;
		
		virtual std::string toString() const { return name(); }

		void accept() { mAccepted = true; }
		void reject() { mAccepted = false; }

		virtual void notifyAll() = 0;

	protected:

		std::vector<std::weak_ptr<EventListener>> mListeners;


	private:

		bool mAccepted;

};

class EventDispatcher {

	public:

		template <class T, class F>
		static void staticDispatch(Event& e, const F&& callback) {
			
			if (e.type() == T::staticType()) {
				e.reject();
				callback(static_cast<T&>(e));
			}

		}
		
		template <class T, class F>
		void dispatch(Event& e, const F&& callback) {
			
			if (e.type() == T::staticType()) {
				e.reject();
				callback(static_cast<T&>(e));
			}

		}

};

class EventHandler {

	public:

		~EventHandler() {
			stop();
		}

		void run() {
			mRunning.store(true);
			while (mRunning.load()) {
				
				{
					// When you sleep after acquiring the lock, 
					// the thread will hold the lock during the sleep period.
					// This is why we scope the mutex block of code.

					std::lock_guard<std::mutex> lock(mMutex);

					if (!mEventQueue.empty()) {
						std::shared_ptr<Event> e = mEventQueue.front();
						mEventQueue.pop();

						for (auto it = mListeners.begin(); it != mListeners.end(); ) {
							if (auto listener = it->lock()) {
								listener->onEvent(*e);
								++it;
							} else
								it = mListeners.erase(it);  // Remove expired listeners
						}
					}
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(1));

			}
		}

		void stop() {
			mRunning.store(false);
		}

		void push(std::shared_ptr<Event> e) {
			std::lock_guard<std::mutex> lock(mMutex);
			mEventQueue.push(e);
		}

		void registerListener(std::weak_ptr<EventListener> listener) {
			std::lock_guard<std::mutex> lock(mMutex);
			mListeners.push_back(std::move(listener));
		}


	private:

		std::queue<std::shared_ptr<Event>> mEventQueue;
		std::vector<std::weak_ptr<EventListener>> mListeners;

		std::mutex mMutex;

		std::atomic<bool> mRunning { false };

};
