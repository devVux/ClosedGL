#include "pch.h"
#include "Application.h"

#include "ClosedGL/Events/WindowEvents.h"
#include "ClosedGL/Events/MouseEvents.h"

#include "ClosedGL/Core/Input.h"

#include "ClosedGL/Renderer/Renderer2D.h"

#include "ClosedGL/Layers/ImGuiLayer.h"
#include "ClosedGL/Layers/StatsLayer.h"

static void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam) {
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

Application* Application::sInstance = nullptr;

Application::Application(AWindow* window): pWindow(window), pImGuiLayer(new ImGuiLayer), pStatsLayer(new StatsLayer) {

	sInstance = this;
	
	pWindow->init();

	mLayers.pushOverlay(pImGuiLayer);

}

void Application::init() {

	int success = gladLoadGL();
	assert(success != 0);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Renderer2D::init();

}

void Application::run() {

	mRunning = true;

	float t = static_cast<float>(glfwGetTime());
	float currentTime;


	while (mRunning) {

		Renderer2D::clear();

		currentTime = static_cast<float>(glfwGetTime());
		Timestep ts(std::min(currentTime - t, 0.05f));
		t = currentTime;

		mWorld.update(ts, 1, 1);
		
		pImGuiLayer->begin();
		mLayers.updateOverlays();
		mLayers.updateLayers();
		pImGuiLayer->end();


		update(ts);

		pWindow->update();

	}

}

void Application::onEvent(Event& e) {

	mDispatcher.dispatch<WindowCloseEvent>(e, [this](WindowCloseEvent& e) {
		mRunning = false;
	});

}
