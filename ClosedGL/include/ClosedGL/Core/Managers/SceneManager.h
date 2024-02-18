#pragma once

#include <entt/entt.hpp>
#include "ClosedGL/Scene/Entity.h"

class SceneManager {

	public:

		~SceneManager() {
			while (!mEntities.empty()) {
				delete mEntities.back();
				mEntities.pop_back();
			}
		}

		static Entity& createEntity() {
			Entity* e = new Entity(mRegistry, mRegistry.create());
			mEntities.emplace_back(e);
			return *e;
		}

		template <class T>
		static T get(const Entity& entity) {
			return mRegistry.try_get<T>((entt::entity) entity.entityID());
		}

		template <class T, class ...U>
		static T group() {
			return mRegistry.group<T, U...>();
		}

		template <class T, class ...U>
		static auto view() {
			return mRegistry.view<T, U...>();
		}


	private:

		static std::vector<Entity*> mEntities;
		static entt::registry mRegistry;

};