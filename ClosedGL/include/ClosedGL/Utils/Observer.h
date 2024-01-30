#pragma once

#include <vector>
#include <algorithm>

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