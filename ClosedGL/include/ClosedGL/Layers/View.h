#pragma once

#include "ClosedGL/Layers/LayerStack.h"

#include "ClosedGL/Layers/ImGuiController.h"
#include "ClosedGL/Layers/StatsLayer.h"

#include "ClosedGL/Utils/Observer.h"

class Application;

class View: public Observer, public Subject {

	public:

		View(Ref<Application> model);
		~View() {
			destroy();
			delete pStatsLayer;
		}
		
		virtual void update() override;
		
		NOTIFY

		void init();
		void destroy();
		void begin();
		void end();

	private:

		StatsLayer* pStatsLayer { new StatsLayer };
		
		LayerStack mLayers;

};