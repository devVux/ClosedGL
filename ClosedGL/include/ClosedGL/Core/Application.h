#pragma once

#include "Window.h"
#include "ClosedGL/Events/Event.h"

#include "ClosedGL/Renderer/Renderer.h"
#include "ClosedGL/Layers/LayerStack.h"

#include <Physiks/World.h>

class Application: public EventListener {

	public:

		static Application& instance() { return *sInstance; }

		Application(AWindow* window);
		virtual ~Application() {
			
		}

		void init();

		virtual void run();
		virtual void update(Timestep ts) {}
		void onEvent(Event& e) override;
		

		AWindow* window() const { return pWindow; }
		void* nativeWindow() const { return pWindow->native(); }

	private:

		AWindow* pWindow;
		EventDispatcher mDispatcher;

		// layer stack will call delete
		class ImGuiLayer* pImGuiLayer;
		class StatsLayer* pStatsLayer;
		
		bool mRunning { false };
	
	protected:

		World mWorld;
	
		LayerStack mLayers;

	private:

		static Application* sInstance;
	
};

namespace ClosedGL {
	
	extern Application* create(AWindow* window);

}
