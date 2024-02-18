#pragma once

#include "ClosedGL/Layers/Layer.h"

#include "ClosedGL/Core/Application.h"
#include "ClosedGL/Renderer/Renderer2D.h"

#include "ClosedGL/Core/Clock.h"
#include "ClosedGL/Utils/Observer.h"

#include "imgui.h"
#include "imgui_internal.h"


class StatsLayer: public Layer, public Subject {

	public:

		StatsLayer() {
			t.every(1s, [](float& frames) {
				frames = 1.0f / Time::delta;
			}, fps);
		}

		void update() override {

			ImGui::Begin("Stats");

			ImGui::Text("FPS %.2f", fps);
			//ImGui::Text("Fixed Updates %u", Application::Stats::updates);

			ImGui::Text("Draw calls: %u", Renderer2D::Stats::drawCalls);
			ImGui::Text("Polygons: %u", Renderer2D::Stats::polyCount);

			ImGui::End();

		}

		virtual void notify() override {
			std::for_each(std::begin(mObservers), std::end(mObservers), [](Observer* observer) {
				observer->update();
				});
		}

	private:

		Timer t;
		float fps { 0 };

};