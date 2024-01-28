#include "pch.h"
#include "Scene.h"

#include "ClosedGL/Renderer/Renderer2D.h"
#include "Physiks/Body.h"

void Scene::beginScene(const OrthographicCamera& camera) {
	mView = camera.view();
	mProjection = camera.projection();
}

std::shared_ptr<Entity> Scene::createEntity() {
	return std::make_shared<Entity>(mRegistry, mRegistry.create());
}

void Scene::update(Timestep ts) {
	
	const auto& group = mRegistry.group<PhysicsComponent<Body>>(entt::get<TransformComponent, SpriteComponent>);

	for (auto entity : group) {
		
		auto& p = group.get<PhysicsComponent<Body>>(entity);
		auto& t = group.get<TransformComponent>(entity);
		auto& s = group.get<SpriteComponent>(entity);
		
		auto& b = p.body;

		t.setPosition(glm::vec2(b->position().x, b->position().y));

		Renderer2D::drawQuad(t.transform, s.color);

	}

}

void Scene::updatePhysics(Timestep ts) {


}
