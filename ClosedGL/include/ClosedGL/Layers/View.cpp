#include "pch.h"
#include "View.h"

#include "ClosedGL/Core/Application.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

View::View(Application* model): mModel(model) {
	model->registerObserver(this);
	pStatsLayer->registerObserver(this);
}

// on application update
void View::update() {

	begin();

	mLayers.updateOverlays();
	mLayers.updateLayers();
	
	pStatsLayer->update();

	end();

}

void View::init() {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void) io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::instance().nativeWindow()), true);
	ImGui_ImplOpenGL3_Init("#version 410 core");
}

void View::destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void View::begin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void View::end() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
