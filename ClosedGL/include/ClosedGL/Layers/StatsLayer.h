#pragma once

#include "ClosedGL/Layers/Layer.h"

#include "ClosedGL/Renderer/Renderer2D.h"

#include "ClosedGL/Core/Clock.h"
#include "ClosedGL/Utils/Observer.h"

#include "imgui.h"
#include "imgui_internal.h"

class StatsLayer: public Layer, public Subject {

	public:

		void update() override {

			ImGui::Begin("Stats");

			float fps = (float) 1 / Clock::tickInterval();
			if (ImGui::SliderFloat("FPS", &fps, 1, 250))
				Clock::setTickInterval(1 / fps);

			ImGui::Text("Draw calls: %u", Renderer2D::RendererStats::drawCalls);
			ImGui::Text("Polygons: %u", Renderer2D::RendererStats::polyCount);

			ImGui::End();

		}

		virtual void notify() override {
			std::for_each(std::begin(mObservers), std::end(mObservers), [](Observer* observer) {
				observer->update();
			});
		}

};	 