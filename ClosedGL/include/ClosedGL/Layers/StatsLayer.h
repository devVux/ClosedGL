#pragma once


#include "ClosedGL/Layers/Layer.h"
#include "ClosedGL/Core/Timestep.h"
#include "ClosedGL/Utils/Observer.h"

#include "imgui.h"
#include "imgui_internal.h"

class StatsLayer: public Layer, public Subject {

	public:

		void update(Timestep ts);

		virtual void notify() override {
			std::for_each(std::begin(mObservers), std::end(mObservers), [](Observer* observer) {
				observer->update();
			});
		}

};	 