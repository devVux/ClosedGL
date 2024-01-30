#pragma once

#include "ClosedGL/Core/Timestep.h"
#include "ClosedGL/Scene/OrthographicCamera.h"

#include "Entity.h"
#include <entt/entt.hpp>

#include <memory>

class Scene {
	
	public:
		
		void beginScene(const OrthographicCamera& camera);

		std::shared_ptr<Entity> createEntity();

		template <class T>
		T& get(const Entity& entity) {
			return *mRegistry.try_get<T>((entt::entity) entity.entityID());
		}

		void update(Timestep ts);
		void updatePhysics(Timestep ts);

	private:

		entt::registry mRegistry;

		glm::mat4 mView;
		glm::mat4 mProjection;

};
