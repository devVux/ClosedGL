#include "pch.h"
#include "Scene.h"

#include "ClosedGL/Renderer/Renderer2D.h"


void Scene::update(Timestep ts) const {

	const auto& group = mRegistry.view<PhysicsComponent, TransformComponent, SpriteComponent>();

	for (auto entity : group) {

		auto& p = group.get<PhysicsComponent>(entity);
		auto& t = group.get<TransformComponent>(entity);
		auto& s = group.get<SpriteComponent>(entity);

		auto& b = p.body;

		//Renderer2D::drawQuad(t.transform, s.color);

	}

	Renderer2D::drawQuad({ -1.0f, 0.0f }, { 10.0f, 10.0f }, { 0.2f, 0.5f, 0.7f });

}
