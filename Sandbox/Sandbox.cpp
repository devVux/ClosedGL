#pragma once
#include <ClosedGL.h>

#include "ClosedGL/Core/OrthographicCamera.h"

#include "ClosedGL/Renderer/Texture.h"
#include "ClosedGL/Scene/Components.h"

#include "ClosedGL/Scene/Entity.h"

#include <random>

#include "ClosedGL/Events/KeyEvents.h"

static std::random_device dev;
static std::mt19937 rng(dev());
static std::uniform_real_distribution<float> color(0.0f, 1.0f);
static std::uniform_real_distribution<float> pos(-10.0f, 10.0f);
static std::uniform_real_distribution<float> dim(0.1f, 1.0f);

class Sandbox: public Application {

	public:

		Sandbox(AWindow* window): Application(window) {

			auto e = mScene.createEntity();
			actor = mWorld.createBody();
			
			e->addComponent<PhysicsComponent<Body>>(actor, e);
			e->addComponent<TransformComponent>(glm::mat4(1.0f));
			e->addComponent<SpriteComponent>(glm::vec3(0.0f));

			auto e2 = mScene.createEntity();
			actor2 = mWorld.createBody();
			actor2->setPosition({ 3.0f, 3.0f }).setSize({ 3.0f, 1.0f });

			e2->addComponent<PhysicsComponent<Body>>(actor2, e2);
			e2->addComponent<TransformComponent>(
				glm::scale(
					glm::translate(glm::mat4(1.0f), glm::vec3(actor2->position().x, actor2->position().y, 0.0f)),
					glm::vec3(actor2->size().x, actor2->size().y, 0.0f))
			);
			e2->addComponent<SpriteComponent>(glm::vec3(1.0f));

			
				//srand((unsigned) time(0));
			
			
		}

		virtual ~Sandbox() {
			
		}

		void update(Timestep ts) {

			//mCamera.update(ts);

			Renderer2D::beginScene(mCamera);

			move();

			mScene.update(ts);
			Renderer2D::endScene();
		}

		void move() {
		
			static float speed = 10.0f;
			float x = 0, y = 0;

			if (Input::isKeyDown(CGL::KEY_W))
					y += speed;
			if (Input::isKeyDown(CGL::KEY_S))
					y += -speed;
			if (Input::isKeyDown(CGL::KEY_A))
					x += -speed;
			if (Input::isKeyDown(CGL::KEY_D))
					x += speed;

			actor->setVelocity({ x, y });

		}

	private:

		Scene mScene;
		OrthographicCamera mCamera;
		Body* actor;
		Body* actor2;
		EventDispatcher mDispatcher;

};

Application* ClosedGL::create(AWindow* window) {
	return new Sandbox(window);
}