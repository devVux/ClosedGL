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
		static T* get(const Entity& entity) {
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

		template <class T, class ...U>
		static bool hasComponent(const Entity& entity) {
			return mRegistry.any_of<T, U...>((entt::entity) entity.entityID());
		}

		template <class T, class ...U>
		static bool hasComponent(const entt::entity& entity) {
			return mRegistry.any_of<T, U...>(entity);
		}

		static const entt::registry& registry() { return mRegistry; }

	private:

		static std::vector<Entity*> mEntities;
		static entt::registry mRegistry;

};