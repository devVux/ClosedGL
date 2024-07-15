#pragma once

#include <vector>
#include <memory>

class Observer {
	
	public:

		virtual ~Observer() = default;

		virtual void update() = 0;

};

class Subject {

	public:

		virtual void notify() = 0;

		void registerObserver(Observer* observer) {
			mObservers.push_back(observer);
		}

	protected:

		std::vector<Observer*> mObservers;

};

#define NOTIFY \
	virtual void notify() override { \
		for (auto observer : mObservers) \
				observer->update(); \
		}
