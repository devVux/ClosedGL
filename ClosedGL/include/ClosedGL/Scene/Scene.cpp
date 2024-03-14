#include "pch.h"
#include "Scene.h"

#include "ClosedGL/Renderer/Renderer2D.h"

#include "ClosedGL/Core/Managers/SceneManager.h"

void Scene::update(Timestep ts) {

	const auto& group1 = SceneManager::view<TransformComponent, SpriteComponent>();

	for (auto entity : group1) {

		auto& t = group1.get<TransformComponent>(entity);
		auto& s = group1.get<SpriteComponent>(entity);

		if (s.texture)
			Renderer2D::drawQuad(t.transform, *s.texture, s.coords, s.color);
		else
			Renderer2D::drawQuad(t.transform, s.color);
	}

	
	const auto& group2 = SceneManager::view<TransformComponent>();

	for (auto entity : group2) {
		auto& t = group1.get<TransformComponent>(entity);
		Renderer2D::drawQuad(t.transform);
	}


}