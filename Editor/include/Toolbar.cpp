#include "Toolbar.h"

#include "imgui.h"
#include <IconsFontAwesome5.h>

static constexpr ImVec2 buttonSize { 55, 31 };

void Toolbar::update() {

	ImGui::Begin("Toolbar");
	{

		// on play
		if (ImGui::Button(ICON_FA_PLAY, buttonSize)) {
			mPlaying = true;
			listener->onPlayPressed();
		}

		ImGui::SameLine();

		if (mPlaying) {

			// on stop
			if (ImGui::Button(ICON_FA_STOP, buttonSize)) {
				mPlaying = false;
				listener->onStopPressed();
			}

			ImGui::SameLine();

			// on pause
			if (ImGui::Button(ICON_FA_PAUSE, buttonSize)) {
				listener->onPausePressed();
			}

		}

	} ImGui::End();

}
