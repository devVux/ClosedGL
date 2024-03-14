#pragma once

#include "Window.h"
#include "ClosedGL/Events/Event.h"

#include "ClosedGL/Scene/Scene.h"

#include <Physiks/World.h>

#include <algorithm>

#include "ClosedGL/Scene/PerspectiveCamera.h"

class Application: public EventListener {

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


		GLFWwindow* nativeWindow() const { return pWindow->native(); }
		bool isRunning() const { return mRunning; }
		void stop() { mRunning = false; }
	private:

		Window* pWindow;
		EventDispatcher mDispatcher;

		Scene mScene;
		
		bool mRunning { false };
	
	protected:

		World mWorld;
	

	private:

		static Application* sInstance;
	
};

namespace ClosedGL {
	
	extern Application* create(Window* window);

}
