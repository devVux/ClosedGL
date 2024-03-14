#pragma once
#include <ClosedGL.h>

#include <random>

static std::random_device dev;
static std::mt19937 rng(dev());
static std::uniform_real_distribution<float> color(0.0f, 1.0f);
static std::uniform_real_distribution<float> pos(-10.0f, 10.0f);
static std::uniform_real_distribution<float> dim(0.1f, 1.0f);

class Sandbox: public Application {

	public:
		
		std::vector<SubTexture> subs;

		Sandbox(Window* window): Application(window) {

			Application::init();
			
			Entity& e = SceneManager::createEntity();
			e.addComponent<TransformComponent>(glm::mat4(2.0f));
			Texture& texture = TextureManager::create("F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Minecraft\\glass.png");
			e.addComponent<SpriteComponent>(&texture, glm::vec3(0.0f));

			Entity& e2 = SceneManager::createEntity();
			e2.addComponent<TransformComponent>(glm::translate(glm::mat4(1.0f), { 2.0f, 2.0f, 0.0f }));
			e2.addComponent<SpriteComponent>(glm::vec3(0.6f));

		}

		virtual ~Sandbox() {

		}


};

Application* ClosedGL::create(Window* window) {
	return new Sandbox(window);
}