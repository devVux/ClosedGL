#pragma once

#include <atomic>

namespace RenderCommands {

	namespace Stats {

		extern std::atomic_uint32_t drawCalls;
		extern std::atomic_uint32_t polyCount;

		inline void incrementDrawCalls() { Stats::drawCalls++; }
		inline void incrementPolyCount() { Stats::polyCount++; }
		inline void reset() {
			Stats::drawCalls = 0;
			Stats::polyCount = 0;
		}

	}

	 void clear(float r = 0.2f, float g = 0.2f, float b = 0.2f);

}