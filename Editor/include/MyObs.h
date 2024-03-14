#pragma once

#include <vector>
#include <algorithm>

template <class T>
class Observer {

	public:

		virtual ~Observer() = default;

		virtual void notify(const T&) = 0;

};

template <class T>
class Subject {

	public:

		virtual void notifyAll() = 0;

		void registerObserver(Observer<T>* observer) {
			mObservers.push_back(observer);
		}

	protected:

		std::vector<Observer<T>*> mObservers;

};