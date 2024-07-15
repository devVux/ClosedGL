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

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

static std::random_device dev;
static std::mt19937 rng(dev());
static std::uniform_real_distribution<float> color(0.0f, 1.0f);
static std::uniform_real_distribution<float> pos(-10.0f, 10.0f);
static std::uniform_real_distribution<float> dim(0.1f, 1.0f);

class Sandbox: public Application {

	public:
		
		Sandbox(Window* window): Application(window) {

			Ref<Scene> scene = std::make_shared<Scene>();
			Ref<Entity> e = scene->createEntity();

			{
				b2BodyDef groundBodyDef;
				groundBodyDef.position.Set(0.0f, -10.0f);

				b2Body* groundBody = mWorld.CreateBody(&groundBodyDef);
				b2PolygonShape groundBox;
				groundBox.SetAsBox(50.0f, 10.0f);

				groundBody->CreateFixture(&groundBox, 0.0f);

				e->addComponent<PhysicsComponent>(groundBody);
				e->addComponent<TransformComponent>(glm::mat4(2.0f));
				e->addComponent<SpriteComponent>(glm::vec3(0.0f));
			}

			mSceneManager.addScene(scene);

		}

		virtual ~Sandbox() {

		}


};

Application* ClosedGL::create(Window* window) {
	return new Sandbox(window);
}