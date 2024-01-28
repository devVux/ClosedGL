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
#define NOTIFY_ALL() virtual void notifyAll() { for (EventListener* listener : mListeners) listener->onEvent(*this); }

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

		std::vector<EventListener*> mListeners;


	private:

		bool mAccepted;

};

class EventDispatcher {

	public:

		/*
		@param callback: deve accettare come parametro T&
		*/
		template <class T, class F>
		static void staticDispatch(Event& e, const F& callback) {
			
			if (dynamic_cast<T*>(&e) != nullptr) {
				e.reject();
				callback(static_cast<T&>(e));
			}

		}
		
		template <class T, class F>
		void dispatch(Event& e, const F&& callback) {

			
			if (dynamic_cast<T*>(&e) != nullptr) {
				e.reject();
				callback(static_cast<T&>(e));
			}

		}

};


class IEventHandler {

	public:

		virtual ~IEventHandler() = default;

		virtual void push(Event* e) = 0;

};

class EventHandler: public IEventHandler {

	public:

		~EventHandler() {
			std::lock_guard guard(mMutex);
			while (!mEventQueue.empty()) {
				delete mEventQueue.back();
				mEventQueue.pop();
			}
		}

		void run() {
			mRunning = true;
			while (mRunning) {
				mMutex.lock();

				if (!mEventQueue.empty()) {
					Event* e = mEventQueue.front();
					for (auto& listener : mListeners)
						listener->onEvent(*e);

					delete e;
					mEventQueue.pop();
				}
				mMutex.unlock();
				//std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		}
		void stop() {
			std::lock_guard<std::mutex> lock(mMutex);
			mRunning = false;
		}

		void push(Event* e) {
			std::lock_guard<std::mutex> lock(mMutex);
			mEventQueue.push(e);
		}

		void registerListener(EventListener* listener) {
			mListeners.insert(mListeners.begin(), listener);
		}

	private:

		std::queue<Event*> mEventQueue;
		std::vector<EventListener*> mListeners;

		mutable std::mutex mMutex;

		bool mRunning;

};
