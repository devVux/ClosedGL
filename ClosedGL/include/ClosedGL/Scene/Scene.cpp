#include "pch.h"
#include "Scene.h"

#include "ClosedGL/Renderer/Renderer2D.h"
#include "Physiks/Body.h"

#include "ClosedGL/Core/Managers/SceneManager.h"

void Scene::update(Timestep ts) {

	const auto& group = SceneManager::view<PhysicsComponent, TransformComponent, SpriteComponent>();

	for (auto entity : group) {

		auto& p = group.get<PhysicsComponent>(entity);
		auto& t = group.get<TransformComponent>(entity);
		auto& s = group.get<SpriteComponent>(entity);

		auto& b = p.body;

		t.setPosition(glm::vec2(b->position().x, b->position().y));

		Renderer2D::drawQuad(t.transform, s.color);

	}

	const auto& view = SceneManager::view<MotionComponent>();

	for (auto entity : view) {

		auto& m = view.get<MotionComponent>(entity);

		m.move(ts);

	}

}