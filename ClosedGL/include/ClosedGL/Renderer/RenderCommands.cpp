#include "pch.h"
#include "RenderCommands.h"


std::atomic_uint32_t RenderCommands::Stats::drawCalls = 0;
std::atomic_uint32_t RenderCommands::Stats::polyCount = 0;

void RenderCommands::clear(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}