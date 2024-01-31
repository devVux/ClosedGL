#pragma once

#include "ClosedGL/Layers/LayerStack.h"

#include "ClosedGL/Layers/ImGuiController.h"
#include "ClosedGL/Layers/StatsLayer.h"

#include "ClosedGL/Utils/Observer.h"

class Application;

class View: public Observer, public Subject {

	public:

		View(Application* model);
		~View() {
			destroy();
			delete pStatsLayer;
		}
		
		virtual void update() override;
		
		virtual void notify() override {
			std::for_each(std::begin(mObservers), std::end(mObservers), [](Observer* const observer) {
				observer->update();
			});
		}

		void init();
		void destroy();
		void begin();
		void end();

	private:

		Application* mModel;

		StatsLayer* pStatsLayer { new StatsLayer };
		
		LayerStack mLayers;

};