#include "pch.h"
#include "Application.h"

#include "ClosedGL/Events/WindowEvents.h"
#include "ClosedGL/Events/MouseEvents.h"

#include "ClosedGL/Core/Input.h"

#include "ClosedGL/Renderer/RenderCommands.h"
#include "ClosedGL/Renderer/Renderer2D.h"

#include "ClosedGL/Core/Managers/TextureManager.h"

static void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam) {
	if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}


uint32_t Application::Stats::updates = 0;
uint32_t Application::Stats::frameNr = 0;

Application* Application::sInstance = nullptr;


Timestep Time::delta = 0;


Application::Application(Window* window): pWindow(window), mWorld({ 0.0f, -10.0f }) {

	sInstance = this;
	
}

void Application::init() {

	int success = gladLoadGL();
	assert(success != 0);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create first white texture
	mTextureManager.create(std::nullopt);

	Renderer2D::init();

}

void Application::run() {

	mRunning = true;
	Time::Clock clock;
	Timestep accumulator = 0.0;

	Stats::updates = (uint32_t) (1 / clock.tickInterval() + 1);

	while (mRunning) {

		pWindow->pollEvents();

		Timestep ts = clock.tick();
		Time::delta = ts;
		accumulator += ts;

		while (accumulator >= clock.tickInterval()) {
			//mWorld.fixedUpdate(clock.tickInterval(), 1, 1);
			accumulator -= clock.tickInterval();
		}

		//mWorld.Step(ts, 1, 1);
		render(ts);

	}

}

void Application::render(Timestep ts) {
	RenderCommands::clear();

	Renderer2D::beginScene(mCamera);
	mCamera.update(ts);
	mSceneManager.updateCurrentScene(ts);
	Renderer2D::endScene();

	notify();
	pWindow->swapBuffers();
}

void Application::onEvent(Event& e) {

	mDispatcher.dispatch<WindowCloseEvent>(e, [this](WindowCloseEvent& e) {
		mRunning = false;
	});

}
