#pragma once

#include "Window.h"
#include "ClosedGL/Events/Event.h"

#include "ClosedGL/Core/Managers/SceneManager.h"
#include "ClosedGL/Core/Managers/TextureManager.h"

#include "ClosedGL/Scene/OrthographicCamera.h"
#include "ClosedGL/Scene/PerspectiveCamera.h"

#include <box2d/b2_world.h>

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


		NOTIFY

		GLFWwindow* nativeWindow() const { return pWindow->native(); }

	private:


		Window* pWindow;
		EventDispatcher mDispatcher;

		bool mRunning { false };
	
	protected:

		b2World mWorld;
		OrthographicCamera mCamera;
	
		SceneManager mSceneManager;
		TextureManager mTextureManager;

	private:

		static Application* sInstance;
	
};

namespace ClosedGL {
	
	extern Application* create(Window* window);

}
