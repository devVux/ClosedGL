#pragma once

#include "Window.h"
#include "ClosedGL/Events/Event.h"

#include "ClosedGL/Renderer/Renderer.h"
#include "ClosedGL/Layers/LayerStack.h"

#include <Physiks/World.h>

class Application: public EventListener {

	public:

		static Application& instance() { return *sInstance; }

		Application(IEventHandler* eventHandler);
		virtual ~Application() {
			delete pWindow;
		}

		void init();

		virtual void run();
		virtual void update(Timestep ts) {}
		void onEvent(Event& e) override;
		

		Window* window() const { return pWindow; }

	private:

		Window* pWindow;
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
	
	extern Application* create(IEventHandler* eventHandler);

}
