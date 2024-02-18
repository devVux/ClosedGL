#pragma once
#include <ClosedGL.h>

#include "ClosedGL/Scene/OrthographicCamera.h"

#include "ClosedGL/Renderer/Texture.h"
#include "ClosedGL/Scene/Components.h"

#include "ClosedGL/Scene/Entity.h"

#include <random>

#include "ClosedGL/Events/KeyEvents.h"

#include "ClosedGL/Core/Managers/SceneManager.h"
#include "ClosedGL/Core/Managers/TextureManager.h"
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
			e.addComponent<TransformComponent>(glm::mat4(2.0f));
			e.addComponent<SpriteComponent>(glm::vec3(0.0f));

			Texture& whiteTexture = TextureManager::create(/*"F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Minecraft\\wood.png"*/);
			e.addComponent<MeshComponent>(&whiteTexture);

			Entity& e2 = SceneManager::createEntity();
			Body* body2 = mWorld.createBody();
			body2->setPosition({ 10, 5 });
			e2.addComponent<PhysicsComponent>(body2, &e2);
			e2.addComponent<TransformComponent>(glm::mat4(1.0f));
			e2.addComponent<SpriteComponent>(glm::vec3(0.0f));

			Texture& texture2 = TextureManager::create("F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Minecraft\\glass.png");
			e2.addComponent<MeshComponent>(&texture2);			
			
			Entity& e3 = SceneManager::createEntity();
			Body* body3 = mWorld.createBody();
			body3->setPosition({ 5, 10 });
			e3.addComponent<PhysicsComponent>(body3, &e3);
			e3.addComponent<TransformComponent>(glm::mat4(1.0f));
			e3.addComponent<SpriteComponent>(glm::vec3(0.0f));

			Texture& texture3 = TextureManager::create("F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Minecraft\\cobblestone.png");
			e3.addComponent<MeshComponent>(&texture3);

			TextureManager::resident();

		}

		virtual ~Sandbox() {

		}


};

Application* ClosedGL::create(Window* window) {
	return new Sandbox(window);
}