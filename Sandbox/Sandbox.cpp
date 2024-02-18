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
		
		std::vector<SubTexture> subs;

		Sandbox(Window* window): Application(window) {

			Entity& e = SceneManager::createEntity();
			Body* body = mWorld.createBody();

			e.addComponent<PhysicsComponent>(body, &e);
			e.addComponent<TransformComponent>(glm::mat4(2.0f));
			e.addComponent<SpriteComponent>(glm::vec3(0.0f));

			Texture& texture = TextureManager::create("F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Minecraft\\wood.png");
			e.addComponent<MeshComponent>(&texture);

			Entity& e2 = SceneManager::createEntity();
			Body* body2 = mWorld.createBody();
			body2->setPosition({ 10, 5 });
			e2.addComponent<PhysicsComponent>(body2, &e2);
			e2.addComponent<TransformComponent>(glm::mat4(1.0f));
			e2.addComponent<SpriteComponent>(glm::vec3(0.0f));

			Texture& texture2 = TextureManager::create("F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Chayed's Free Pixels\\Game Boy\\Gameboy Tileset.png");
			//SubTexture& sub2 = TextureManager::crop(texture2, { 0, 172, 16, 16 });
			subs = TextureManager::crop(texture2, { 
				{ 0, 172, 16, 16 },
				{ 0, 156, 16, 16 },
			});
			e2.addComponent<MeshComponent>(&subs[1]);

			TextureManager::resident();

		}

		virtual ~Sandbox() {

		}


};

Application* ClosedGL::create(Window* window) {
	return new Sandbox(window);
}