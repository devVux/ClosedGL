#pragma once

#include "entt/entt.hpp"

class Entity {

	public:

		Entity() = default;
		Entity(entt::registry& registry, entt::entity entityID): mHandle(registry, entityID) {  }

		template <class T, class... Args>
		inline void addComponent(Args&&... args) {
			mHandle.emplace<T>(std::forward<Args>(args)...);
		}
		
		template <class T>
		inline void removeComponent() {
			mHandle.erase<T>();
		}

		int entityID() const { return (int) mHandle.entity(); }

		bool operator==(const Entity& other) const { return entityID() == other.entityID(); }

	private:

		entt::handle mHandle;

};
