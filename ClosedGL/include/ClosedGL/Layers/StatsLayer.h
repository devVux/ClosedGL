#pragma once

#include "ClosedGL/Renderer/Batch.h"
#include "ClosedGL/Layers/Layer.h"

#include "imgui.h"
#include "imgui_internal.h"

class StatsLayer: public Layer {

	public:
		
		void update(const Stats& stats) {

			ImGui::Text("%hu", stats.drawCalls);
			ImGui::Text("%hu", stats.fps);

		}

};	 