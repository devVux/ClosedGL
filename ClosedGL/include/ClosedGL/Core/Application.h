#pragma once

#include "Window.h"
#include "ClosedGL/Events/Event.h"

#include "ClosedGL/Renderer/Renderer.h"
#include "ClosedGL/Scene/Scene.h"

#include <Physiks/World.h>

#include "ClosedGL/Utils/Observer.h"
#include <algorithm>

class Application: public EventListener, public Subject {

	public:

		struct Stats {

			static uint32_t updates;
			static uint32_t frameNr;

			static void reset() {
				updates = 0;
				frameNr = 0;
			}

		};

	public:

		static Application& instance() { return *sInstance; }

		Application(Window* window);
		virtual ~Application() {
			
		}

		void init();

		virtual void run();
		void render(Timestep ts);
		void onEvent(Event& e) override;


		virtual void notify() override {
			std::for_each(std::begin(mObservers), std::end(mObservers), [](Observer* observer) {
				observer->update();
			});
		}

		GLFWwindow* nativeWindow() const { return pWindow->native(); }

	private:

		Window* pWindow;
		EventDispatcher mDispatcher;

		Scene mScene;
		
		bool mRunning { false };
	
	protected:

		World mWorld;
		OrthographicCamera mCamera;
	

	private:

		static Application* sInstance;
	
};

namespace ClosedGL {
	
	extern Application* create(Window* window);

}
