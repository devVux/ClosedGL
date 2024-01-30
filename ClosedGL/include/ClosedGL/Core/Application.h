#pragma once

#include "Window.h"
#include "ClosedGL/Events/Event.h"

#include "ClosedGL/Renderer/Renderer.h"

#include <Physiks/World.h>

#include "ClosedGL/Utils/Observer.h"
#include <algorithm>

class Application: public EventListener, public Subject {

	public:

		static Application& instance() { return *sInstance; }

		Application(AWindow* window);
		virtual ~Application() {
			delete pWindow;
		}

		void init();

		virtual void run();
		virtual void update(Timestep ts) {}
		void onEvent(Event& e) override;
		

		virtual void notify() override {
			std::for_each(std::begin(mObservers), std::end(mObservers), [](Observer* observer) {
				observer->update();
			});
		}

		void* nativeWindow() const { return pWindow->native(); }

	private:

		AWindow* pWindow;
		EventDispatcher mDispatcher;


		
		bool mRunning { false };
	
	protected:

		World mWorld;
	

	private:

		static Application* sInstance;
	
};

namespace ClosedGL {
	
	extern Application* create(AWindow* window);

}
