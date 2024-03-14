#include "SceneView.h"

#define IM_VEC2_CLASS_EXTRA \
    ImVec2(glm::vec2& f): x(f.x), y(f.y) {} \
    bool operator==(const ImVec2& other) const { return x == other.x && y == other.y; } \
    bool operator!=(const ImVec2& other) const { return !(*this == other); } \
    operator glm::vec2() const { return glm::vec2(x, y); }

#include "imgui.h"
#include "imgui_internal.h"
#include "IconsFontAwesome5.h"

void SceneView::update() {

	ImVec2 mSize { 400, 300 };

	ImGui::Begin("Scene");
	{

		ImVec2 size = ImGui::GetWindowSize();

		if (mSize != size) {
			mSize = size;
			mFrameBuffer.resize(mSize);
		}

		if (!f) mFrameBuffer.bind();

		if (ImGui::IsWindowFocused())
			camera.update(0.01f);


		Renderer2D::beginScene(camera);
		Renderer2D::clear();

		scene.update(0.01f);

		Renderer2D::endScene();

		ImGui::Image((ImTextureID) mFrameBuffer.colorAttachment(), mSize);

		mFrameBuffer.unbind();

	} ImGui::End();


}
