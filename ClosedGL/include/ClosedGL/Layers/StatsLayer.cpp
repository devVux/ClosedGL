#include "pch.h"
#include "ClosedGL/Layers/StatsLayer.h"

#include "ClosedGL/Renderer/Renderer2D.h"

void StatsLayer::update(Timestep ts) {

	ImGui::Text("FPS: %.2f", 1 / ts);
	ImGui::Text("draw calls: %u", Renderer2D::RendererStats::drawCalls);
	ImGui::Text("Polygons: %u", Renderer2D::RendererStats::polyCount);

}