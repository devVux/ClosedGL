#pragma once
#include <ClosedGL.h>

#include "ClosedGL/Scene/OrthographicCamera.h"

#include "ClosedGL/Renderer/Texture.h"
#include "ClosedGL/Scene/Components.h"

#include "ClosedGL/Scene/Entity.h"

#include <random>

#include "ClosedGL/Events/KeyEvents.h"

#include "ClosedGL/Core/Managers/SceneManager.h"
#include "ClosedGL/Core/Window.h"

static std::random_device dev;
static std::mt19937 rng(dev());
static std::uniform_real_distribution<float> color(0.0f, 1.0f);
static std::uniform_real_distribution<float> pos(-10.0f, 10.0f);
static std::uniform_real_distribution<float> dim(0.1f, 1.0f);

class Sandbox: public Application {

	public:

		Sandbox(Window* window): Application(window) {

			Entity& e = SceneManager::createEntity();
			Body* body = mWorld.createBody();

			e.addComponent<PhysicsComponent>(body, &e);
			e.addComponent<TransformComponent>(glm::mat4(1.0f));
			e.addComponent<SpriteComponent>(glm::vec3(0.0f));

		}

		virtual ~Sandbox() {

		}


};

Application* ClosedGL::create(Window* window) {
	return new Sandbox(window);
}