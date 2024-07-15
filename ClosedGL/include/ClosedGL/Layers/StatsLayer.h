#pragma once

#include "ClosedGL/Layers/Layer.h"

#include "ClosedGL/Core/Application.h"
#include "ClosedGL/Renderer/RenderCommands.h"
#include "ClosedGL/Renderer/Renderer2D.h"

#include "ClosedGL/Core/Clock.h"
#include "ClosedGL/Utils/Observer.h"

#include "imgui.h"
#include "imgui_internal.h"


class StatsLayer: public Layer, public Subject {

	public:

		StatsLayer() {
			t.every(1s, [](float& frames) {
				frames = (float) (1.0f / Time::delta);
			}, fps);
		}

		void update() override {

			ImGui::Begin("Stats");

			ImGui::Text("FPS %.2f", fps);
			//ImGui::Text("Fixed Updates %u", Application::Stats::updates);

			ImGui::Text("Draw calls: %u", RenderCommands::Stats::drawCalls.load());
			ImGui::Text("Polygons: %u", RenderCommands::Stats::polyCount.load());

			ImGui::End();

		}

		NOTIFY

	private:

		Time::Timer t;
		float fps { 0 };

};